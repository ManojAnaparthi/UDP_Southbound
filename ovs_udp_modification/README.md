# Phase 4: Open vSwitch UDP Modification

## Overview

This phase implements UDP socket support in Open vSwitch (OVS) to enable end-to-end UDP communication between OVS switches and the UDP-based Ryu controller created in Phase 3.

## Modification Strategy

### Core Components to Modify

Open vSwitch uses an abstraction layer for network connections. We need to add UDP support at three key layers:

1. **Stream Layer** (`lib/stream-udp.c`) - Low-level UDP socket operations
2. **Virtual Connection Layer** (`lib/vconn-udp.c`) - OpenFlow connection over UDP
3. **Connection Manager** (`ofproto/connmgr.c`) - UDP-aware connection tracking

### Architecture

```
┌─────────────────────────────────────────────────┐
│         OVS Switch Application                  │
└─────────────────────────────────────────────────┘
                      │
                      ▼
┌─────────────────────────────────────────────────┐
│     Connection Manager (ofproto/connmgr.c)      │
│   - Manages controller connections              │
│   - Handles UDP connection states               │
└─────────────────────────────────────────────────┘
                      │
                      ▼
┌─────────────────────────────────────────────────┐
│   Virtual Connection Layer (lib/vconn-udp.c)    │
│   - OpenFlow message handling                   │
│   - Connection state machine                    │
│   - UDP-specific logic                          │
└─────────────────────────────────────────────────┘
                      │
                      ▼
┌─────────────────────────────────────────────────┐
│      Stream Layer (lib/stream-udp.c)            │
│   - UDP socket creation/binding                 │
│   - Send/receive operations                     │
│   - Address management                          │
└─────────────────────────────────────────────────┘
                      │
                      ▼
┌─────────────────────────────────────────────────┐
│            UDP Socket (OS Level)                │
└─────────────────────────────────────────────────┘
```

## Implementation Files

### 1. lib/stream-udp.c
Low-level UDP socket operations compatible with OVS stream interface.

**Key Functions**:
- `udp_open()` - Create and bind UDP socket
- `udp_connect()` - Connect to remote address
- `udp_recv()` - Receive data from socket
- `udp_send()` - Send data to socket
- `udp_close()` - Close socket

### 2. lib/vconn-udp.c
OpenFlow virtual connection implementation over UDP.

**Key Functions**:
- `vconn_udp_open()` - Open UDP connection to controller
- `vconn_udp_recv()` - Receive OpenFlow messages
- `vconn_udp_send()` - Send OpenFlow messages
- `vconn_udp_run()` - Process connection events
- `vconn_udp_close()` - Close connection

### 3. Modifications to ofproto/connmgr.c
Update connection manager to handle UDP connections.

**Changes Needed**:
- Add UDP connection type recognition
- Update connection tracking for stateless UDP
- Handle connection timeout for UDP (more lenient)
- Add UDP-specific error handling

## Protocol Flow

### Connection Establishment (UDP)

```
OVS Switch                           Ryu UDP Controller
    |                                        |
    |  1. Create UDP socket                 |
    |     (bind to local port)              |
    |                                        |
    |  2. Send HELLO (UDP)                  |
    |  ────────────────────────────────────>|
    |                                        |
    |                    3. Process HELLO   |
    |                       Send HELLO back |
    |  <────────────────────────────────────|
    |                                        |
    |  4. Process HELLO                     |
    |     Send FEATURES_REQUEST             |
    |  ────────────────────────────────────>|
    |                                        |
    |              5. Send FEATURES_REPLY   |
    |  <────────────────────────────────────|
    |                                        |
    |  6. Connection established            |
    |     Ready for packet forwarding       |
```

### Message Exchange

All OpenFlow messages (HELLO, FEATURES_REQUEST/REPLY, PACKET_IN, FLOW_MOD, etc.) are sent as UDP datagrams to controller:port.

## Key Differences from TCP

| Aspect | TCP (Original) | UDP (Modified) |
|--------|---------------|----------------|
| Connection | Stateful, 3-way handshake | Stateless, immediate send |
| Reliability | Automatic retransmission | Application-level (optional) |
| Ordering | In-order delivery | No ordering guarantee |
| Overhead | Higher (connection state) | Lower (no state) |
| Message Boundary | Stream (no boundaries) | Datagram (preserved) |
| Port per switch | Ephemeral client port | Can use fixed port |

## Design Decisions

### 1. Connectionless Operation
- No persistent connection state between messages
- Each OpenFlow message is a separate UDP datagram
- Controller address stored for outbound messages

### 2. Message Boundaries
- UDP preserves message boundaries (unlike TCP streams)
- No need for message framing/delimiting
- Simpler parsing on receiver side

### 3. Reliability (Optional)
- Phase 4: Basic UDP with no retransmission
- Phase 6: Add selective reliability for critical messages
- Use OpenFlow xid (transaction ID) for matching responses

### 4. Connection "State"
- Track controller address and last message time
- Implement timeout-based connection cleanup
- Maintain minimal state for OpenFlow handshake

