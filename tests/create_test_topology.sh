#!/bin/bash
# Create virtual interfaces and connect to OVS bridge for testing

set -e

echo "============================================"
echo "Creating test topology with OVS"
echo "============================================"

# Create two network namespaces to simulate hosts
echo "Creating network namespaces..."
sudo ip netns add h1 2>/dev/null || echo "  h1 already exists"
sudo ip netns add h2 2>/dev/null || echo "  h2 already exists"

# Create veth pairs
echo "Creating veth pairs..."
sudo ip link add veth1 type veth peer name veth1-br 2>/dev/null || echo "  veth1 already exists"
sudo ip link add veth2 type veth peer name veth2-br 2>/dev/null || echo "  veth2 already exists"

# Move one end to namespaces
echo "Moving interfaces to namespaces..."
sudo ip link set veth1 netns h1 2>/dev/null || true
sudo ip link set veth2 netns h2 2>/dev/null || true

# Add ports to bridge
echo "Adding ports to bridge..."
sudo ovs-vsctl --may-exist add-port test-br veth1-br
sudo ovs-vsctl --may-exist add-port test-br veth2-br

# Configure interfaces in namespaces
echo "Configuring host interfaces..."
sudo ip netns exec h1 ip addr add 10.0.0.1/24 dev veth1 2>/dev/null || true
sudo ip netns exec h2 ip addr add 10.0.0.2/24 dev veth2 2>/dev/null || true

# Bring up interfaces
echo "Bringing up interfaces..."
sudo ip netns exec h1 ip link set dev veth1 up
sudo ip netns exec h2 ip link set dev veth2 up
sudo ip link set dev veth1-br up
sudo ip link set dev veth2-br up

echo ""
echo "============================================"
echo "Test topology ready!"
echo "============================================"
echo "Bridge: test-br"
echo "Host 1 (h1): 10.0.0.1 - veth1"
echo "Host 2 (h2): 10.0.0.2 - veth2"
echo ""
echo "Test with:"
echo "  sudo ip netns exec h1 ping -c 3 10.0.0.2"
echo "============================================"

# Show configuration
echo ""
echo "Bridge ports:"
sudo ovs-vsctl list-ports test-br
