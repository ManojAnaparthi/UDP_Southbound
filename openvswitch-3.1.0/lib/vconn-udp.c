/*
 * Copyright (c) 2025 IIT Gandhinagar - CN Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * vconn-udp.c - UDP virtual connection implementation for OpenFlow
 *
 * This file implements the vconn interface for UDP-based OpenFlow
 * connections, allowing OVS to communicate with controllers over UDP.
 *
 * Key Features:
 * - OpenFlow protocol over UDP
 * - Message boundary preservation
 * - Stateless communication
 * - Compatible with vconn interface
 */

#include <config.h>
#include "vconn-provider.h"
#include <errno.h>
#include <inttypes.h>
#include <netdb.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "openvswitch/dynamic-string.h"
#include "openvswitch/ofpbuf.h"
#include "openvswitch/vlog.h"
#include "openvswitch/ofp-msgs.h"
#include "openvswitch/ofp-print.h"
#include "packets.h"
#include "socket-util.h"
#include "stream.h"
#include "util.h"
#include "openflow/openflow.h"

VLOG_DEFINE_THIS_MODULE(vconn_udp);

/* Maximum OpenFlow message size (64KB - headers) */
#define MAX_OPENFLOW_MSG_SIZE 65535

/* UDP vconn structure */
struct vconn_udp {
    struct vconn vconn;         /* Base vconn structure */
    struct stream *stream;       /* Underlying UDP stream */
    struct ofpbuf *rxbuf;       /* Receive buffer for current message */
    struct ofpbuf *txbuf;       /* Transmit buffer for current message */
};

/* Cast from base vconn to UDP vconn */
static struct vconn_udp *
vconn_udp_cast(struct vconn *vconn)
{
    vconn_assert_class(vconn, &udp_vconn_class);
    return CONTAINER_OF(vconn, struct vconn_udp, vconn);
}

/* Create a new UDP vconn */
static struct vconn *
vconn_udp_new(struct stream *stream, int connect_status,
              uint32_t allowed_versions)
{
    struct vconn_udp *udp;

    udp = xmalloc(sizeof *udp);
    vconn_init(&udp->vconn, &udp_vconn_class, connect_status,
               stream_get_name(stream), allowed_versions);
    udp->stream = stream;
    udp->rxbuf = NULL;
    udp->txbuf = NULL;

    return &udp->vconn;
}

/* Open a UDP vconn connection */
static int
vconn_udp_open(const char *name, uint32_t allowed_versions,
               char *suffix OVS_UNUSED, struct vconn **vconnp, uint8_t dscp)
{
    struct stream *stream;
    int error;

    /* Open UDP stream (name includes the "udp:" prefix, like tcp/ssl). */
    error = stream_open_with_default_port(name, OFP_PORT, &stream, dscp);
    if (!error) {
        error = stream_connect(stream);
        if (!error || error == EAGAIN) {
            *vconnp = vconn_udp_new(stream, error, allowed_versions);
            VLOG_INFO("UDP vconn opened: %s", name);
            return 0;
        }
    }

    stream_close(stream);
    return error;
}

/* Close the UDP vconn */
static void
vconn_udp_close(struct vconn *vconn)
{
    struct vconn_udp *udp = vconn_udp_cast(vconn);

    VLOG_INFO("Closing UDP vconn: %s", vconn_get_name(vconn));

    stream_close(udp->stream);
    ofpbuf_delete(udp->rxbuf);
    ofpbuf_delete(udp->txbuf);
    free(udp);
}

/* Connect the UDP vconn */
static int
vconn_udp_connect(struct vconn *vconn)
{
    struct vconn_udp *udp = vconn_udp_cast(vconn);

    /* Delegate to stream layer */
    return stream_connect(udp->stream);
}

