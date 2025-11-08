# Connection Manager Modifications for UDP Support

## Overview

The connection manager (`ofproto/connmgr.c`) needs minimal modifications to support UDP-based OpenFlow connections. Since we've implemented UDP at the stream and vconn layers, the connection manager primarily needs awareness of UDP's stateless nature.

## Key Differences: TCP vs UDP

| Aspect | TCP Connection | UDP Connection |
|--------|---------------|----------------|
| State Tracking | Full connection state | Minimal state |
| Connection Timeout | Standard (e.g., 10s) | More lenient (e.g., 30s) |
| Failure Detection | TCP keepalive + retries | Message timeout only |
| Reconnection | Requires new 3-way handshake | Immediate (no handshake) |
| Message Delivery | Guaranteed in-order | Best-effort |

## Required Modifications

### 1. Connection Type Detection

Add UDP connection type detection in connection initialization:

```c
/* In ofproto/connmgr.c */

static bool
is_udp_connection(const struct rconn *rc)
{
    const char *target = rconn_get_target(rc);
    return target && !strncmp(target, "udp:", 4);
}
```

### 2. Timeout Configuration

Adjust timeouts for UDP connections (more lenient due to stateless nature):

```c
/* In ofproto/connmgr.c - connmgr_set_probe_interval() or similar */

static int
get_probe_interval(struct rconn *rc)
{
    if (is_udp_connection(rc)) {
        /* UDP: longer probe interval since there's no connection state */
        return 30;  /* 30 seconds instead of default 10 */
    } else {
        /* TCP: standard probe interval */
        return 10;
    }
}
```

### 3. Connection State Handling

Update connection state machine to handle UDP's immediate "connection":

```c
/* In ofproto/connmgr.c - connection state handling */

static void
ofconn_create(struct connmgr *mgr, struct rconn *rconn, 
              enum ofconn_type type, bool enable_async_msgs)
{
    struct ofconn *ofconn = xzalloc(sizeof *ofconn);
    
    /* ... existing initialization ... */
    
    /* UDP connections are immediately "active" */
    if (is_udp_connection(rconn)) {
        ofconn->protocol = OFPUTIL_P_OF13_OXM;  /* OpenFlow 1.3 */
        rconn_set_probe_interval(rconn, get_probe_interval(rconn));
    }
    
    /* ... rest of initialization ... */
}
```

### 4. Error Handling

Add UDP-specific error handling (less strict than TCP):

```c
/* In ofproto/connmgr.c - error handling */

static void
handle_connection_failure(struct ofconn *ofconn, int error)
{
    struct rconn *rc = ofconn_get_rconn(ofconn);
    
    if (is_udp_connection(rc)) {
        /* UDP: Don't immediately disconnect on transient errors */
        if (error == EAGAIN || error == EWOULDBLOCK) {
            /* Normal for UDP - just retry */
            return;
        }
        /* Only disconnect on persistent errors */
        if (ofconn->error_count++ > UDP_ERROR_THRESHOLD) {
            rconn_disconnect(rc);
        }
    } else {
        /* TCP: Standard error handling */
        rconn_disconnect(rc);
    }
}
```

## Configuration Changes

### 1. Controller URL Format

Support `udp:` prefix in controller URLs:

```bash
# Old (TCP):
ovs-vsctl set-controller br0 tcp:127.0.0.1:6633

# New (UDP):
ovs-vsctl set-controller br0 udp:127.0.0.1:6633
```

### 2. Database Schema

No changes needed to OVSDB schema - the `target` field already supports arbitrary URL formats.

## Integration Points

### Files to Modify

1. **ofproto/connmgr.c**
   - Add `is_udp_connection()` helper function
   - Modify `get_probe_interval()` to return different values for UDP
   - Update connection state initialization
   - Add UDP-aware error handling

2. **lib/rconn.c** (optional)
   - Add UDP-specific connection tracking
   - Implement lenient timeout logic

