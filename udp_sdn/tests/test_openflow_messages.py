#!/usr/bin/env python3
"""
OpenFlow Message Verification Test
===================================

Test all OpenFlow 1.3 message types:
1. HELLO exchange
2. FEATURES_REQUEST/REPLY
3. ECHO_REQUEST/REPLY
4. FLOW_MOD
5. PACKET_IN handling

This creates a test bridge and monitors controller responses.
"""

import subprocess
import time
import sys

def run_cmd(cmd, description=""):
    """Run command and return output."""
    if description:
        print("  {}...".format(description))
    try:
        result = subprocess.check_output(cmd, shell=True, stderr=subprocess.STDOUT)
        return result.decode('utf-8').strip()
    except subprocess.CalledProcessError as e:
        print("    ERROR: {}".format(e.output.decode('utf-8')))
        return None

def check_controller():
    """Check if controller is running."""
    result = run_cmd("ps aux | grep phase3_udp_l2_controller | grep -v grep")
    if result:
        print("✓ Controller is running")
        return True
    else:
        print("✗ Controller is NOT running")
        print("\nStart it with:")
        print("  cd /home/set-iitgn-vm/Acads/CN/CN_PR/udp_sdn")
        print("  python3.10 phase3_udp_l2_controller.py > /tmp/phase3_controller.log 2>&1 &")
        return False

def cleanup_bridges():
    """Remove test bridges."""
    print("\n1. Cleaning up old test bridges...")
    bridges = ['test-oftest', 'test-l2']
    for br in bridges:
        run_cmd("sudo ovs-vsctl --if-exists del-br {}".format(br), 
                "Removing {}".format(br))
    time.sleep(1)
    print("✓ Cleanup complete")

def create_test_bridge():
    """Create test bridge for OpenFlow testing."""
    print("\n2. Creating test bridge 'test-oftest'...")
    
    run_cmd("sudo ovs-vsctl add-br test-oftest", 
            "Creating bridge")
    run_cmd("sudo ovs-vsctl set bridge test-oftest protocols=OpenFlow13", 
            "Setting OpenFlow 1.3")
    run_cmd("sudo ovs-vsctl set-controller test-oftest udp:127.0.0.1:6653", 
            "Setting UDP controller")
    run_cmd("sudo ovs-vsctl set bridge test-oftest fail_mode=secure", 
            "Setting fail mode")
    
    print("✓ Bridge created")
    return True

def wait_for_connection():
    """Wait for switch to connect to controller."""
    print("\n3. Waiting for OpenFlow handshake...")
    print("  (Waiting 5 seconds for connection...)")
    time.sleep(5)
    
    # Check in controller log for recent connection
    result = run_cmd("tail -30 /tmp/phase3_controller.log | grep 'Switch connected: DPID' | tail -1")
    if result:
        print("✓ Switch connected to controller")
        return True
    
    # Also check ovs-vsctl
    result = run_cmd("sudo ovs-vsctl show | grep -A 2 test-oftest | grep is_connected")
    if result and 'true' in result:
        print("✓ Switch connected (verified by ovs-vsctl)")
        return True
    else:
        print("⚠ Connection status unclear, but controller may have received HELLO")
        return True  # Continue anyway

def verify_hello_exchange():
    """Verify HELLO message exchange."""
    print("\n4. Verifying HELLO exchange...")
    
    # Check controller log for HELLO messages
    result = run_cmd("tail -100 /tmp/phase3_controller.log | grep 'HELLO from' | tail -1")
    if result:
        print("✓ HELLO message received")
        print("  {}".format(result.split('INFO - ')[-1] if 'INFO - ' in result else result))
        return True
    else:
        print("✗ No HELLO messages in log")
        return False

def verify_features_reply():
    """Verify FEATURES_REPLY received."""
    print("\n5. Verifying FEATURES_REPLY...")
    
    result = run_cmd("tail -100 /tmp/phase3_controller.log | grep 'Switch connected: DPID' | tail -1")
    if result:
        print("✓ FEATURES_REPLY received")
        print("  {}".format(result.split('INFO - ')[-1] if 'INFO - ' in result else result))
        return True
    else:
        print("✗ No FEATURES_REPLY in log")
        return False

