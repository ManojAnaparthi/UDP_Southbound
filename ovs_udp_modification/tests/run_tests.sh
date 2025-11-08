#!/bin/bash
#
# Quick test script for OVS UDP modifications
# Runs unit tests to verify UDP functionality
#

set -e  # Exit on error

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"

echo "========================================================================"
echo " OVS UDP Modification - Quick Test"
echo "========================================================================"
echo ""

# Check Python is available
if ! command -v python3 &> /dev/null; then
    echo "[ERROR] python3 not found. Please install Python 3."
    exit 1
fi

echo "[INFO] Python 3 found: $(python3 --version)"
echo ""

# Run unit tests
echo "Running UDP unit tests..."
echo ""
python3 "$SCRIPT_DIR/test_udp_unit.py"

TEST_RESULT=$?

echo ""
if [ $TEST_RESULT -eq 0 ]; then
    echo "========================================================================"
    echo " ✓ All unit tests passed!"
    echo "========================================================================"
    echo ""
    echo "Next steps:"
    echo "  1. Build OVS with UDP support (see BUILD_GUIDE.md)"
    echo "  2. Start UDP controller: python3 -m udp_baseline.controllers.udp_ofp_controller"
    echo "  3. Run integration test: sudo python3 tests/test_ovs_udp_integration.py"
    echo ""
else
    echo "========================================================================"
    echo " ✗ Unit tests failed"
    echo "========================================================================"
    echo ""
    echo "Please check the errors above and try again."
    echo ""
    exit 1
fi