3. **vswitchd/bridge.c** (optional)
   - Add UDP support validation
   - Log UDP connection establishment

### Minimal Patch Approach

For academic purposes, the minimal modification is to ensure the vconn and stream classes are registered:

```c
/* In lib/stream.c - register stream classes */

void
stream_init(void)
{
    static struct ovsthread_once once = OVSTHREAD_ONCE_INITIALIZER;

    if (ovsthread_once_start(&once)) {
        /* Register all stream classes */
        stream_register_class(&tcp_stream_class);
        stream_register_class(&unix_stream_class);
        stream_register_class(&udp_stream_class);  /* ADD THIS */
        /* ... */
        ovsthread_once_done(&once);
    }
}
```

```c
/* In lib/vconn.c - register vconn classes */

void
vconn_init(void)
{
    static struct ovsthread_once once = OVSTHREAD_ONCE_INITIALIZER;

    if (ovsthread_once_start(&once)) {
        /* Register all vconn classes */
        vconn_register_class(&tcp_vconn_class);
        vconn_register_class(&unix_vconn_class);
        vconn_register_class(&udp_vconn_class);  /* ADD THIS */
        /* ... */
        ovsthread_once_done(&once);
    }
}
```

## Testing Changes

After modifications, test with:

```bash
# 1. Start UDP controller
python3 -m udp_baseline.controllers.udp_ofp_controller

# 2. Configure OVS to use UDP
sudo ovs-vsctl set-controller br0 udp:127.0.0.1:6633

# 3. Verify connection
sudo ovs-vsctl show
# Should show: Controller "udp:127.0.0.1:6633" is_connected: true

# 4. Check logs
sudo ovs-appctl vlog/list | grep -E "(vconn_udp|stream_udp)"
```

## Validation

### Expected Behavior

1. ✅ Controller URL accepts `udp:` prefix
2. ✅ UDP vconn and stream classes load successfully
3. ✅ OpenFlow HELLO exchange over UDP
4. ✅ FEATURES_REQUEST/REPLY over UDP
5. ✅ Packet-in messages sent via UDP
6. ✅ Flow-mod messages received via UDP
7. ✅ Connection remains stable under load

### Log Messages

```
# OVS vswitchd logs:
INFO|stream_udp|UDP stream opened to udp:127.0.0.1:6633 (fd=12)
INFO|vconn_udp|UDP vconn opened: udp:127.0.0.1:6633
INFO|rconn|udp:127.0.0.1:6633: connected
INFO|ofproto|br0: using datapath ID 0000000000000001
INFO|ofproto|br0: datapath ID changed to 0000000000000001

# Controller logs:
[INFO] UDP OpenFlow Controller listening on 0.0.0.0:6633
[INFO] Received HELLO from ('127.0.0.1', 54321), xid=1
[SEND] HELLO → ('127.0.0.1', 54321)
[INFO] Switch connected: DPID=0x0000000000000001
```

## Rollback Plan

If UDP modifications cause issues:

```bash
# Revert to TCP
sudo ovs-vsctl set-controller br0 tcp:127.0.0.1:6633

# Or remove controller
sudo ovs-vsctl del-controller br0

# Restart OVS with original code
sudo systemctl restart openvswitch-switch
```

## Performance Considerations

### UDP Advantages
- No 3-way handshake delay
- No connection state overhead
- Faster message delivery (no ACK wait)
- Better for stateless control messages

### UDP Challenges
- No automatic retransmission
- No flow control
- Potential message loss (mitigated by reliable network)
- Out-of-order delivery (handled by OpenFlow xid)

## Next Steps

1. Apply minimal patches to connmgr.c
2. Register stream and vconn classes
3. Rebuild OVS
4. Run integration tests
5. Collect performance metrics (Phase 5)

---

**Note**: These modifications maintain backward compatibility. TCP connections continue to work unchanged. UDP support is purely additive.