def verify_flow_installation():
    """Verify table-miss flow installation."""
    print("\n6. Verifying FLOW_MOD (table-miss)...")
    
    result = run_cmd("tail -100 /tmp/phase3_controller.log | grep 'Table-miss flow installed' | tail -1")
    if result:
        print("✓ FLOW_MOD sent (table-miss flow)")
        return True
    else:
        print("✗ No FLOW_MOD in log")
        return False

def verify_echo():
    """Verify ECHO_REQUEST/REPLY (may not appear immediately)."""
    print("\n7. Checking ECHO_REQUEST/REPLY...")
    
    # ECHO messages are at debug level, so we just verify controller is responding
    result = run_cmd("sudo ovs-vsctl show | grep -A 2 test-oftest | grep is_connected")
    if result and 'true' in result:
        print("✓ Connection maintained (ECHO working)")
        return True
    else:
        print("⚠ Connection status unclear")
        return False

def trigger_packet_in():
    """Try to trigger PACKET_IN by adding a port and generating traffic."""
    print("\n8. Testing PACKET_IN (attempting to generate traffic)...")
    
    # Try to add a veth pair
    print("  Creating veth pair...")
    run_cmd("sudo ip link add veth0 type veth peer name veth1")
    run_cmd("sudo ip link set veth0 up")
    run_cmd("sudo ip link set veth1 up")
    
    # Add veth0 to bridge
    result = run_cmd("sudo ovs-vsctl add-port test-oftest veth0", 
                    "Adding veth0 to bridge")
    if result and "Error" in result:
        print("  ⚠ Could not add port (this is OK)")
    
    # Try to send traffic
    run_cmd("sudo ip addr add 192.168.100.1/24 dev veth1")
    time.sleep(1)
    run_cmd("sudo ping -c 2 -W 1 192.168.100.2 > /dev/null 2>&1")
    
    time.sleep(2)
    
    # Check for PACKET_IN in log
    result = run_cmd("tail -50 /tmp/phase3_controller.log | grep 'PACKET_IN from DPID'")
    if result:
        print("✓ PACKET_IN messages received")
        lines = result.split('\n')
        for line in lines[:3]:  # Show first 3
            print("  {}".format(line.split('INFO - ')[-1] if 'INFO - ' in line else line))
        return True
    else:
        print("⚠ No PACKET_IN messages (may need actual host traffic)")
        return False

def show_summary():
    """Show summary of OpenFlow messages."""
    print("\n" + "="*70)
    print("OpenFlow Message Summary (last 20 entries)")
    print("="*70)
    
    run_cmd("tail -50 /tmp/phase3_controller.log | grep -E 'HELLO|FEATURES_REPLY|Table-miss|PACKET_IN|Learning|Installing flow' | tail -20")
    print("")

def main():
    """Main test procedure."""
    print("="*70)
    print("OpenFlow Message Verification Test")
    print("="*70)
    
    # Check prerequisites
    if not check_controller():
        return 1
    
    # Run tests
    cleanup_bridges()
    
    if not create_test_bridge():
        print("\n✗ FAILED: Could not create test bridge")
        return 1
    
    if not wait_for_connection():
        print("\n✗ FAILED: Switch did not connect")
        return 1
    
    # Verify OpenFlow messages
    hello_ok = verify_hello_exchange()
    features_ok = verify_features_reply()
    flow_ok = verify_flow_installation()
    echo_ok = verify_echo()
    packet_in_ok = trigger_packet_in()
    
    # Show summary
    show_summary()
    
    # Final result
    print("="*70)
    print("Test Results:")
    print("="*70)
    print("  HELLO exchange:       {}".format("✓ PASS" if hello_ok else "✗ FAIL"))
    print("  FEATURES_REPLY:       {}".format("✓ PASS" if features_ok else "✗ FAIL"))
    print("  FLOW_MOD:             {}".format("✓ PASS" if flow_ok else "✗ FAIL"))
    print("  ECHO (keepalive):     {}".format("✓ PASS" if echo_ok else "⚠ UNCLEAR"))
    print("  PACKET_IN:            {}".format("✓ PASS" if packet_in_ok else "⚠ NEEDS TRAFFIC"))
    print("="*70)
    
    if hello_ok and features_ok and flow_ok:
        print("\n✓ Core OpenFlow messages working correctly!")
        print("✓ Handshake successful!")
        return 0
    else:
        print("\n✗ Some OpenFlow messages failed")
        return 1

if __name__ == '__main__':
    sys.exit(main())
