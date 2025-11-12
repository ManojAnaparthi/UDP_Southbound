#!/bin/bash
# Monitor OVS logs for PACKET_IN and other OpenFlow messages

echo "============================================"
echo "OVS Log Monitor - Looking for PACKET_IN"
echo "============================================"
echo ""
echo "This will tail OVS logs and highlight PACKET_IN messages"
echo "Press Ctrl+C to stop"
echo ""

# Find OVS log file
OVS_LOG="/var/log/openvswitch/ovs-vswitchd.log"

if [ ! -f "$OVS_LOG" ]; then
    echo "ERROR: OVS log not found at $OVS_LOG"
    echo "Looking for alternatives..."
    
    # Try other locations
    if [ -f "/usr/local/var/log/openvswitch/ovs-vswitchd.log" ]; then
        OVS_LOG="/usr/local/var/log/openvswitch/ovs-vswitchd.log"
    elif [ -f "ovs/tests/ovs-vswitchd.log" ]; then
        OVS_LOG="ovs/tests/ovs-vswitchd.log"
    else
        echo "Cannot find OVS log file"
        exit 1
    fi
fi

echo "Monitoring: $OVS_LOG"
echo ""

# Tail log with highlighting
sudo tail -f "$OVS_LOG" | grep --line-buffered -E "PACKET_IN|packet_in|FLOW_MOD|flow_mod|received|sent|udp|UDP" | \
    while IFS= read -r line; do
        if [[ "$line" == *"PACKET_IN"* ]] || [[ "$line" == *"packet_in"* ]]; then
            echo -e "\033[1;32m$line\033[0m"  # Green for PACKET_IN
        elif [[ "$line" == *"FLOW_MOD"* ]] || [[ "$line" == *"flow_mod"* ]]; then
            echo -e "\033[1;33m$line\033[0m"  # Yellow for FLOW_MOD
        elif [[ "$line" == *"error"* ]] || [[ "$line" == *"Error"* ]] || [[ "$line" == *"ERROR"* ]]; then
            echo -e "\033[1;31m$line\033[0m"  # Red for errors
        else
            echo "$line"
        fi
    done
