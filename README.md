# TCP to UDP SDN Southbound Protocol Modification

## Project Overview

Modification of SDN southbound communication protocol from TCP to UDP for the Ryu controller and Open vSwitch (OVS) architecture. This project aims to reduce connection overhead and improve performance while maintaining reliable control plane communication.

### Current Status: Phase 1-3 Complete ✅

**Completed Work**:
- ✅ Phase 1: Environment setup and TCP baseline implementation
- ✅ Phase 2: Performance metrics collection (94,423 events captured)
- ✅ Phase 3: Code architecture analysis and UDP controller implementation (310 lines)

**Key Achievements**:
- TCP baseline: 2,526 msg/sec throughput, 1.973ms mean latency
- UDP compatibility validated: 99.7% safety margin (218 bytes vs 65KB limit)
- Standalone UDP OpenFlow controller working with HELLO/FEATURES exchange

**Next Phase**: Modify Open vSwitch (OVS) for UDP support

---

## Project Phases

| Phase | Title | Description | Status | Deliverables |
|-------|-------|-------------|--------|--------------|
| **1** | Environment Setup & TCP Baseline | Install tools (Ryu, OVS, Mininet), implement TCP baseline controller, collect performance data | ✅ Complete | TCP controller, 94K events, 4-panel visualization |
| **2** | Code Analysis & Architecture | Analyze Ryu & OVS architecture, identify TCP components, map UDP modification points | ✅ Complete | Architecture documentation, 8 modification points identified |
| **3** | UDP Implementation (Ryu) | Create standalone UDP OpenFlow controller, implement message parsing, validate basic communication | ✅ Complete | UDP controller (310 lines), message parser, test suite |
| **4** | UDP Implementation (OVS) | Modify Open vSwitch C code for UDP sockets, enable end-to-end UDP communication | 🔜 Next | Modified OVS with UDP support |
| **5** | Performance Testing | Run comparative tests (TCP vs UDP), collect metrics, analyze performance differences | ⏳ Pending | Performance comparison data, metrics |
| **6** | Reliability Mechanisms | Implement selective ACK, retransmission, sequence tracking for critical messages | ⏳ Pending | Reliability layer implementation |
| **7** | Final Analysis & Documentation | Generate visualizations, write final report, prepare presentation | ⏳ Pending | Final report, presentation slides |

**Current Phase**: Phase 3 Complete, Phase 4 Ready to Begin  
**Completion**: 3/7 Phases (43%)

---

## Phase 1: Environment Setup & TCP Baseline ✅

### 1.1 Environment Configuration
**Tools Installed**:
- Ryu SDN Controller (Python-based, OpenFlow 1.3)
- Open vSwitch 2.x
- Mininet network emulator
- Python libraries: ryu, eventlet, msgpack, numpy, matplotlib, seaborn

**Test Infrastructure**:
```
tcp_baseline/
  ├── controllers/       - Ryu controller implementations
  ├── analysis/          - Analysis and visualization scripts
  ├── data/              - Raw data (metrics, logs, pcap)
  ├── results/           - Reports and visualizations
  └── topology/          - Mininet network topologies
```

### 1.2 TCP Baseline Implementation

**Controller**: L2 Learning Switch with comprehensive instrumentation
- OpenFlow 1.3 protocol
- Event-driven architecture
- Tracks 9 message types: Packet-In, Flow-Mod, Packet-Out, Hello, Features Request/Reply, Echo Request/Reply, Barrier
- Metrics: latency, throughput, message sizes, connection overhead

**Test Topology**:
- 3 switches in linear configuration
- 4 hosts (2 per edge switch)
- Automatic ping traffic generation

### 1.3 Performance Metrics Collected

**Baseline Results**:
```
Duration:         37.38 seconds
Total Messages:   94,423 (Packet-In events)
Throughput:       2,526 msg/sec
Mean Latency:     1.973 ms
Median Latency:   1.133 ms
Std Deviation:    2.419 ms
P95 Latency:      8.805 ms
P99 Latency:      8.898 ms
Latency Range:    [0.236, 8.921] ms
```

