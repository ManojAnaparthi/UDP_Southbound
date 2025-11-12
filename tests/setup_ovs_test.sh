#!/bin/bash
# Setup OVS test environment without Mininet

set -e

echo "============================================"
echo "Setting up OVS test environment"
echo "============================================"

# Start OVS if not running
echo "Starting OVS daemons..."
sudo /usr/share/openvswitch/scripts/ovs-ctl start 2>&1 | grep -i "started\|already"

# Wait a bit for OVS to start
sleep 2

# Clean up any existing bridge
echo "Cleaning up existing bridge..."
sudo ovs-vsctl --if-exists del-br test-br

# Create new bridge
echo "Creating test bridge..."
sudo ovs-vsctl add-br test-br

# Set OpenFlow version to 1.3
echo "Setting OpenFlow version to 1.3..."
sudo ovs-vsctl set bridge test-br protocols=OpenFlow13

# Set controller to UDP
echo "Setting UDP controller (127.0.0.1:6653)..."
sudo ovs-vsctl set-controller test-br udp:127.0.0.1:6653

# Set fail mode to secure (only use controller flows)
echo "Setting fail mode to secure..."
sudo ovs-vsctl set-fail-mode test-br secure

# Show bridge info
echo ""
echo "Bridge configuration:"
sudo ovs-vsctl show

echo ""
echo "Controller connection:"
sudo ovs-vsctl get-controller test-br

echo ""
echo "OpenFlow version:"
sudo ovs-vsctl get bridge test-br protocols

echo ""
echo "============================================"
echo "OVS test bridge ready!"
echo "Bridge: test-br"
echo "Controller: udp:127.0.0.1:6653"
echo "Protocol: OpenFlow13"
echo "============================================"
