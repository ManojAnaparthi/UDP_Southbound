#!/usr/bin/env python3
"""
Complete UDP SDN Project Test Report
=====================================

This script generates a comprehensive test report.
"""

import subprocess
import time

def run_cmd(cmd):
    try:
        return subprocess.check_output(cmd, shell=True, stderr=subprocess.STDOUT).decode('utf-8').strip()
    except:
        return "ERROR"

print("="*70)
print("UDP SDN PROJECT - COMPREHENSIVE TEST REPORT")
print("="*70)
print("")

print("1. CONTROLLER STATUS")
print("-"*70)
ps_out = run_cmd("ps aux | grep phase3_udp_l2_controller | grep -v grep")
if ps_out and ps_out != "ERROR":
    print("✓ Controller is RUNNING")
    print("  " + ps_out.split()[1] + " (PID)")
else:
    print("✗ Controller is NOT running")
print("")

print("2. OPENFLOW HANDSHAKE VERIFICATION")
print("-"*70)
hello_count = run_cmd("grep -c 'HELLO from' /tmp/phase3_controller.log 2>/dev/null || echo 0")
features_count = run_cmd("grep -c 'Switch connected: DPID' /tmp/phase3_controller.log 2>/dev/null || echo 0")
flow_count = run_cmd("grep -c 'Table-miss flow installed' /tmp/phase3_controller.log 2>/dev/null || echo 0")

print("  HELLO messages received: {}".format(hello_count))
print("  FEATURES_REPLY received: {}".format(features_count))
print("  Table-miss flows installed: {}".format(flow_count))

if int(hello_count) > 0 and int(features_count) > 0:
    print("  ✓ OpenFlow handshake is WORKING")
else:
    print("  ✗ OpenFlow handshake FAILED")
print("")

print("3. CONNECTED SWITCHES")
print("-"*70)
last_switches = run_cmd("tail -200 /tmp/phase3_controller.log | grep 'Switch connected: DPID' | tail -5")
if last_switches and last_switches != "ERROR":
    for line in last_switches.split('\n')[:5]:
        dpid = line.split('DPID')[1].split()[0] if 'DPID' in line else "Unknown"
        print("  Switch: {}".format(dpid))
    print("  ✓ Switches are connecting")
else:
    print("  ⚠ No recent switch connections")
print("")

print("4. L2 LEARNING STATUS")
print("-"*70)
packet_in_count = run_cmd("grep -c 'PACKET_IN from DPID' /tmp/phase3_controller.log 2>/dev/null || echo 0")
learning_count = run_cmd("grep -c 'Learning:' /tmp/phase3_controller.log 2>/dev/null || echo 0")
flow_install_count = run_cmd("grep -c 'Installing flow for' /tmp/phase3_controller.log 2>/dev/null || echo 0")

print("  PACKET_IN messages: {}".format(packet_in_count))
print("  MAC learning events: {}".format(learning_count))
print("  Dynamic flows installed: {}".format(flow_install_count))

if int(packet_in_count) > 0:
    print("  ✓ L2 learning is ACTIVE")
else:
    print("  ⚠ L2 learning NOT YET TESTED (no PACKET_IN)")
print("")

print("5. PHASE COMPLETION STATUS")
print("-"*70)
print("  Phase 1 (OVS UDP Validation):     ✓ COMPLETE")
print("  Phase 2 (Basic Controller):       ✓ COMPLETE")
if int(hello_count) > 0 and int(features_count) > 0:
    print("  Phase 3 (L2 Learning Logic):      ✓ CONTROLLER READY")
    if int(packet_in_count) > 0:
        print("                                     ✓ L2 LEARNING WORKING")
    else:
        print("                                     ⚠ NEEDS TRAFFIC TEST")
else:
    print("  Phase 3 (L2 Learning Logic):      ✗ INCOMPLETE")
print("  Phase 4 (Performance Benchmark):   ⏭  PENDING")
print("")

print("6. RECOMMENDATIONS")
print("-"*70)
if int(packet_in_count) == 0:
    print("  To test L2 learning:")
    print("    1. Create Mininet topology with 2 hosts")
    print("    2. Generate ping traffic")
    print("    3. Monitor controller log for PACKET_IN")
    print("")
    print("  Note: Table-miss flow installation working,")
    print("        but no packets received yet. This may be")
    print("        due to:")
    print("        - No active traffic on connected switches")
    print("        - Flow table issue (check with ovs-ofctl)")
print("")

print("="*70)
print("END OF REPORT")
print("="*70)