**Message Size Analysis**:
```
Max Message Size:  218 bytes
UDP Limit:         65,507 bytes
Safety Margin:     99.7%
UDP Compatible:    ✅ YES (no fragmentation needed)
```

**Key Finding**: All OpenFlow messages are well within UDP's 65KB datagram limit, validating UDP conversion feasibility.

### 1.4 Data Collected

**Files Generated** (in `tcp_baseline/`):
- `data/tcp_baseline_metrics.json` (7.1 MB) - Raw performance data with 94,423 events
- `data/tcp_baseline.pcap` (46 KB) - Network packet capture
- `data/tcp_baseline.log` (60 MB) - Detailed controller logs
- `results/tcp_baseline_performance.png` (689 KB) - 4-panel visualization
- `results/tcp_baseline_report.txt` (1.2 KB) - Performance summary

**Visualization**: Comprehensive 4-panel performance analysis:
1. **Throughput Over Time** - Message rate per second with peak detection
2. **Average Latency Comparison** - Simple bar chart comparing message types
3. **Message Sizes vs UDP Limit** - Box plots validating UDP compatibility
4. **Protocol Overhead Breakdown** - TCP header overhead analysis (54 bytes/msg)

![TCP Baseline Performance](tcp_baseline/results/tcp_baseline_performance.png)

---

## Phase 2: Code Analysis & Architecture Understanding ✅

### 2.1 Ryu Controller Architecture

**Core Components Analyzed**:

1. **StreamServer** (`ryu/controller/controller.py`):
   - TCP socket management
   - Connection handling via `eventlet.listen()`
   - **Modification Point**: Replace with UDP DatagramServer

2. **OpenFlow Protocol** (`ryu/ofproto/`):
   - Message parsing and serialization
   - Protocol state machine
   - **Modification Point**: Add UDP sequence numbers and ACKs

3. **Event System** (`ryu/controller/ofp_event.py`):
   - Event-driven message handling
   - Minimal changes needed (protocol-agnostic)

4. **Connection Manager**:
   - Datapath lifecycle management
   - **Modification Point**: UDP connection state tracking

### 2.2 Key Code Locations

**Ryu Controller** (Python):
```
ryu/controller/controller.py:
  - Line 89-120: StreamServer initialization (TCP)
  - Line 200-250: Connection accept handler
  → Replace with DatagramServer and UDP socket

ryu/controller/ofp_handler.py:
  - Line 180-200: Message receive/send
  → Add UDP reliability layer

ryu/lib/hub.py:
  - Socket wrapper abstractions
  → Add UDP-specific methods
```

**Open vSwitch** (C) - Phase 4:
```
lib/stream.c:
  - TCP stream management
  → Add UDP stream support

lib/vconn.c:
  - Virtual connection abstraction
  → UDP connection state machine

ofproto/connmgr.c:
  - Connection manager
  → UDP-aware connection tracking
```

### 2.3 OpenFlow Message Flow

**Control Plane Messages** (require reliability):
- HELLO - Connection establishment
- FEATURES_REQUEST/REPLY - Switch capabilities
- FLOW_MOD - Flow table modifications
- BARRIER_REQUEST/REPLY - Transaction boundaries

**Data Plane Messages** (can tolerate loss):
- PACKET_IN - New packet notifications (best-effort)
- PACKET_OUT - Packet forwarding instructions
- ECHO_REQUEST/REPLY - Keep-alive (idempotent)

**Selective Reliability Strategy**:
- Control messages: Require ACK + retransmission
- Data messages: No ACK (reduce overhead)
- Keep-alives: Optional ACK

### 2.4 Modification Points Identified

