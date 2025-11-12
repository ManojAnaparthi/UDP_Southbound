#!/usr/bin/env python2
from mininet.net import Mininet
from mininet.node import OVSSwitch
from mininet.clean import cleanup
import subprocess
import time

# Cleanup
cleanup()
time.sleep(2)

print("Creating Mininet topology...")
net = Mininet(switch=OVSSwitch, controller=None, autoSetMacs=True, waitConnected=False)
h1 = net.addHost('h1', ip='10.0.0.1/24', mac='00:00:00:00:00:01')
h2 = net.addHost('h2', ip='10.0.0.2/24', mac='00:00:00:00:00:02')
s1 = net.addSwitch('s1', protocols='OpenFlow13')
net.addLink(h1, s1)
net.addLink(h2, s1)
net.start()

print("Configuring controller...")
subprocess.call(['ovs-vsctl', 'set-controller', 's1', 'udp:127.0.0.1:6653'])
subprocess.call(['ovs-vsctl', 'set', 'bridge', 's1', 'fail_mode=secure'])

print("Waiting for handshake (5 seconds)...")
time.sleep(5)

print("\n=== Test 1: Ping h1 -> h2 ===")
result = h1.cmd('ping -c 2 -W 2 10.0.0.2')
print(result)

print("\nWaiting 2 seconds...")
time.sleep(2)

print("\n=== Test 2: Ping h2 -> h1 ===")
result = h2.cmd('ping -c 2 -W 2 10.0.0.1')
print(result)

print("\nCleaning up...")
net.stop()
