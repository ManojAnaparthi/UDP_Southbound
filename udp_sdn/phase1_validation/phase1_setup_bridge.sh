#!/bin/bash
# Phase 1: OVS UDP Validation Test Script

echo "=========================================="
echo "Phase 1: OVS UDP Validation Test"
echo "=========================================="
echo ""

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Bridge name
BRIDGE="br-udp-test"

echo "Step 1: Checking if OVS is installed..."
if ! command -v ovs-vsctl &> /dev/null; then
    echo -e "${RED}ERROR: ovs-vsctl not found. Please install openvswitch-switch${NC}"
    exit 1
fi
echo -e "${GREEN}✓ OVS is installed${NC}"
echo ""

echo "Step 2: Cleaning up any existing bridge..."
sudo ovs-vsctl --if-exists del-br $BRIDGE 2>/dev/null
sleep 1
echo -e "${GREEN}✓ Cleanup complete${NC}"
echo ""

echo "Step 3: Creating test bridge '$BRIDGE'..."
sudo ovs-vsctl add-br $BRIDGE
if [ $? -ne 0 ]; then
    echo -e "${RED}ERROR: Failed to create bridge${NC}"
    exit 1
fi
echo -e "${GREEN}✓ Bridge created${NC}"
echo ""

echo "Step 4: Setting OpenFlow version to 1.3..."
sudo ovs-vsctl set bridge $BRIDGE protocols=OpenFlow13
echo -e "${GREEN}✓ OpenFlow 1.3 configured${NC}"
echo ""

echo "Step 5: Configuring UDP controller..."
sudo ovs-vsctl set-controller $BRIDGE udp:127.0.0.1:6653
if [ $? -ne 0 ]; then
    echo -e "${RED}ERROR: Failed to set controller${NC}"
    exit 1
fi
echo -e "${GREEN}✓ Controller configured (udp:127.0.0.1:6653)${NC}"
echo ""

echo "Step 6: Setting fail mode to secure..."
sudo ovs-vsctl set bridge $BRIDGE fail_mode=secure
echo -e "${GREEN}✓ Fail mode set${NC}"
echo ""

echo "Step 7: Verifying configuration..."
echo "----------------------------------------"
sudo ovs-vsctl show
echo "----------------------------------------"
echo ""

echo "=========================================="
echo "Setup Complete!"
echo "=========================================="
echo ""
echo -e "${YELLOW}Next Steps:${NC}"
echo "1. In another terminal, run:"
echo "   cd /home/set-iitgn-vm/Acads/CN/CN_PR/udp_sdn"
echo "   python3 phase1_udp_listener.py"
echo ""
echo "2. The listener should receive:"
echo "   - HELLO messages (OpenFlow handshake)"
echo "   - ECHO_REQUEST messages (keepalive)"
echo ""
echo "3. To generate PACKET_IN messages, add a port:"
echo "   sudo ovs-vsctl add-port $BRIDGE veth0"
echo ""
echo "4. To cleanup when done:"
echo "   sudo ovs-vsctl del-br $BRIDGE"
echo ""
