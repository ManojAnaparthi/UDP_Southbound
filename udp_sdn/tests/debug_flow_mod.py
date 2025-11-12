#!/usr/bin/env python3
"""
Test OpenFlow 1.3 FLOW_MOD Structure
=====================================

Debug the FLOW_MOD message format to ensure it matches OpenFlow 1.3 spec.
"""

import struct

def build_correct_table_miss_flow():
    """
    Build a correct table-miss FLOW_MOD for OpenFlow 1.3.
    
    According to OpenFlow 1.3 spec:
    - FLOW_MOD is 56 bytes base + match + instructions
    - Must be 8-byte aligned
    - Instructions must contain proper actions
    """
    
    version = 0x04  # OpenFlow 1.3
    msg_type = 14   # OFPT_FLOW_MOD
    xid = 0x12345678
    
    # FLOW_MOD body (48 bytes after header)
    cookie = 0
    cookie_mask = 0
    table_id = 0
    command = 0  # OFPFC_ADD
    idle_timeout = 0
    hard_timeout = 0
    priority = 0
    buffer_id = 0xffffffff
    out_port = 0xffffffff
    out_group = 0xffffffff
    flags = 0x0001  # OFPFF_SEND_FLOW_REM
    pad = 0
    
    # Build flow_mod body
    flow_body = struct.pack('!QQ', cookie, cookie_mask)
    flow_body += struct.pack('!BBHHHIII', table_id, command, idle_timeout, 
                            hard_timeout, priority, buffer_id, out_port, out_group)
    flow_body += struct.pack('!HH', flags, pad)
    
    # Match structure (match all = wildcard)
    # type=OFPMT_OXM (1), length=4 (just type+length, no TLVs)
    match_type = 1
    match_length = 4
    match = struct.pack('!HH', match_type, match_length)
    # Pad to 8-byte boundary
    match_padded_len = ((4 + 7) // 8) * 8  # = 8
    match += b'\x00' * (match_padded_len - 4)
    
    # Instructions: OFPIT_APPLY_ACTIONS with OUTPUT action
    # Instruction header: type=4 (APPLY_ACTIONS), length (includes actions)
    
    # Action: OUTPUT to CONTROLLER
    action_type = 0  # OFPAT_OUTPUT
    action_len = 16  # Fixed size for OUTPUT action
    output_port = 0xfffffffd  # OFPP_CONTROLLER
    max_len = 0xffff  # Send full packet (OFPCML_NO_BUFFER)
    
    action = struct.pack('!HH', action_type, action_len)
    action += struct.pack('!IH', output_port, max_len)
    action += b'\x00' * 6  # padding to 16 bytes
    
    # Instruction: APPLY_ACTIONS
    inst_type = 4  # OFPIT_APPLY_ACTIONS
    inst_len = 8 + len(action)  # header (8) + actions
    inst_pad = 0
    
    instruction = struct.pack('!HHI', inst_type, inst_len, inst_pad)
    instruction += action
    
    # Assemble complete message
    flow_mod = flow_body + match + instruction
    
    # Add header
    total_length = 8 + len(flow_mod)
    header = struct.pack('!BBHI', version, msg_type, total_length, xid)
    
    complete_msg = header + flow_mod
    
    print("FLOW_MOD Message Analysis:")
    print("="*70)
    print("Header: {} bytes".format(len(header)))
    print("  Version: 0x{:02x}".format(version))
    print("  Type: {} (FLOW_MOD)".format(msg_type))
    print("  Length: {} bytes".format(total_length))
    print("  XID: 0x{:08x}".format(xid))
    print("")
    print("Body: {} bytes".format(len(flow_body)))
    print("  Priority: {}".format(priority))
    print("  Table: {}".format(table_id))
    print("  Command: {} (ADD)".format(command))
    print("")
    print("Match: {} bytes (padded)".format(len(match)))
    print("  Type: {} (OXM)".format(match_type))
    print("  Length: {} (no match fields = match all)".format(match_length))
    print("")
    print("Instructions: {} bytes".format(len(instruction)))
    print("  Type: {} (APPLY_ACTIONS)".format(inst_type))
    print("  Length: {}".format(inst_len))
    print("  Action: OUTPUT to CONTROLLER")
    print("  Max length: {} (no limit)".format(max_len))
    print("")
    print("Total message: {} bytes".format(len(complete_msg)))
    print("8-byte aligned: {}".format("YES" if len(complete_msg) % 8 == 0 else "NO"))
    print("")
    print("Hex dump (first 64 bytes):")
    hex_str = ''.join('{:02x}'.format(b) for b in complete_msg[:64])
    for i in range(0, len(hex_str), 32):
        print("  " + hex_str[i:i+32])
    print("")
    
    return complete_msg

if __name__ == '__main__':
    msg = build_correct_table_miss_flow()
    
    print("="*70)
    print("Verification:")
    print("="*70)
    print("✓ Message length: {} bytes".format(len(msg)))
    print("✓ 8-byte aligned: {}".format(len(msg) % 8 == 0))
    print("✓ Minimum size (56 bytes): {}".format(len(msg) >= 56))
    print("")
    print("This message should work with OVS!")
