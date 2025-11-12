# UDP-BASED SDN CONTROLLER IMPLEMENTATION

**Project Goal**: Implement direct UDP communication between Open vSwitch and Ryu SDN controller

**Date Started**: November 12, 2025  
**Repository**: CN_Project_SDN

---

## PROJECT MOTIVATION

### Why UDP for SDN?
1. **TCP Overhead**: TCP connection setup, teardown, and state maintenance adds latency
2. **QuicSDN Results**: Showed 20-40% performance improvement over TCP
3. **Message Characteristics**: SDN control messages are typically short and don't need TCP's guarantees
4. **Stateless**: UDP eliminates connection state overhead

### Our Approach
Instead of modifying OVS source code (complex), we:
- Leverage existing OVS UDP support (lib/stream-udp.c, lib/vconn-udp.c)
- Build custom Ryu controller with UDP socket support
- Direct UDP communication (no tunneling)

---

## IMPLEMENTATION PHASES

### Phase 1: OVS UDP Validation ⏳
**Goal**: Verify OVS can send OpenFlow messages over UDP

**Tasks**:
- [ ] Create minimal UDP listener on port 6653
- [ ] Configure OVS bridge with UDP controller
- [ ] Capture and decode HELLO messages
- [ ] Test ECHO_REQUEST (keepalive)
- [ ] Test PACKET_IN messages
- [ ] Document message formats

### Phase 2: Basic Ryu UDP Controller
**Goal**: Implement OpenFlow protocol handler

**Tasks**:
- [ ] Create Ryu app with UDP socket
- [ ] Implement HELLO exchange
- [ ] Handle FEATURES_REQUEST/REPLY
- [ ] Respond to ECHO_REQUEST
- [ ] Process PACKET_IN messages
- [ ] Install table-miss flow

### Phase 3: L2 Learning Logic
**Goal**: Add MAC learning and intelligent forwarding

**Tasks**:
- [ ] Parse Ethernet headers from PACKET_IN
- [ ] Implement MAC address learning table
- [ ] Install flows for known MAC addresses
- [ ] Flood packets for unknown destinations
- [ ] Handle switch reconnections

### Phase 4: Performance Benchmarking
**Goal**: Quantify UDP vs TCP improvements

**Tasks**:
- [ ] Measure TCP baseline (latency, throughput)
- [ ] Measure UDP performance
- [ ] Compare CPU usage
- [ ] Test packet loss
- [ ] Generate performance report

---

## TECHNICAL BACKGROUND

### OpenFlow Protocol
- **Version**: OpenFlow 1.3 (0x04) or 1.5 (0x06)
- **Message Header**: 8 bytes [version][type][length][xid]
- **Key Messages**:
  - HELLO (0x00): Protocol negotiation
  - ECHO_REQUEST (0x02): Keepalive
  - FEATURES_REQUEST (0x05): Get switch capabilities
  - PACKET_IN (0x0a): Packet received by switch
  - FLOW_MOD (0x0e): Install flow entries
  - PACKET_OUT (0x0d): Send packet from switch

### OVS UDP Support
- **Files**: lib/stream-udp.c (260 lines), lib/vconn-udp.c (316 lines)
- **Socket Type**: Connected UDP (simplified API)
- **Port**: Standard OpenFlow port 6653
- **Configuration**: `ovs-vsctl set-controller <bridge> udp:<ip>:<port>`

---

## ENVIRONMENT SETUP

### Prerequisites
```bash
# Install OVS
sudo apt-get install openvswitch-switch

# Install Ryu
pip3 install ryu

# Fix eventlet compatibility
pip3 install 'eventlet==0.33.3'

# Python version
python3.8 or higher (for f-strings)
```

### Test Bridge Setup
```bash
sudo ovs-vsctl add-br br-udp-test
sudo ovs-vsctl set bridge br-udp-test protocols=OpenFlow13
sudo ovs-vsctl set-controller br-udp-test udp:127.0.0.1:6653
```

---

## PROGRESS LOG

### 2025-11-12: Project Initialization
- Created project structure
- Reviewed quicSDN approach (QUIC tunneling)
- Decided on direct UDP approach (simpler, no encryption overhead)
- Starting Phase 1: OVS UDP Validation

---

## REFERENCES

1. **QuicSDN Paper**: arXiv:2107.08336 - "Enhancing SDN Flows using QUIC"
2. **OVS UDP Code**: ovs/lib/stream-udp.c, ovs/lib/vconn-udp.c
3. **OpenFlow Spec**: OpenFlow 1.3/1.5 Specification
4. **Ryu Documentation**: https://ryu.readthedocs.io/

---

## NOTES

- QuicSDN uses QUIC tunneling (client/server architecture)
- We use direct UDP (simpler, no encryption/reliability layer)
- OVS UDP support is production-ready (no modifications needed)
- UDP preserves message boundaries (no framing required)