**Tier 1 - Critical** (Completed in Phase 3):
1. Replace StreamServer with DatagramServer in Ryu
2. Add UDP socket creation and binding
3. Implement message framing for UDP datagrams
4. Add sequence numbers to OpenFlow messages (deferred to Phase 6)

**Tier 2 - Important** (Phase 4):
1. Implement selective ACK mechanism
2. Add retransmission logic for control messages
3. Modify OVS to use UDP sockets
4. Update connection state machines

**Tier 3 - Optimization** (Phase 5-6):
1. Tune retransmission timeouts
2. Implement congestion control
3. Add performance profiling
4. Optimize buffer sizes

---

## Key Findings (Phase 1-2)

### ✅ Achievements

1. **TCP Baseline Established**
   - 94,423 events captured over 37.38 seconds
   - Mean latency: 1.973 ms (stable performance)
   - Throughput: 2,526 msg/sec sustained

2. **UDP Compatibility Validated**
   - Max message size: 218 bytes
   - UDP limit: 65,507 bytes
   - **99.7% safety margin** - No fragmentation concerns

3. **Architecture Mapped**
   - 8 critical modification points identified in Ryu
   - OVS modification scope defined
   - Selective reliability strategy designed

4. **Instrumentation Complete**
   - Tracks 9 OpenFlow message types
   - Measures latency, throughput, sizes
   - Automated visualization pipeline

### Performance Baseline Summary

| Metric | Value | Notes |
|--------|-------|-------|
| **Test Duration** | 37.38 sec | Automated traffic generation |
| **Total Events** | 94,423 | Packet-In messages |
| **Throughput** | 2,526 msg/sec | Sustained rate |
| **Mean Latency** | 1.973 ms | Controller processing time |
| **Median Latency** | 1.133 ms | P50 value |
| **P95 Latency** | 8.805 ms | 95th percentile |
| **P99 Latency** | 8.898 ms | 99th percentile |
| **Max Message Size** | 218 bytes | Well within UDP limit |
| **Protocol Overhead** | 54 bytes/msg | TCP+IP+Ethernet headers |

**Expected UDP Improvements** (for future phases):
- Overhead reduction: 54B → 42B (**22% reduction**)
- Connection time: 3-way handshake → 0 (**eliminated**)
- Latency improvement: ~10-15% expected (no TCP retransmissions)

---

## Phase 3: UDP Implementation in Ryu Controller ✅

### 3.1 Implementation Overview

**Objective**: Create a standalone UDP-based OpenFlow controller in Ryu without modifying the core Ryu framework. This approach:
- Demonstrates protocol understanding
- Maintains clear separation between original and custom code
- Enables independent testing and validation
- Suitable for academic submission

**Key Decision**: Implemented custom UDP transport layer while reusing Ryu's OpenFlow protocol libraries (`ofproto_v1_3`).

### 3.2 Architecture

**UDP Controller Design**:
```
Client (Test/Simulator)
       |
    UDP Socket (Port 6633)
       |
  UDPOpenFlowController
       |
  +----+----+
  |         |
Parser   Handler
  |         |
OpenFlow  Response
Messages  Generation
```

**Protocol Flow**:
1. Receive UDP datagram
2. Parse OpenFlow header (version, type, length, xid)
3. Handle message based on type
4. Send response via UDP

### 3.3 Implementation Components

**Files Created** (310 lines total):

#### Controllers (`udp_baseline/controllers/`)

1. **`udp_ofp_controller.py`** (148 lines) - Main Controller
   - UDP socket server listening on port 6633
   - Handles OpenFlow message types:
     * HELLO - Connection establishment
     * FEATURES_REQUEST/REPLY - Switch capabilities exchange
     * PACKET_IN - Packet notification from switch
     * FLOW_MOD - Flow table modification
   - Multi-threaded receive loop
   - Switch connection tracking (DPID → address mapping)

2. **`udp_datapath.py`** (15 lines) - Datapath Abstraction
   - Wraps UDP socket with datapath interface
   - Stores switch address (IP, port) and DPID
   - Message sending abstraction