/* Receive an OpenFlow message via UDP */
static int
vconn_udp_recv(struct vconn *vconn, struct ofpbuf **msgp)
{
    struct vconn_udp *udp = vconn_udp_cast(vconn);
    struct ofpbuf *rx;
    size_t rx_len;
    int error;

    /* Allocate receive buffer if needed */
    if (!udp->rxbuf) {
        udp->rxbuf = ofpbuf_new(MAX_OPENFLOW_MSG_SIZE);
    }

    rx = udp->rxbuf;
    ofpbuf_clear(rx);

    /* Receive one UDP datagram (one complete OpenFlow message) */
    error = stream_recv(udp->stream, rx->data, ofpbuf_tailroom(rx));

    if (error <= 0) {
        if (error == -EAGAIN) {
            return EAGAIN;
        }
        VLOG_ERR("UDP recv error: %s", ovs_strerror(-error));
        return error ? -error : EOF;
    }

    rx_len = error;
    rx->size = rx_len;

    /* Validate OpenFlow message header */
    if (rx_len < sizeof(struct ofp_header)) {
        VLOG_WARN("Received too-short OpenFlow message (%zu bytes)", rx_len);
        return EAGAIN;
    }

    /* Check message length field matches received data */
    const struct ofp_header *oh = rx->data;
    size_t msg_len = ntohs(oh->length);

    if (msg_len > rx_len) {
        VLOG_WARN("OpenFlow message claims %zu bytes but only %zu received",
                  msg_len, rx_len);
        return EAGAIN;
    }

    if (msg_len < rx_len) {
        /* Truncate to actual message length */
        rx->size = msg_len;
    }

    /* Return the complete message */
    *msgp = rx;
    udp->rxbuf = NULL;  /* Transfer ownership to caller */

    VLOG_DBG("UDP received OpenFlow message: type=%u, length=%zu",
             oh->type, msg_len);

    return 0;
}

/* Send an OpenFlow message via UDP */
static int
vconn_udp_send(struct vconn *vconn, struct ofpbuf *msg)
{
    struct vconn_udp *udp = vconn_udp_cast(vconn);
    size_t msg_len = msg->size;
    int error;

    /* Validate message size */
    if (msg_len > MAX_OPENFLOW_MSG_SIZE) {
        VLOG_ERR("Message too large for UDP: %zu bytes", msg_len);
        ofpbuf_delete(msg);
        return EMSGSIZE;
    }

    /* Send entire message as one UDP datagram */
    error = stream_send(udp->stream, msg->data, msg_len);

    if (error == (int) msg_len) {
        /* Successfully sent */
        VLOG_DBG("UDP sent OpenFlow message: %zu bytes", msg_len);
        ofpbuf_delete(msg);
        return 0;
    } else if (error >= 0) {
        /* Partial send - shouldn't happen with UDP datagrams */
        VLOG_WARN("Partial UDP send: %d of %zu bytes", error, msg_len);
        ofpbuf_delete(msg);
        return EAGAIN;
    } else if (error == -EAGAIN) {
        /* Would block - save for later */
        if (udp->txbuf) {
            ofpbuf_delete(udp->txbuf);
        }
        udp->txbuf = msg;
        return 0;
    } else {
        /* Error */
        VLOG_ERR("UDP send error: %s", ovs_strerror(-error));
        ofpbuf_delete(msg);
        return -error;
    }
}

/* Run periodic operations */
static void
vconn_udp_run(struct vconn *vconn)
{
    struct vconn_udp *udp = vconn_udp_cast(vconn);

    stream_run(udp->stream);

    /* Try to flush pending transmit buffer */
    if (udp->txbuf) {
        size_t msg_len = udp->txbuf->size;
        int error = stream_send(udp->stream, udp->txbuf->data, msg_len);

        if (error == (int) msg_len) {
            VLOG_DBG("UDP flushed pending message: %zu bytes", msg_len);
            ofpbuf_delete(udp->txbuf);
            udp->txbuf = NULL;
        } else if (error >= 0) {
            VLOG_WARN("Partial UDP flush: %d of %zu bytes", error, msg_len);
        } else if (error != -EAGAIN) {
            VLOG_ERR("UDP flush error: %s", ovs_strerror(-error));
            ofpbuf_delete(udp->txbuf);
            udp->txbuf = NULL;
        }
    }
}

/* Wait for vconn events */
static void
vconn_udp_wait(struct vconn *vconn, enum vconn_wait_type wait)
{
    struct vconn_udp *udp = vconn_udp_cast(vconn);

    switch (wait) {
    case WAIT_CONNECT:
        stream_connect_wait(udp->stream);
        break;

    case WAIT_RECV:
        stream_recv_wait(udp->stream);
        break;

    case WAIT_SEND:
        if (udp->txbuf) {
            stream_send_wait(udp->stream);
        }
        break;

    default:
        OVS_NOT_REACHED();
    }
}

/* UDP vconn class definition */
const struct vconn_class udp_vconn_class = {
    "udp",                      /* name */
    vconn_udp_open,             /* open */
    vconn_udp_close,            /* close */
    vconn_udp_connect,          /* connect */
    vconn_udp_recv,             /* recv */
    vconn_udp_send,             /* send */
    vconn_udp_run,              /* run */
    NULL,                       /* run_wait */
    vconn_udp_wait,             /* wait */
};
