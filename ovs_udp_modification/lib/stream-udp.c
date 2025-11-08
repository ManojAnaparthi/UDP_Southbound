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
 * stream-udp.c - UDP socket stream implementation for Open vSwitch
 *
 * This file implements the stream interface for UDP sockets, enabling
 * Open vSwitch to communicate with controllers using UDP instead of TCP.
 *
 * Key Features:
 * - Stateless UDP communication
 * - Compatible with OVS stream interface
 * - Message boundary preservation
 * - Minimal connection state
 */

#include <config.h>
#include "stream-provider.h"
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "openvswitch/dynamic-string.h"
#include "openvswitch/vlog.h"
#include "packets.h"
#include "socket-util.h"
#include "util.h"

VLOG_DEFINE_THIS_MODULE(stream_udp);

/* UDP stream structure */
struct udp_stream {
    struct stream stream;           /* Base stream structure */
    int fd;                         /* UDP socket file descriptor */
    struct sockaddr_storage remote; /* Remote controller address */
    socklen_t remote_len;          /* Length of remote address */
    bool connected;                 /* Connection state flag */
};

/* Cast from base stream to UDP stream */
static struct udp_stream *
udp_stream_cast(struct stream *stream)
{
    stream_assert_class(stream, &udp_stream_class);
    return CONTAINER_OF(stream, struct udp_stream, stream);
}

/* Create a new UDP stream */
static int
new_udp_stream(const char *name, int fd, int connect_status,
               struct sockaddr_storage *remote, socklen_t remote_len,
               struct stream **streamp)
{
    struct udp_stream *s;

    s = xmalloc(sizeof *s);
    stream_init(&s->stream, &udp_stream_class, connect_status, name);
    s->fd = fd;
    s->remote = *remote;
    s->remote_len = remote_len;
    s->connected = (connect_status == 0);
    
    *streamp = &s->stream;
    return 0;
}

/* Open a UDP stream connection */
static int
udp_open(const char *name, char *suffix, struct stream **streamp,
         uint8_t dscp OVS_UNUSED)
{
    struct sockaddr_storage ss;
    socklen_t ss_len;
    int fd, error;

    /* Parse the target address (format: udp:IP:PORT) */
    error = inet_parse_active(suffix, 0, &ss, &ss_len, NULL);
    if (error) {
        VLOG_ERR("Failed to parse UDP address '%s': %s", 
                 suffix, ovs_strerror(error));
        return error;
    }

    /* Create UDP socket */
    fd = socket(ss.ss_family, SOCK_DGRAM, IPPROTO_UDP);
    if (fd < 0) {
        error = errno;
        VLOG_ERR("Failed to create UDP socket: %s", ovs_strerror(error));
        return error;
    }

    /* Set socket to non-blocking mode */
    error = set_nonblocking(fd);
    if (error) {
        VLOG_ERR("Failed to set non-blocking mode: %s", ovs_strerror(error));
        close(fd);
        return error;
    }

    /* "Connect" the UDP socket (sets default destination) */
    if (connect(fd, (struct sockaddr *)&ss, ss_len) < 0) {
        error = errno;
        /* For UDP, connect() failure might not be fatal */
        VLOG_WARN("UDP connect() returned error: %s", ovs_strerror(error));
        /* Continue anyway - we can still use sendto() */
    }

    /* Enable SO_REUSEADDR for better socket reuse */
    int enable = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0) {
        VLOG_WARN("Failed to set SO_REUSEADDR: %s", ovs_strerror(errno));
    }

    VLOG_INFO("UDP stream opened to %s (fd=%d)", name, fd);

    return new_udp_stream(name, fd, 0, &ss, ss_len, streamp);
}

/* Close the UDP stream */
static void
udp_close(struct stream *stream)
{
    struct udp_stream *s = udp_stream_cast(stream);
    
    VLOG_INFO("Closing UDP stream (fd=%d)", s->fd);
    
    close(s->fd);
    free(s);
}

/* Connect the UDP stream (always succeeds for UDP) */
static int
udp_connect(struct stream *stream)
{
    struct udp_stream *s = udp_stream_cast(stream);
    
    /* UDP is connectionless, so we just mark as connected */
    s->connected = true;
    
    return 0;
}

/* Receive data from UDP socket */
static ssize_t
udp_recv(struct stream *stream, void *buffer, size_t n)
{
    struct udp_stream *s = udp_stream_cast(stream);
    ssize_t retval;

    /* Receive UDP datagram */
    retval = recvfrom(s->fd, buffer, n, 0, 
                      (struct sockaddr *)&s->remote, &s->remote_len);
    
    if (retval < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return -EAGAIN;
        }
        VLOG_ERR("UDP recv error: %s", ovs_strerror(errno));
        return -errno;
    }
    
    if (retval == 0) {
        /* Empty datagram - shouldn't happen but handle it */
        return -EAGAIN;
    }

    VLOG_DBG("UDP received %zd bytes", retval);
    
    return retval;
}

/* Send data via UDP socket */
static ssize_t
udp_send(struct stream *stream, const void *buffer, size_t n)
{
    struct udp_stream *s = udp_stream_cast(stream);
    ssize_t retval;

    /* Send UDP datagram to connected address */
    retval = sendto(s->fd, buffer, n, 0,
                    (struct sockaddr *)&s->remote, s->remote_len);
    
    if (retval < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return -EAGAIN;
        }
        VLOG_ERR("UDP send error: %s", ovs_strerror(errno));
        return -errno;
    }

    VLOG_DBG("UDP sent %zd bytes", retval);
    
    return retval;
}

/* Run periodic operations (no-op for UDP) */
static void
udp_run(struct stream *stream OVS_UNUSED)
{
    /* Nothing to do for UDP */
}

/* Wait for stream events */
static void
udp_wait(struct stream *stream, enum stream_wait_type wait)
{
    struct udp_stream *s = udp_stream_cast(stream);
    
    switch (wait) {
    case STREAM_CONNECT:
        /* UDP is "connected" immediately */
        break;
        
    case STREAM_RECV:
        poll_fd_wait(s->fd, POLLIN);
        break;
        
    case STREAM_SEND:
        poll_fd_wait(s->fd, POLLOUT);
        break;
        
    default:
        OVS_NOT_REACHED();
    }
}

/* UDP stream class definition */
const struct stream_class udp_stream_class = {
    "udp",                      /* name */
    false,                      /* needs_probes */
    udp_open,                   /* open */
    udp_close,                  /* close */
    udp_connect,                /* connect */
    udp_recv,                   /* recv */
    udp_send,                   /* send */
    udp_run,                    /* run */
    NULL,                       /* run_wait */
    udp_wait,                   /* wait */
};