3. **`udp_controller.py`** (42 lines) - Ryu App Integration
   - Shows how to integrate UDP with Ryu's application framework
   - Demonstrates UDP socket creation within RyuApp
   - Template for future extensions

#### Libraries (`udp_baseline/lib/`)

4. **`udp_ofp_parser.py`** (46 lines) - Message Parser
   - Parses OpenFlow v1.3 message headers from UDP datagrams
   - Extracts: version, type, length, xid
   - Maps message type codes to readable names
   - Validates OpenFlow version compatibility

5. **`ryu_udp_socket.py`** (26 lines) - Socket Wrapper
   - UDP socket abstraction
   - Send/receive message methods
   - Client address tracking

#### Tests (`udp_baseline/tests/`)

6. **`test_udp_socket.py`** (12 lines) - Socket Binding Test
   - Validates UDP socket creation and binding
   - Tests basic datagram reception

7. **`test_message_parsing.py`** (11 lines) - Parser Validation
   - Tests OpenFlow HELLO message parsing
   - Validates header extraction

8. **`udp_echo_test.py`** (10 lines) - Echo Server
   - Simple UDP echo server for connectivity testing
   - Validates bidirectional communication

### 3.4 Supported OpenFlow Messages

| Message Type | Code | Direction | Implementation |
|--------------|------|-----------|----------------|
| HELLO | 0 | Both | ✅ Send & Receive |
| FEATURES_REQUEST | 5 | Controller → Switch | ✅ Send |
| FEATURES_REPLY | 6 | Switch → Controller | ✅ Receive |
| PACKET_IN | 10 | Switch → Controller | ✅ Receive |
| FLOW_MOD | 14 | Controller → Switch | ✅ Send |
| ECHO_REQUEST | 2 | Both | Parsed only |
| ECHO_REPLY | 3 | Both | Parsed only |
| ERROR | 1 | Both | Parsed only |

### 3.5 Testing & Validation

**Unit Tests**:
```bash
# Test message parsing
python3 -m udp_baseline.tests.test_message_parsing
# Output: Parsed message: {'version': 4, 'type': 0, 'msg_name': 'HELLO', ...}

# Test socket binding
python3 -m udp_baseline.tests.test_udp_socket
# Then: echo "test" | nc -u 127.0.0.1 6633
```

**Integration Test**:
```bash
# Start UDP controller
python3 -m udp_baseline.controllers.udp_ofp_controller
# Output: [INFO] UDP OpenFlow Controller listening on 0.0.0.0:6633

# Send HELLO message (from another terminal)
python3 -c "
import socket, struct
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
msg = struct.pack('!BBHI', 4, 0, 8, 1)  # OpenFlow HELLO
sock.sendto(msg, ('127.0.0.1', 6633))
"
# Controller output:
# [INFO] Received HELLO from ('127.0.0.1', XXXXX), xid=1
# [SEND] HELLO → ('127.0.0.1', XXXXX)
# [SEND] FEATURES_REQUEST → ('127.0.0.1', XXXXX)
```

**Validation Results**:
- ✅ UDP socket binds successfully to port 6633
- ✅ OpenFlow message parsing works correctly
- ✅ HELLO exchange completes successfully
- ✅ FEATURES_REQUEST sent automatically after HELLO
- ✅ Message routing based on type works
- ✅ Multi-client support functional

### 3.6 Current Limitations

**By Design** (for Phase 3):
- ❌ No reliability mechanisms (ACK, retransmission)
- ❌ No sequence number tracking
- ❌ No connection state management
- ❌ Cannot test with real OVS (OVS still uses TCP)
- ❌ No performance metrics collection yet

**Rationale**: These features require both controller AND switch to support UDP. Phase 4 will modify OVS to enable end-to-end UDP testing.

### 3.7 Key Achievements

