#!/bin/bash
# Phase 3: Simple L2 Learning Test

echo "=========================================="
echo "Phase 3: L2 Learning Test"
echo "=========================================="
echo ""

echo "Prerequisites:"
echo "  - Phase 3 controller should be running"
echo "  - Check with: ps aux | grep phase3"
echo ""

# Check if controller is running
if ! ps aux | grep -v grep | grep phase3_udp_l2_controller > /dev/null; then
    echo "ERROR: Phase 3 controller not running!"
    echo "Start it with:"
    echo "  cd /home/set-iitgn-vm/Acads/CN/CN_PR/udp_sdn"
    echo "  python3.10 phase3_udp_l2_controller.py > /tmp/phase3_controller.log 2>&1 &"
    exit 1
fi

echo "✓ Controller is running"
echo ""

# Create test bridge if it doesn't exist
if ! sudo ovs-vsctl br-exists test-l2; then
    echo "Creating test bridge 'test-l2'..."
    sudo ovs-vsctl add-br test-l2
    sudo ovs-vsctl set bridge test-l2 protocols=OpenFlow13
    sudo ovs-vsctl set-controller test-l2 udp:127.0.0.1:6653
    sudo ovs-vsctl set bridge test-l2 fail_mode=secure
    echo "✓ Bridge created"
else
    echo "✓ Bridge 'test-l2' already exists"
fi

echo ""
echo "Waiting for handshake (3 seconds)..."
sleep 3

echo ""
echo "=========================================="
echo "Generating test traffic..."
echo "=========================================="

# Add a port to trigger PACKET_IN
echo "Adding internal port to generate traffic..."
sudo ovs-vsctl add-port test-l2 test-port -- set interface test-port type=internal
sudo ip link set test-port up
sudo ip addr add 10.10.10.1/24 dev test-port

echo ""
echo "Sending ARP packet to trigger PACKET_IN..."
sudo arping -c 2 -I test-port 10.10.10.2 2>/dev/null || true

echo ""
echo "=========================================="
echo "Check controller log for L2 learning:"
echo "=========================================="
echo ""
tail -30 /tmp/phase3_controller.log | grep -A 5 -B 2 "PACKET_IN\|Learning\|Installing flow"

echo ""
echo "=========================================="
echo "Test complete!"
echo "=========================================="
echo ""
echo "To see full log:"
echo "  tail -f /tmp/phase3_controller.log"
echo ""
echo "To cleanup:"
echo "  sudo ovs-vsctl del-br test-l2"
echo ""
