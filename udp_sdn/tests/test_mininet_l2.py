#!/usr/bin/env python2
"""
Mininet L2 Learning Test
=========================

Test L2 learning switch functionality:
- Create 2-host, 1-switch topology
- Send pings to trigger PACKET_IN
- Verify MAC learning
- Verify flow installation
"""

from mininet.net import Mininet
from mininet.node import OVSSwitch
from mininet.log import setLogLevel, info
from mininet.cli import CLI
import subprocess
import time
import os

def cleanup():
    """Clean up any existing Mininet state."""
    info('*** Cleaning up old Mininet state\n')
    devnull = open(os.devnull, 'w')
    subprocess.call(['mn', '-c'], stderr=devnull, stdout=devnull)
    devnull.close()
    time.sleep(2)

def test_l2_learning():
    """Test L2 learning with Mininet."""
    setLogLevel('info')
    
    cleanup()
    
    info('*** Creating network\n')
    net = Mininet(switch=OVSSwitch, controller=None, autoSetMacs=True, waitConnected=False)
    
    info('*** Adding hosts\n')
    h1 = net.addHost('h1', ip='10.0.0.1/24', mac='00:00:00:00:00:01')
    h2 = net.addHost('h2', ip='10.0.0.2/24', mac='00:00:00:00:00:02')
    
    info('*** Adding switch\n')
    s1 = net.addSwitch('s1', protocols='OpenFlow13')
    
    info('*** Creating links\n')
    net.addLink(h1, s1)
    net.addLink(h2, s1)
    
    info('*** Starting network\n')
    net.start()
    
    info('*** Configuring UDP controller (udp:127.0.0.1:6653)\n')
    subprocess.call(['ovs-vsctl', 'set-controller', 's1', 'udp:127.0.0.1:6653'])
    subprocess.call(['ovs-vsctl', 'set', 'bridge', 's1', 'fail_mode=secure'])
    
    info('*** Waiting for controller handshake (5 seconds)...\n')
    time.sleep(5)
    
    info('\n' + '='*70 + '\n')
    info('*** Running L2 Learning Tests\n')
    info('='*70 + '\n\n')
    
    info('Test 1: Ping h1 -> h2 (will trigger PACKET_IN and MAC learning)\n')
    info('-'*70 + '\n')
    result = h1.cmd('ping -c 3 -i 0.5 10.0.0.2')
    info(result)
    
    info('\nWaiting 2 seconds for flow installation...\n')
    time.sleep(2)
    
    info('\nTest 2: Ping h2 -> h1 (should use installed flows)\n')
    info('-'*70 + '\n')
    result = h2.cmd('ping -c 3 -i 0.5 10.0.0.1')
    info(result)
    
    info('\n' + '='*70 + '\n')
    info('*** Checking Controller Log\n')
    info('='*70 + '\n')
    
    # Show L2 learning activity
    info('\n--- MAC Learning Events ---\n')
    subprocess.call(['tail', '-100', '/tmp/phase3_controller.log'])
    subprocess.call('tail -100 /tmp/phase3_controller.log | grep -E "Learning|PACKET_IN from DPID" | tail -10', shell=True)
    
    info('\n--- Flow Installation Events ---\n')
    subprocess.call('tail -100 /tmp/phase3_controller.log | grep -E "Installing flow|Destination known" | tail -10', shell=True)
    
    info('\n' + '='*70 + '\n')
    info('*** Test Summary\n')
    info('='*70 + '\n')
    info('If you see:\n')
    info('  - "PACKET_IN from DPID" messages\n')
    info('  - "Learning: <MAC> at port X" messages\n')
    info('  - "Installing flow" messages\n')
    info('Then L2 learning is working!\n\n')
    
    info('*** Entering CLI (optional - type "exit" to quit)\n')
    info('Commands to try:\n')
    info('  h1 ping -c 1 h2    # Another ping\n')
    info('  exit               # Quit\n\n')
    
    CLI(net)
    
    info('*** Stopping network\n')
    net.stop()

if __name__ == '__main__':
    try:
        test_l2_learning()
    except KeyboardInterrupt:
        info('\n*** Interrupted, cleaning up...\n')
        subprocess.call(['mn', '-c'])
