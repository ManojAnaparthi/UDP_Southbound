#!/usr/bin/env python3
"""
TCP vs UDP OpenFlow Latency Benchmark

Measures and compares latency for OpenFlow messages over TCP vs UDP.
All results are REAL measurements - no synthetic data.

Usage:
    sudo python3 e2e_tests/benchmark_tcp_udp.py
"""

import os
import subprocess
import sys
import time
import statistics
import csv
from pathlib import Path
from datetime import datetime

try:
    import matplotlib
    matplotlib.use('Agg')
    import matplotlib.pyplot as plt
    HAS_MATPLOTLIB = True
except ImportError:
    HAS_MATPLOTLIB = False
    print("Note: matplotlib not installed - skipping charts")


def require_root():
    if os.geteuid() != 0:
        print("ERROR: Must run as root (sudo)")
        sys.exit(1)


def repo_root():
    return Path(__file__).resolve().parents[1]


def cleanup():
    subprocess.run(["mn", "-c"], capture_output=True)
    subprocess.run(["pkill", "-9", "-f", "ryu-manager"], capture_output=True)
    subprocess.run(["ovs-vsctl", "--if-exists", "del-br", "s1"], capture_output=True)
    time.sleep(1)


def start_ryu(repo, transport):
    ryu_dir = repo / "ryu"
    env = os.environ.copy()
    env["PYTHONPATH"] = str(ryu_dir)
    cmd = [
        str(ryu_dir / "bin" / "ryu-manager"),
        "--ofp-listen-host", "0.0.0.0",
        "--ofp-listen-transport", transport,
        "ryu.app.simple_switch_13",
    ]
    return subprocess.Popen(cmd, cwd=str(ryu_dir), env=env,
                           stdout=subprocess.PIPE, stderr=subprocess.PIPE)


def wait_for_ryu(transport, timeout=10):
    port_check = "-ulnp" if transport == "udp" else "-tlnp"
    for _ in range(timeout):
        result = subprocess.run(["ss", port_check], capture_output=True, text=True)
        if "6653" in result.stdout:
            return True
        time.sleep(1)
    return False


def setup_ovs_bridge(transport):
    target = f"{transport}:127.0.0.1:6653"
    subprocess.run(["ovs-vsctl", "--if-exists", "del-br", "s1"], capture_output=True)
    subprocess.run(["ovs-vsctl", "add-br", "s1", "--", "set", "bridge", "s1",
                   "protocols=OpenFlow13"], capture_output=True)
    subprocess.run(["ovs-vsctl", "set-controller", "s1", target], capture_output=True)
    
    for _ in range(50):
        result = subprocess.run(["ovs-vsctl", "list", "controller"],
                               capture_output=True, text=True)
        if "is_connected        : true" in result.stdout:
            return True
        time.sleep(0.2)
    return False


def measure_echo_rtt():
    start = time.perf_counter()
    result = subprocess.run(
        ["ovs-ofctl", "ping", "s1", "1", "-O", "OpenFlow13"],
        capture_output=True, timeout=5
    )
    end = time.perf_counter()
    return (end - start) * 1000 if result.returncode == 0 else None


def measure_flow_mod():
    flow_spec = f"priority=500,in_port=998,actions=drop"
    start = time.perf_counter()
    result = subprocess.run([
        "ovs-ofctl", "-O", "OpenFlow13", "add-flow", "s1", flow_spec
    ], capture_output=True)
    end = time.perf_counter()
    subprocess.run(["ovs-ofctl", "-O", "OpenFlow13", "del-flows", "s1", "priority=500"],
                  capture_output=True)
    return (end - start) * 1000 if result.returncode == 0 else None


def measure_stats():
    start = time.perf_counter()
    result = subprocess.run([
        "ovs-ofctl", "-O", "OpenFlow13", "dump-flows", "s1"
    ], capture_output=True)
    end = time.perf_counter()
    return (end - start) * 1000 if result.returncode == 0 else None


def run_benchmark(transport, repo, num_samples=50):
    print(f"\n{'='*60}")
    print(f"  BENCHMARKING {transport.upper()}")
    print(f"{'='*60}\n")
    
    cleanup()
    
    print(f"[1] Starting Ryu with {transport.upper()}...")
    ryu_proc = start_ryu(repo, transport)
    if not wait_for_ryu(transport):
        print(f"    ✗ Failed")
        ryu_proc.kill()
        return None
    print(f"    ✓ Ryu listening")
    
    print(f"[2] Connecting OVS...")
    if not setup_ovs_bridge(transport):
        print(f"    ✗ Failed")
        ryu_proc.kill()
        return None
    print(f"    ✓ Connected")
    time.sleep(1)
    
    results = {'echo': [], 'flow_mod': [], 'stats': []}
    
    print(f"\n[3] Echo RTT ({num_samples} samples)...")
    for i in range(num_samples):
        lat = measure_echo_rtt()
        if lat: results['echo'].append(lat)
        if (i+1) % 10 == 0: print(f"    {i+1}/{num_samples}")
        time.sleep(0.05)
    if results['echo']:
        print(f"    ✓ {statistics.mean(results['echo']):.2f} ms avg")
    
    print(f"\n[4] Flow-Mod ({num_samples} samples)...")
    for i in range(num_samples):
        lat = measure_flow_mod()
        if lat: results['flow_mod'].append(lat)
        if (i+1) % 10 == 0: print(f"    {i+1}/{num_samples}")
        time.sleep(0.05)
    if results['flow_mod']:
        print(f"    ✓ {statistics.mean(results['flow_mod']):.2f} ms avg")
    
    print(f"\n[5] Stats Request ({num_samples} samples)...")
    for i in range(num_samples):
        lat = measure_stats()
        if lat: results['stats'].append(lat)
        if (i+1) % 10 == 0: print(f"    {i+1}/{num_samples}")
        time.sleep(0.05)
    if results['stats']:
        print(f"    ✓ {statistics.mean(results['stats']):.2f} ms avg")
    
    subprocess.run(["ovs-vsctl", "--if-exists", "del-br", "s1"], capture_output=True)
    ryu_proc.terminate()
    ryu_proc.wait()
    
    return results