## Testing Strategy

### Unit Tests
1. UDP socket creation and binding
2. OpenFlow message send/receive over UDP
3. Message parsing with UDP-preserved boundaries

### Integration Tests
1. OVS switch connects to UDP controller (Phase 3)
2. HELLO exchange over UDP
3. FEATURES_REQUEST/REPLY exchange
4. PACKET_IN notifications
5. FLOW_MOD installation

### End-to-End Test
1. Start Mininet with modified OVS
2. Start UDP Ryu controller
3. Generate traffic between hosts
4. Verify flow installation and packet forwarding
5. Capture and analyze UDP OpenFlow traffic

## Build Instructions

### Prerequisites
```bash
# Install OVS build dependencies
sudo apt-get install -y build-essential autoconf automake libtool \
    libssl-dev python3-dev python3-pip
```

### Compilation
```bash
# Navigate to OVS source directory
cd /path/to/openvswitch-source

# Apply UDP modifications (copy our files)
cp /path/to/CN_Project_SDN/ovs_udp_modification/lib/stream-udp.c lib/
cp /path/to/CN_Project_SDN/ovs_udp_modification/lib/vconn-udp.c lib/

# Bootstrap and configure
./boot.sh
./configure --prefix=/usr --localstatedir=/var --sysconfdir=/etc

# Build
make -j$(nproc)

# Install (optional)
sudo make install
```

### Testing Modified OVS
```bash
# Run in-tree (without install)
cd /path/to/openvswitch-source
sudo ./vswitchd/ovs-vswitchd --log-file --verbose

# Check UDP support
sudo ovs-vsctl show
sudo ovs-vsctl set-controller br0 udp:127.0.0.1:6633
```

## Integration with Phase 3 UDP Controller

### Controller Setup (Terminal 1)
```bash
cd /path/to/CN_Project_SDN
python3 -m udp_baseline.controllers.udp_ofp_controller
# Expected: [INFO] UDP OpenFlow Controller listening on 0.0.0.0:6633
```

### Modified OVS Setup (Terminal 2)
```bash
# Start OVS with UDP controller
sudo ovs-vsctl set-controller br0 udp:127.0.0.1:6633

# Verify connection
sudo ovs-vsctl show
# Should show: Controller "udp:127.0.0.1:6633"
```

### Traffic Generation (Terminal 3)
```bash
# Using Mininet
sudo mn --controller=remote,ip=127.0.0.1,port=6633,protocol=udp

# Or manual ping
h1 ping h2
```

## Expected Output

### Controller Logs
```
[INFO] UDP OpenFlow Controller listening on 0.0.0.0:6633
[INFO] Received HELLO from ('127.0.0.1', 54321), xid=1
[SEND] HELLO → ('127.0.0.1', 54321)
[SEND] FEATURES_REQUEST → ('127.0.0.1', 54321)
[INFO] Received FEATURES_REPLY from ('127.0.0.1', 54321)
[INFO] Switch connected: DPID=0x0000000000000001
[INFO] Received PACKET_IN from DPID=0x0000000000000001
```

### OVS Logs
```
2025-11-08T10:30:00.000Z|00001|vconn|INFO|udp:127.0.0.1:6633: connected
2025-11-08T10:30:00.100Z|00002|rconn|INFO|udp:127.0.0.1:6633: connection established
2025-11-08T10:30:00.200Z|00003|ofproto|INFO|features reply received
```

## Validation Checklist

- [ ] UDP socket successfully created and bound
- [ ] HELLO message exchange over UDP
- [ ] FEATURES_REQUEST/REPLY successful
- [ ] PACKET_IN notifications reach controller
- [ ] FLOW_MOD commands install flows
- [ ] Multi-switch support works
- [ ] No TCP connections in netstat output
- [ ] Wireshark shows UDP OpenFlow traffic on port 6633

## Performance Metrics to Collect

After Phase 4 implementation, we can compare:

1. **Connection Setup Time**
   - TCP: 3-way handshake + OpenFlow HELLO
   - UDP: Direct OpenFlow HELLO

2. **Message Latency**
   - End-to-end latency for PACKET_IN → FLOW_MOD

3. **Throughput**
   - Messages per second under load

4. **Resource Usage**
   - Memory footprint (TCP connection state vs UDP)
   - CPU usage

## Next Steps

After Phase 4:
- **Phase 5**: Run performance benchmarks (TCP vs UDP)
- **Phase 6**: Add reliability layer for critical messages
- **Phase 7**: Final analysis and documentation

## References

- Open vSwitch Architecture: https://docs.openvswitch.org/en/latest/
- OpenFlow 1.3 Specification: https://www.opennetworking.org/
- OVS Source Code: https://github.com/openvswitch/ovs
- Phase 3 UDP Controller: `udp_baseline/controllers/udp_ofp_controller.py`

---

**Status**: Phase 4 Implementation Files Created  
**Date**: November 8, 2025  
**Next**: Implement stream-udp.c and vconn-udp.c