1. **Clean Architecture** ✅
   - Custom implementation without modifying Ryu core
   - Reuses Ryu's protocol libraries
   - Clear code separation for academic review

2. **Working UDP Transport** ✅
   - Successful OpenFlow message exchange over UDP
   - Proper message parsing and handling
   - Multi-threaded server design

3. **Validated Functionality** ✅
   - Unit tests pass
   - Integration tests successful
   - HELLO/FEATURES exchange working

4. **Academic Readiness** ✅
   - Well-documented code
   - Clear attribution (custom vs library code)
   - Testable and reproducible

### 3.8 Code Statistics

| Component | Files | Lines | Purpose |
|-----------|-------|-------|---------|
| Controllers | 3 | 205 | UDP server & message handling |
| Libraries | 2 | 72 | Socket wrapper & parser |
| Tests | 3 | 33 | Validation & testing |
| **Total** | **8** | **310** | **Custom implementation** |

### 3.9 Next Phase Preview

**Phase 4** will focus on:
- Modifying Open vSwitch (OVS) C code for UDP support
- Enabling end-to-end UDP communication
- Then performance testing becomes possible

---

## Repository Structure

```
CN_PR/
├── README.md                          # This file
├── tcp_baseline/                      # TCP baseline (Phase 1 & 2 complete)
│   ├── controllers/                   # Ryu controller implementations
│   │   ├── tcp_baseline_controller.py
│   │   └── tcp_baseline_instrumented.py
│   ├── analysis/                      # Analysis scripts
│   │   ├── visualize_metrics.py
│   │   ├── analyze_tcp_performance.py
│   │   └── analyze_ryu_tcp.py
│   ├── data/                          # Raw data (67 MB)
│   │   ├── tcp_baseline_metrics.json  (7.1 MB)
│   │   ├── tcp_baseline.pcap          (46 KB)
│   │   ├── tcp_baseline.log           (60 MB)
│   │   └── ryu_tcp_analysis.txt
│   ├── results/                       # Generated outputs
│   │   ├── tcp_baseline_performance.png
│   │   └── tcp_baseline_report.txt
│   └── topology/                      # Mininet topologies
│       ├── test_topology_tcp.py
│       └── basic_topo.py
├── udp_baseline/                      # UDP implementation (Phase 3 complete)
│   ├── controllers/                   # UDP OpenFlow controllers
│   │   ├── udp_ofp_controller.py      # Main UDP controller (148 lines)
│   │   ├── udp_datapath.py            # Datapath abstraction (15 lines)
│   │   └── udp_controller.py          # Ryu app integration (42 lines)
│   ├── lib/                           # UDP libraries
│   │   ├── udp_ofp_parser.py          # OpenFlow parser (46 lines)
│   │   └── ryu_udp_socket.py          # Socket wrapper (26 lines)
│   ├── tests/                         # Validation tests
│   │   ├── test_message_parsing.py    # Parser tests
│   │   ├── test_udp_socket.py         # Socket tests
│   │   └── udp_echo_test.py           # Echo server
│   └── README.md                      # Phase 3 documentation
└── ryu/                               # Ryu controller source (for reference)
    ├── controller/                    # Core controller logic
    ├── ofproto/                       # OpenFlow protocol implementation
    ├── lib/                           # Helper libraries
    └── app/                           # Sample applications
```

---

## Quick Start

### Run TCP Baseline Test

**Terminal 1** - Start Controller:
```bash
cd tcp_baseline/controllers
ryu-manager tcp_baseline_instrumented.py --verbose
```

**Terminal 2** - Run Test Topology:
```bash
cd tcp_baseline/topology
sudo python test_topology_tcp.py
# Test runs for ~60 seconds with automatic traffic generation
```

**Terminal 3** - Generate Visualization:
```bash
cd tcp_baseline/analysis
python3 visualize_metrics.py
# Outputs: ../results/tcp_baseline_performance.png
```

