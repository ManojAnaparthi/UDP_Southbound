#!/usr/bin/env python3

import os
import re
import signal
import subprocess
import sys
import time
from pathlib import Path


def _require_root():
    if os.geteuid() != 0:
        print("ERROR: This test must be run as root (sudo).", file=sys.stderr)
        sys.exit(2)


def _repo_root() -> Path:
    return Path(__file__).resolve().parents[1]


def _run(cmd, *, check=True, capture=True, text=True, env=None):
    kwargs = {}
    if capture:
        kwargs.update({"stdout": subprocess.PIPE, "stderr": subprocess.STDOUT, "text": text})
    p = subprocess.run(cmd, env=env, **kwargs)
    if check and p.returncode != 0:
        out = p.stdout if capture else ""
        raise RuntimeError(f"Command failed ({p.returncode}): {' '.join(cmd)}\n{out}")
    return p.stdout if capture else ""


def _terminate(proc: subprocess.Popen, timeout_s: float = 3.0):
    if proc is None:
        return
    if proc.poll() is not None:
        return
    try:
        proc.send_signal(signal.SIGINT)
        proc.wait(timeout=timeout_s)
        return
    except Exception:
        pass
    try:
        proc.terminate()
        proc.wait(timeout=timeout_s)
        return
    except Exception:
        pass
    try:
        proc.kill()
    except Exception:
        pass


def _start_ryu_udp(repo: Path) -> tuple[subprocess.Popen, Path]:
    ryu_dir = repo / "ryu"
    ryu_manager = ryu_dir / "bin" / "ryu-manager"
    if not ryu_manager.exists():
        raise RuntimeError(f"Missing ryu-manager at {ryu_manager}")

    log_path = repo / "e2e_tests" / "artifacts" / "ryu_udp.log"
    log_path.parent.mkdir(parents=True, exist_ok=True)

    env = os.environ.copy()
    env["PYTHONPATH"] = str(ryu_dir)

    cmd = [
        str(ryu_manager),
        "--ofp-listen-host", "0.0.0.0",
        "--ofp-listen-transport", "udp",
        "--ofp-udp-listen-port", "6653",
        "ryu.app.simple_switch_13",
    ]

    with open(log_path, "w", encoding="utf-8") as fp:
        proc = subprocess.Popen(cmd, cwd=str(ryu_dir), env=env, stdout=fp, stderr=subprocess.STDOUT)

    # Give the controller time to start.
    time.sleep(2.0)
    return proc, log_path


def _mininet_flow_dump() -> str:
    # ovs-ofctl is available after openvswitch-switch install.
    return _run(["ovs-ofctl", "-O", "OpenFlow13", "dump-flows", "s1"], check=False)


def main() -> int:
    _require_root()
    repo = _repo_root()

    # Clean any stale Mininet/OVS state first.
    _run(["mn", "-c"], check=False)

    ryu_proc = None
    try:
        ryu_proc, ryu_log = _start_ryu_udp(repo)

        # Import Mininet only after we're root.
        from mininet.log import setLogLevel
        from mininet.net import Mininet
        from mininet.node import OVSSwitch
        from mininet.topo import SingleSwitchTopo

        setLogLevel("warning")

        topo = SingleSwitchTopo(k=2)
        net = Mininet(topo=topo, controller=None, switch=OVSSwitch, build=False, autoSetMacs=True)
        net.build()
        net.start()

        s1 = net.get("s1")

        # Force OpenFlow13 and set UDP controller.
        s1.cmd("ovs-vsctl --timeout=5 set bridge s1 protocols=OpenFlow13")
        s1.cmd("ovs-vsctl --timeout=5 set-fail-mode s1 secure")
        s1.cmd("ovs-vsctl --timeout=5 set-controller s1 udp:127.0.0.1:6653")

        # Wait for controller connection with retry loop.
        connected = False
        for attempt in range(10):
            time.sleep(1.0)
            controllers = _run(["ovs-vsctl", "--format=table", "--columns=target,is_connected", "list", "Controller"], check=False)
            if "true" in controllers.lower():
                connected = True
                break

        # Generate traffic.
        ping_loss = net.pingAll(timeout="2")

        # Dump flows.
        flows = _mininet_flow_dump()
        flows_path = repo / "e2e_tests" / "artifacts" / "ovs_flows.txt"
        flows_path.write_text(flows, encoding="utf-8")

        # Validate: table-miss should exist and should output to controller.
        has_table_miss = bool(re.search(r"priority=0.*CONTROLLER", flows))

        # Validate: after ping, simple_switch should learn and install higher-priority flows.
        # Be tolerant about exact match fields; just require non-table-miss entries.
        has_non_table_miss = any(
            ("priority=" in line and "priority=0" not in line and "actions=" in line)
            for line in flows.splitlines()
        )

        net.stop()

        if not connected:
            print("FAIL: OVS does not report controller connected.")
            print("This usually means your currently installed OVS build does not actually support OpenFlow-over-UDP runtime, even if it accepts `udp:` in ovs-vsctl.")
            print("See artifacts:")
            print(f"  {ryu_log}")
            print(f"  {flows_path}")
            return 1

        if ping_loss == 100.0:
            print("FAIL: pingAll() had 100% loss.")
            print("See artifacts:")
            print(f"  {ryu_log}")
            print(f"  {flows_path}")
            return 1

        if not has_table_miss:
            print("FAIL: Expected a table-miss flow with CONTROLLER action, but it was not found.")
            print("See artifacts:")
            print(f"  {ryu_log}")
            print(f"  {flows_path}")
            return 1

        if not has_non_table_miss:
            print("FAIL: Expected learned forwarding flows (non table-miss), but none were found.")
            print("See artifacts:")
            print(f"  {ryu_log}")
            print(f"  {flows_path}")
            return 1

        print("PASS: Ryu (UDP) + OVS (UDP controller) end-to-end Mininet test succeeded.")
        print("Artifacts:")
        print(f"  {ryu_log}")
        print(f"  {flows_path}")
        return 0

    finally:
        try:
            _run(["mn", "-c"], check=False)
        except Exception:
            pass
        _terminate(ryu_proc)


if __name__ == "__main__":
    raise SystemExit(main())
