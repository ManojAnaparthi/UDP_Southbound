# E2E Tests (Clean)

This folder contains **new, clean end-to-end tests** that validate the requirement-compliant setup:

- **Modified Ryu** listening for OpenFlow over **UDP**
- **OVS** configured with a **udp:** controller target
- **Mininet** used to generate traffic

## Test: UDP southbound in Mininet

Run:

```bash
cd /home/manoz/Acads/CN_PR
sudo python3 e2e_tests/udp_mininet_e2e.py
```

Outputs:
- `e2e_tests/artifacts/ryu_udp.log`
- `e2e_tests/artifacts/ovs_flows.txt`

## Notes

- This test uses `ryu.app.simple_switch_13` (unmodified) to prove that only the transport changed.
- If OVS does not actually include UDP OpenFlow runtime support, it may accept `udp:` in `ovs-vsctl` but will never show `is_connected=true`.