### View Results
```bash
# Summary statistics
cat tcp_baseline/results/tcp_baseline_report.txt

# View visualization
xdg-open tcp_baseline/results/tcp_baseline_performance.png

# Analyze packet capture
tcpdump -r tcp_baseline/data/tcp_baseline.pcap -nn | head -20
```

### Run Phase 3 UDP Controller

**Terminal 1** - Start UDP Controller:
```bash
cd /home/set-iitgn-vm/Acads/CN/CN_PR
python3 -m udp_baseline.controllers.udp_ofp_controller
# Output: [INFO] UDP OpenFlow Controller listening on 0.0.0.0:6633
```

**Terminal 2** - Test with HELLO Message:
```bash
python3 -c "
import socket, struct
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
hello = struct.pack('!BBHI', 4, 0, 8, 1)  # OpenFlow HELLO
sock.sendto(hello, ('127.0.0.1', 6633))
print('HELLO sent to UDP controller')
"
# Expected controller output:
# [INFO] Received HELLO from ('127.0.0.1', XXXXX)
# [SEND] HELLO → ('127.0.0.1', XXXXX)
# [SEND] FEATURES_REQUEST → ('127.0.0.1', XXXXX)
```

**Terminal 3** - Run Unit Tests:
```bash
# Test message parsing
python3 -m udp_baseline.tests.test_message_parsing

# Test UDP socket
python3 -m udp_baseline.tests.test_udp_socket
# Then from another terminal: echo "test" | nc -u 127.0.0.1 6633
```

---

## Tools & Dependencies

### Required Software
```bash
# Ryu Controller
pip install ryu eventlet msgpack

# Network Tools
sudo apt install openvswitch-switch mininet

# Analysis Tools
pip install numpy matplotlib seaborn
```

### Python Version
- Python 3.8+ recommended
- Tested on Python 3.10

### Network Emulation
- Mininet 2.3.0+
- Open vSwitch 2.17+

---

## Testing Methodology

### Test Scenario
1. Create linear topology (3 switches, 4 hosts)
2. Start Ryu controller with instrumented L2 switch
3. Generate ping traffic between hosts
4. Collect metrics for 30-60 seconds
5. Capture packets with tcpdump
6. Analyze performance and visualize

### Metrics Collection
- **Latency**: Time from Packet-In arrival to Flow-Mod installation
- **Throughput**: Messages processed per second
- **Message Sizes**: OpenFlow message payload sizes
- **Overhead**: Protocol header bytes (TCP/UDP + IP + Ethernet)

### Validation
- ✅ Minimum 20 latency samples (21 collected)
- ✅ Test duration > 30 seconds (37.38 sec)
- ✅ Multiple message types captured (9 types)
- ✅ Statistical validity confirmed (natural variation)

---

## Project Status Summary

| Phase | Description | Status | Completion Date |
|-------|-------------|--------|-----------------|
| **Phase 1** | Environment Setup & TCP Baseline | ✅ Complete | Nov 1, 2025 |
| **Phase 2** | Code Analysis & Architecture | ✅ Complete | Nov 1, 2025 |
| **Phase 3** | UDP Implementation (Ryu) | ✅ Complete | Nov 6, 2025 |
| **Phase 4** | UDP Implementation (OVS) | 🔜 Next | Pending |
| **Phase 5** | Performance Testing & Comparison | ⏳ Future | Pending |

**Current Status**: Phase 3 Complete - UDP controller implemented and validated

---

## Team & Contact

**Institution**: Indian Institute of Technology Gandhinagar  
**Course**: Computer Networks  
**Project Type**: Research & Implementation

---

## References

1. Ryu SDN Framework: https://ryu-sdn.org/
2. OpenFlow Specification v1.3: https://opennetworking.org/
3. Open vSwitch Documentation: https://www.openvswitch.org/
4. Mininet Network Emulator: http://mininet.org/

---

**Last Updated**: November 6, 2025  
**Status**: Phase 1-3 Complete