def create_charts(tcp, udp, output_dir):
    if not HAS_MATPLOTLIB:
        return
    
    print("\n[6] Generating charts...")
    metrics = [('Echo RTT', 'echo'), ('Flow-Mod', 'flow_mod'), ('Stats', 'stats')]
    
    # Box plot
    fig, axes = plt.subplots(1, 3, figsize=(12, 4))
    fig.suptitle('Latency Distribution: TCP vs UDP', fontweight='bold')
    for ax, (name, key) in zip(axes, metrics):
        if tcp.get(key) and udp.get(key):
            bp = ax.boxplot([tcp[key], udp[key]], labels=['TCP', 'UDP'], patch_artist=True)
            bp['boxes'][0].set_facecolor('#3498db')
            bp['boxes'][1].set_facecolor('#2ecc71')
            ax.set_ylabel('Latency (ms)')
            ax.set_title(name)
    plt.tight_layout()
    plt.savefig(output_dir / 'latency_boxplot.png', dpi=150)
    plt.close()
    print("    ✓ latency_boxplot.png")
    
    # Bar chart
    fig, ax = plt.subplots(figsize=(8, 5))
    x = range(len(metrics))
    width = 0.35
    tcp_avgs = [statistics.mean(tcp.get(k, [0])) for _, k in metrics]
    udp_avgs = [statistics.mean(udp.get(k, [0])) for _, k in metrics]
    ax.bar([i - width/2 for i in x], tcp_avgs, width, label='TCP', color='#3498db')
    ax.bar([i + width/2 for i in x], udp_avgs, width, label='UDP', color='#2ecc71')
    ax.set_ylabel('Latency (ms)')
    ax.set_title('Average Latency: TCP vs UDP')
    ax.set_xticks(x)
    ax.set_xticklabels([m[0] for m in metrics])
    ax.legend()
    plt.tight_layout()
    plt.savefig(output_dir / 'latency_comparison.png', dpi=150)
    plt.close()
    print("    ✓ latency_comparison.png")


def save_csv(tcp, udp, output_dir):
    with open(output_dir / 'benchmark_summary.csv', 'w', newline='') as f:
        writer = csv.writer(f)
        writer.writerow(['metric', 'transport', 'avg_ms', 'min_ms', 'max_ms', 'stdev_ms', 'samples'])
        for name, key in [('echo_rtt', 'echo'), ('flow_mod', 'flow_mod'), ('stats', 'stats')]:
            for transport, data in [('TCP', tcp), ('UDP', udp)]:
                vals = data.get(key, [])
                if vals:
                    writer.writerow([name, transport, f"{statistics.mean(vals):.3f}",
                                   f"{min(vals):.3f}", f"{max(vals):.3f}",
                                   f"{statistics.stdev(vals):.3f}" if len(vals) > 1 else "0",
                                   len(vals)])
    print("    ✓ benchmark_summary.csv")


def print_results(tcp, udp):
    print("\n" + "="*70)
    print("  RESULTS (all measurements are REAL)")
    print("="*70)
    
    print(f"\n  {'Metric':<15} {'TCP (ms)':<12} {'UDP (ms)':<12} {'Difference':<20}")
    print("-"*70)
    
    for name, key in [('Echo RTT', 'echo'), ('Flow-Mod', 'flow_mod'), ('Stats', 'stats')]:
        t = statistics.mean(tcp.get(key, [0]))
        u = statistics.mean(udp.get(key, [0]))
        diff = u - t
        pct = (diff / t * 100) if t else 0
        winner = "← UDP faster" if diff < 0 else "← TCP faster"
        print(f"  {name:<15} {t:<12.2f} {u:<12.2f} {diff:+.2f} ms ({pct:+.1f}%) {winner}")
    
    # Consistency
    if tcp.get('echo') and udp.get('echo'):
        tcp_std = statistics.stdev(tcp['echo'])
        udp_std = statistics.stdev(udp['echo'])
        print(f"\n  Consistency (Echo StdDev): TCP={tcp_std:.2f}ms, UDP={udp_std:.2f}ms")
        if udp_std < tcp_std:
            print(f"  → UDP is {(1 - udp_std/tcp_std)*100:.1f}% more consistent")


def main():
    require_root()
    repo = repo_root()
    
    print("="*70)
    print("  TCP vs UDP OpenFlow Latency Benchmark")
    print("="*70)
    
    tcp = run_benchmark("tcp", repo)
    udp = run_benchmark("udp", repo)
    
    if tcp and udp:
        output_dir = repo / "e2e_tests" / "artifacts"
        output_dir.mkdir(exist_ok=True)
        
        create_charts(tcp, udp, output_dir)
        save_csv(tcp, udp, output_dir)
        print_results(tcp, udp)
    
    cleanup()
    print("\n" + "="*70)
    print("  COMPLETE")
    print("="*70 + "\n")


if __name__ == "__main__":
    main()
