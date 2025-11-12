#!/usr/bin/env python2
"""
Quick Mininet Test for Phase 3
===============================
"""

from mininet.net import Mininet
from mininet.node import OVSSwitch
from mininet.log import setLogLevel
import subprocess
import time

setLogLevel('info')

# Cleanup first
print("Cleaning up...")
import os
devnull = open(os.devnull, 'w')
subprocess.call(['mn', '-c'], stderr=devnull, stdout=devnull)
devnull.close()
time.sleep(2)

print("Creating topology...")
net = Mininet(switch=OVSSwitch, controller=None, autoSetMacs=True, waitConnected=True)

# Add hosts
h1 = net.addHost('h1', ip='10.0.0.1/24', mac='00:00:00:00:00:01')
h2 = net.addHost('h2', ip='10.0.0.2/24', mac='00:00:00:00:00:02')

# Add switch
s1 = net.addSwitch('s1', protocols='OpenFlow13')

# Links
net.addLink(h1, s1)
net.addLink(h2, s1)

# Start
net.start()

print("Configuring controller...")
subprocess.call(['ovs-vsctl', 'set-controller', 's1', 'udp:127.0.0.1:6653'])
subprocess.call(['ovs-vsctl', 'set', 'bridge', 's1', 'fail_mode=secure'])

print("Waiting 5 seconds for handshake...")
time.sleep(5)

print("\n=== Testing L2 Learning ===")
print("Ping h1 -> h2 (3 packets)...")
result = h1.cmd('ping -c 3 10.0.0.2')
print(result)

print("\nPing h2 -> h1 (3 packets)...")
result = h2.cmd('ping -c 3 10.0.0.1')
print(result)

print("\n=== Check controller log: ===")
print("tail -50 /tmp/phase3_controller.log | grep -A 3 'PACKET_IN'")

print("\nStopping...")
net.stop()
