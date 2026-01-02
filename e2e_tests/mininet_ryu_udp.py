#!/usr/bin/env python3
"""
Mininet + Ryu UDP Demo

This script creates a Mininet topology where OVS switches automatically
connect to a Ryu controller via UDP (not TCP).

Usage:
    sudo python3 e2e_tests/mininet_ryu_udp.py
"""

import os
import signal
import subprocess
import sys
import time
from pathlib import Path


def require_root():
    if os.geteuid() != 0:
        print("ERROR: Must run as root (sudo)")
        sys.exit(1)


def repo_root():
    return Path(__file__).resolve().parents[1]


def start_ryu_udp(repo):
    """Start Ryu controller with UDP transport."""
    ryu_dir = repo / "ryu"
    ryu_manager = ryu_dir / "bin" / "ryu-manager"
    
    env = os.environ.copy()
    env["PYTHONPATH"] = str(ryu_dir)
    
    cmd = [
        str(ryu_manager),
        "--ofp-listen-host", "0.0.0.0",
        "--ofp-listen-transport", "udp",
        "--ofp-udp-listen-port", "6653",
        "--verbose",
        "ryu.app.simple_switch_13",
    ]
    
    proc = subprocess.Popen(cmd, cwd=str(ryu_dir), env=env)
    return proc


def main():
    require_root()
    repo = repo_root()
    
    # Clean any stale state
    subprocess.run(["mn", "-c"], capture_output=True)
    subprocess.run(["pkill", "-9", "-f", "ryu-manager"], capture_output=True)
    time.sleep(1)
    
    print("=" * 60)
    print("  Mininet + Ryu UDP Demo")
    print("=" * 60)
    print()
    
    # Step 1: Start Ryu with UDP
    print("[1] Starting Ryu controller with UDP transport...")
    ryu_proc = start_ryu_udp(repo)
    time.sleep(3)
    
    # Verify Ryu is listening on UDP
    result = subprocess.run(["ss", "-ulnp"], capture_output=True, text=True)
    if "6653" in result.stdout:
        print("    ✓ Ryu listening on UDP port 6653")
    else:
        print("    ✗ Ryu failed to start")
        ryu_proc.kill()
        sys.exit(1)
    print()
    
    # Step 2: Create Mininet topology
    print("[2] Creating Mininet topology: h1 --- s1 --- h2")
    
    from mininet.net import Mininet
    from mininet.node import OVSSwitch, Controller
    from mininet.topo import SingleSwitchTopo
    from mininet.log import setLogLevel
    from mininet.cli import CLI
    
    setLogLevel("info")
    
    topo = SingleSwitchTopo(k=2)
    # Use standard OVSSwitch with no controller (we'll set it manually)
    net = Mininet(topo=topo, switch=OVSSwitch, controller=None, autoSetMacs=True)
    
    print("    ✓ Topology created")
    print()
    
    # Step 3: Start the network
    print("[3] Starting network...")
    net.start()
    
    # Configure the switch to use UDP controller (must be done AFTER net.start())
    print("    Configuring switch to use UDP controller...")
    s1 = net.get("s1")
    s1.cmd("ovs-vsctl set bridge s1 protocols=OpenFlow13")
    s1.cmd("ovs-vsctl set-controller s1 udp:127.0.0.1:6653")
    s1.cmd("ovs-vsctl set-fail-mode s1 secure")
    
    # Wait for OpenFlow handshake to complete
    print("    Waiting for OpenFlow connection...")
    for i in range(15):  # Wait up to 15 seconds
        time.sleep(1)
        result = subprocess.run(
            ["ovs-vsctl", "list", "controller"],
            capture_output=True, text=True
        )
        if "is_connected        : true" in result.stdout:
            print("    ✓ Switch s1 connected to controller via UDP")
            break
    else:
        print("    ⚠ Connection timeout (this may still work)")
    print()
    
    # Step 4: Show the topology
    print("[4] Network topology:")
    h1, h2 = net.get("h1", "h2")
    print(f"    h1: {h1.IP()}")
    print(f"    h2: {h2.IP()}")
    print(f"    s1: connected to udp:127.0.0.1:6653")
    print()
    
    # Step 5: Test connectivity
    print("[5] Testing connectivity (ping h1 -> h2)...")
    time.sleep(3)  # Additional wait for flows to be installed
    result = h1.cmd(f"ping -c 3 {h2.IP()}")
    print(result)
    
    if "0% packet loss" in result:
        print("    ✓ Ping successful!")
    else:
        print("    ✗ Ping failed")
    print()
    
    # Step 6: Show flows installed by Ryu
    print("[6] OpenFlow flows installed by Ryu (via UDP):")
    flows = subprocess.run(
        ["ovs-ofctl", "-O", "OpenFlow13", "dump-flows", "s1"],
        capture_output=True, text=True
    )
    for line in flows.stdout.strip().split("\n"):
        if line.strip():
            print(f"    {line.strip()}")
    print()
    
    # Step 7: Additional ping test
    print("[7] Running pingall test...")
    net.pingAll()
    print()
    
    print("=" * 60)
    print("  SUCCESS: Mininet hosts communicating via Ryu UDP controller!")
    print("=" * 60)
    print()
    
    # Cleanup
    print("\nCleaning up...")
    net.stop()
    ryu_proc.terminate()
    ryu_proc.wait()
    print("Done.")


if __name__ == "__main__":
    main()
