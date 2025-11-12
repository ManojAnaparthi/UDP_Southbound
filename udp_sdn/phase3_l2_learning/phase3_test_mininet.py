#!/usr/bin/env python
"""
Phase 3: Mininet Test Topology
===============================

Simple 2-host, 1-switch topology to test L2 learning.

Topology:
  h1 (10.0.0.1) --- s1 --- h2 (10.0.0.2)
"""

from mininet.net import Mininet
from mininet.node import OVSSwitch, RemoteController
from mininet.cli import CLI
from mininet.log import setLogLevel, info
import time

def test_topology():
    """Create and test topology."""
    setLogLevel('info')
    
    info('*** Creating network\n')
    net = Mininet(switch=OVSSwitch, controller=None, autoSetMacs=True)
    
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
    
    info('*** Configuring UDP controller\n')
    import subprocess
    subprocess.call(['ovs-vsctl', 'set-controller', 's1', 'udp:127.0.0.1:6653'])
    subprocess.call(['ovs-vsctl', 'set', 'bridge', 's1', 'fail_mode=secure'])
    
    info('*** Waiting for controller connection (5 seconds)...\n')
    time.sleep(5)
    
    info('\n*** Testing L2 Learning ***\n')
    info('Test 1: h1 -> h2 ping (should trigger learning)\n')
    h1.cmd('ping -c 3 10.0.0.2')
    
    info('\nTest 2: h2 -> h1 ping (should use installed flows)\n')
    h2.cmd('ping -c 3 10.0.0.1')
    
    info('\n*** Tests complete. Check controller log at /tmp/phase3_controller.log\n')
    info('*** To see learned MACs and flows, check the log.\n')
    
    info('\n*** Entering CLI (type "exit" to stop)\n')
    CLI(net)
    
    info('*** Stopping network\n')
    net.stop()

if __name__ == '__main__':
    test_topology()
