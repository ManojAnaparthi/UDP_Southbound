# E2E Tests

End-to-end tests for validating OpenFlow over UDP.

## Test Files

| File | Description |
|------|-------------|
| `mininet_ryu_udp.py` | Interactive Mininet demo with step-by-step output |
| `benchmark_tcp_udp.py` | TCP vs UDP latency comparison (50 samples each) |
| `ofp_message_test_app.py` | Ryu app that tests all OpenFlow message types |
| `ofp_message_test.py` | Runner script for OpenFlow message tests |

## Quick Start

### Interactive Demo
```bash
sudo python3 e2e_tests/mininet_ryu_udp.py
```

### Latency Benchmark
```bash
sudo python3 e2e_tests/benchmark_tcp_udp.py
```

## Artifacts

Generated files in `artifacts/`:
- `benchmark_summary.csv` - Raw latency data
- `latency_boxplot.png` - Latency distribution chart
- `latency_comparison.png` - Bar chart comparison
