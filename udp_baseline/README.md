# Phase 3 – UDP-Based OpenFlow Extension

This module extends the SDN controller (based on **Ryu**) to support **OpenFlow-like communication over UDP**. 
It includes a lightweight UDP controller, datapath parser, socket utilities, and a complete test suite.

---

## Directory Structure

udp_baseline/
├── controllers/
│ ├── udp_controller.py # Main UDP controller logic
│ ├── udp_ofp_controller.py # Handles OpenFlow message types over UDP
│ └── udp_datapath.py # Simulated UDP datapath (switch-side logic)
│
├── lib/
│ ├── ryu_udp_socket.py # UDP socket wrapper for sending/receiving packets
│ ├── udp_ofp_parser.py # Parses OpenFlow v1.3 messages over UDP
│ └── udp_echo_test.py # Simple echo utility for UDP testing
│
├── tests/
│ ├── test_udp_socket.py # Unit test for UDP socket layer
│ ├── test_message_parsing.py # Tests message parsing (HELLO, etc.)
│ └── udp_echo_test.py # Functional test for echo communication
│
└── README.md # This file

## Run this first before running any files
export PYTHONPATH=$PWD

## Test UDP socket creation

Run this standalone to confirm the UDP socket binds to port 6633 and receives data:
python udp_baseline/tests/test_udp_socket.py

Then, from another terminal, send a test message:
echo "hello" | nc -u 127.0.0.1 6633

Expected: it prints
Received 5 bytes from ('127.0.0.1', XXXXX)

## Test UDP echo

Run this as a simple echo server:
python udp_baseline/tests/udp_echo_test.py

Then send a UDP packet using:
echo "ping" | nc -u 127.0.0.1 6633

You’ll see “Echo: 4 bytes from (127.0.0.1, XXXXX)”.


## Running the UDP Controller

Start the UDP controller:
python -m udp_baseline.controllers.udp_ofp_controller

Expected output:
UDP OpenFlow Controller listening on 0.0.0.0:6633


Then, from another terminal, send a sample OpenFlow HELLO message:
python - <<'PY'
import socket, struct
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
msg = struct.pack('!BBHI', 4, 0, 8, 1)   # version=4, type=HELLO, len=8, xid=1
sock.sendto(msg, ('127.0.0.1', 6633))
print("HELLO sent")
PY

Controller output should show:
Received OpenFlow message: type=0, len=8, xid=1
HELLO received from ('127.0.0.1', ...)
HELLO sent to ('127.0.0.1', ...)
FEATURES_REQUEST sent to ('127.0.0.1', ...)

## Test message parsing

Test your OpenFlow parser independently:
python udp_baseline/tests/test_message_parsing.py

Expected output:
Parsed message: <ryu.ofproto.ofproto_v1_3_parser.OFPHello object ...>
