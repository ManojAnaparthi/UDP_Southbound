#!/bin/bash
# Run OpenFlow handshake verification test in correct order

echo "========================================"
echo "OpenFlow Handshake Test Runner"
echo "========================================"
echo

# Step 1: Clear any existing controller
echo "[1/3] Clearing existing controller..."
sudo ovs-vsctl del-controller test-br 2>/dev/null
echo "✓ Controller cleared"
echo

# Step 2: Start handshake verification controller
echo "[2/3] Starting handshake verification controller..."
echo "      (Controller will bind to UDP 127.0.0.1:6653)"
echo

sudo python3.10 tests/verify_handshake.py &
CONTROLLER_PID=$!

echo "      Controller PID: $CONTROLLER_PID"
echo "      Waiting 2 seconds for controller to start..."
sleep 2
echo

# Step 3: Connect OVS to controller
echo "[3/3] Connecting OVS bridge to controller..."
sudo ovs-vsctl set-controller test-br udp:127.0.0.1:6653
echo "✓ OVS connected to udp:127.0.0.1:6653"
echo

# Wait for controller to finish or user to interrupt
echo "========================================"
echo "Waiting for handshake to complete..."
echo "Press Ctrl+C to stop"
echo "========================================"
echo

wait $CONTROLLER_PID
EXIT_CODE=$?

echo
echo "========================================"
echo "Test completed with exit code: $EXIT_CODE"
echo "========================================"

exit $EXIT_CODE
