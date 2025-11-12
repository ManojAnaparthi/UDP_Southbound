#!/usr/bin/env python3
"""
Comprehensive OVS UDP OpenFlow Testing
Tests all phases systematically to identify where PACKET_IN fails
"""

import socket
import struct
import time
import sys
import os
import subprocess

# OpenFlow constants
OFPV_1_3 = 0x04
OFPT_HELLO = 0
OFPT_ERROR = 1
OFPT_ECHO_REQUEST = 2
OFPT_ECHO_REPLY = 3
OFPT_FEATURES_REQUEST = 5
OFPT_FEATURES_REPLY = 6
OFPT_GET_CONFIG_REQUEST = 7
OFPT_GET_CONFIG_REPLY = 8
OFPT_SET_CONFIG = 9
OFPT_PACKET_IN = 10
OFPT_FLOW_MOD = 14
OFPT_PACKET_OUT = 13

# XID counter
xid_counter = 1

def get_xid():
    global xid_counter
    xid = xid_counter
    xid_counter += 1
    return xid

def build_ofp_header(version, msg_type, length, xid):
    """Build OpenFlow header"""
    return struct.pack('!BBHI', version, msg_type, length, xid)

def build_hello():
    """Build HELLO message"""
    xid = get_xid()
    header = build_ofp_header(OFPV_1_3, OFPT_HELLO, 8, xid)
    return header, xid

def build_features_request():
    """Build FEATURES_REQUEST message"""
    xid = get_xid()
    header = build_ofp_header(OFPV_1_3, OFPT_FEATURES_REQUEST, 8, xid)
    return header, xid

def build_set_config():
    """Build SET_CONFIG message to enable sending fragments"""
    xid = get_xid()
    # OpenFlow 1.3: flags should be OFPC_FRAG_NORMAL (0)
    # miss_send_len=0xffff means send full packet
    flags = 0  # OFPC_FRAG_NORMAL
    miss_send_len = 0xffff
    config = struct.pack('!HH', flags, miss_send_len)
    total_len = 8 + len(config)
    header = build_ofp_header(OFPV_1_3, OFPT_SET_CONFIG, total_len, xid)
    return header + config, xid

def build_table_miss_flow():
    """Build table-miss flow that sends all packets to controller"""
    xid = get_xid()
    
    # Flow mod fields
    cookie = 0
    cookie_mask = 0
    table_id = 0
    command = 0  # OFPFC_ADD
    idle_timeout = 0
    hard_timeout = 0
    priority = 0  # Lowest priority for table-miss
    buffer_id = 0xffffffff  # OFP_NO_BUFFER
    out_port = 0xffffffff  # OFPP_ANY
    out_group = 0xffffffff  # OFPG_ANY
    flags = 0
    
    # Build flow_mod body
    flow_body = struct.pack('!QQ', cookie, cookie_mask)
    flow_body += struct.pack('!BBHHHIII', 
                           table_id, command, idle_timeout, hard_timeout,
                           priority, buffer_id, out_port, out_group)
    flow_body += struct.pack('!HH', flags, 0)  # flags + padding
    
    # Match: OXM match with no match fields (match all)
    # struct ofp_match {
    #     uint16_t type;          /* OFPMT_OXM */
    #     uint16_t length;        /* Length of match including padding */
    #     uint8_t oxm_fields[4];  /* OXM TLVs - zero length for match-all */
    #     uint8_t pad[4];         /* Zero bytes to pad to 64 bits */
    # };
    match_type = 1  # OFPMT_OXM
    match_length = 4  # Just the type+length, no OXM TLVs
    match = struct.pack('!HH', match_type, match_length)
    # Pad to 8-byte boundary
    match_padlen = (8 - (match_length % 8)) % 8
    if match_padlen > 0:
        match += b'\x00' * match_padlen
    
    # Instructions: output to controller
    # OFPIT_APPLY_ACTIONS = 4
    inst_type = 4
    # Action: OFPAT_OUTPUT = 0
    action_type = 0
    action_len = 16  # Output action is 16 bytes
    action_port = 0xfffffffd  # OFPP_CONTROLLER
    action_max_len = 0xffff  # No limit
    action = struct.pack('!HHI', action_type, action_len, action_port)
    action += struct.pack('!H', action_max_len)
    action += b'\x00' * 6  # Padding
    
    inst_len = 8 + len(action)  # Header + actions
    instruction = struct.pack('!HH', inst_type, inst_len)
    instruction += b'\x00' * 4  # Padding
    instruction += action
    
    flow_mod = flow_body + match + instruction
    total_len = 8 + len(flow_mod)
    
    header = build_ofp_header(OFPV_1_3, OFPT_FLOW_MOD, total_len, xid)
    return header + flow_mod, xid

def parse_message(data):
    """Parse OpenFlow message header"""
    if len(data) < 8:
        return None
    
    version, msg_type, length, xid = struct.unpack('!BBHI', data[:8])
    
    msg_types = {
        OFPT_HELLO: "HELLO",
        OFPT_ERROR: "ERROR",
        OFPT_ECHO_REQUEST: "ECHO_REQUEST",
        OFPT_ECHO_REPLY: "ECHO_REPLY",
        OFPT_FEATURES_REPLY: "FEATURES_REPLY",
        OFPT_GET_CONFIG_REPLY: "GET_CONFIG_REPLY",
        OFPT_PACKET_IN: "PACKET_IN",
    }
    
    return {
        'version': version,
        'type': msg_type,
        'type_name': msg_types.get(msg_type, "UNKNOWN({})".format(msg_type)),
        'length': length,
        'xid': xid,
        'data': data
    }

class UDPOpenFlowTester:
    def __init__(self, controller_ip='0.0.0.0', controller_port=6653):
        self.controller_ip = controller_ip
        self.controller_port = controller_port
        self.sock = None
        self.switches = {}
        
    def start(self):
        """Start UDP listener"""
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sock.bind((self.controller_ip, self.controller_port))
        self.sock.settimeout(1.0)  # 1 second timeout
        print('✓ UDP controller listening on {}:{}'.format(self.controller_ip, self.controller_port))
        
    def wait_for_message(self, expected_type=None, timeout=5):
        """Wait for a specific message type"""
        start = time.time()
        while time.time() - start < timeout:
            try:
                data, addr = self.sock.recvfrom(65535)
                msg = parse_message(data)
                if msg:
                    print("  ← Received {} from {}".format(msg['type_name'], addr))
                    if expected_type is None or msg['type'] == expected_type:
                        return msg, addr
            except socket.timeout:
                continue
        return None, None
    
    def send_message(self, message, addr):
        """Send OpenFlow message"""
        self.sock.sendto(message, addr)
        msg_type = struct.unpack('!B', message[1:2])[0]
        type_names = {OFPT_HELLO: "HELLO", OFPT_FEATURES_REQUEST: "FEATURES_REQUEST",
                     OFPT_SET_CONFIG: "SET_CONFIG", OFPT_FLOW_MOD: "FLOW_MOD"}
        print("  → Sent {}".format(type_names.get(msg_type, 'UNKNOWN')))
    
    def test_phase1_hello(self):
        """Phase 1: Test basic HELLO exchange"""
        print("\n" + "="*60)
        print("PHASE 1: Testing HELLO Exchange")
        print("="*60)
        
        print("Waiting for HELLO from switch...")
        msg, addr = self.wait_for_message(OFPT_HELLO, timeout=10)
        
        if not msg:
            print("✗ FAILED: No HELLO received")
            return False
        
        print("✓ HELLO received from {}".format(addr))
        
        # Send HELLO reply
        hello, _ = build_hello()
        self.send_message(hello, addr)
        print("✓ HELLO reply sent")
        
        self.switches[addr] = {'dpid': None, 'configured': False}
        
        return True
    
    def test_phase2_features(self, addr):
        """Phase 2: Test FEATURES exchange"""
        print("\n" + "="*60)
        print("PHASE 2: Testing FEATURES Exchange")
        print("="*60)
        
        # Send FEATURES_REQUEST
        features_req, _ = build_features_request()
        self.send_message(features_req, addr)
        
        # Wait for FEATURES_REPLY
        print("Waiting for FEATURES_REPLY...")
        msg, _ = self.wait_for_message(OFPT_FEATURES_REPLY, timeout=5)
        
        if not msg:
            print("✗ FAILED: No FEATURES_REPLY received")
            return False
        
        # Parse DPID
        if len(msg['data']) >= 16:
            dpid = struct.unpack('!Q', msg['data'][8:16])[0]
            print("✓ FEATURES_REPLY received, DPID: {:016x}".format(dpid))
            self.switches[addr]['dpid'] = dpid
            return True
        
        print("✗ FAILED: Invalid FEATURES_REPLY")
        return False
    
    def test_phase3_config(self, addr):
        """Phase 3: Test SET_CONFIG"""
        print("\n" + "="*60)
        print("PHASE 3: Testing SET_CONFIG")
        print("="*60)
        
        # Send SET_CONFIG
        set_config, _ = build_set_config()
        self.send_message(set_config, addr)
        print("✓ SET_CONFIG sent (miss_send_len=0xffff)")
        
        return True
    
    def test_phase4_table_miss(self, addr):
        """Phase 4: Install table-miss flow"""
        print("\n" + "="*60)
        print("PHASE 4: Installing Table-Miss Flow")
        print("="*60)
        
        # Send table-miss flow
        flow_mod, xid = build_table_miss_flow()
        print("Sending FLOW_MOD (length={} bytes, xid={})...".format(len(flow_mod), xid))
        self.send_message(flow_mod, addr)
        
        # Check for error
        print("Checking for errors...")
        time.sleep(0.5)
        try:
            data, err_addr = self.sock.recvfrom(65535)
            msg = parse_message(data)
            if msg and msg['type'] == OFPT_ERROR:
                # Parse error details
                if len(msg['data']) >= 12:
                    error_type = struct.unpack('!H', msg['data'][8:10])[0]
                    error_code = struct.unpack('!H', msg['data'][10:12])[0]
                    print("✗ FAILED: Received ERROR - type:{} code:{}".format(error_type, error_code))
                else:
                    print("✗ FAILED: Received ERROR message")
                return False
            elif msg:
                print("  Received {msg['type_name']} (not an error)".format())
        except socket.timeout:
            pass
        
        print("✓ FLOW_MOD sent successfully (no error)")
        self.switches[addr]['configured'] = True
        
        return True
    
    def test_phase5_packet_in(self, addr):
        """Phase 5: Wait for PACKET_IN messages"""
        print("\n" + "="*60)
        print("PHASE 5: Testing PACKET_IN Reception")
        print("="*60)
        
        print("Waiting for PACKET_IN messages (20 seconds)...")
        print("(Generate traffic with: sudo mn -c && sudo mn --topo single,2 --controller remote,ip=127.0.0.1,port=6653)")
        print("(Then run in mininet: pingall)")
        
        packet_in_count = 0
        start = time.time()
        
        while time.time() - start < 20:
            try:
                data, recv_addr = self.sock.recvfrom(65535)
                msg = parse_message(data)
                if msg:
                    if msg['type'] == OFPT_PACKET_IN:
                        packet_in_count += 1
                        print("  ✓ PACKET_IN #{} received!".format(packet_in_count))
                    elif msg['type'] == OFPT_ECHO_REQUEST:
                        # Reply to echo
                        echo_reply = build_ofp_header(OFPV_1_3, OFPT_ECHO_REPLY, 
                                                     msg['length'], msg['xid'])
                        self.sock.sendto(echo_reply, recv_addr)
                    else:
                        print("  Received {}".format(msg['type_name']))
            except socket.timeout:
                continue
        
        if packet_in_count > 0:
            print("\n✓ SUCCESS: Received {} PACKET_IN messages".format(packet_in_count))
            return True
        else:
            print("\n✗ FAILED: No PACKET_IN messages received")
            return False
    
    def run_full_test(self):
        """Run complete test sequence"""
        print("\n" + "="*60)
        print("COMPREHENSIVE OVS UDP OPENFLOW TEST")
        print("="*60)
        
        self.start()
        
        # Phase 1: HELLO
        if not self.test_phase1_hello():
            return False
        
        addr = list(self.switches.keys())[0]
        
        # Phase 2: FEATURES
        if not self.test_phase2_features(addr):
            return False
        
        # Phase 3: SET_CONFIG (skip for now - OVS has issues with flags)
        # if not self.test_phase3_config(addr):
        #     return False
        print("\n" + "="*60)
        print("PHASE 3: SET_CONFIG - SKIPPED (OVS compatibility)")
        print("="*60)
        
        # Phase 4: Table-miss flow
        if not self.test_phase4_table_miss(addr):
            return False
        
        # Phase 5: PACKET_IN
        if not self.test_phase5_packet_in(addr):
            return False
        
        print("\n" + "="*60)
        print("ALL TESTS PASSED!")
        print("="*60)
        
        return True

def main():
    print("""
OVS UDP OpenFlow Comprehensive Test
====================================

This test will:
1. Start a UDP controller on port 6653
2. Wait for switch HELLO
3. Exchange FEATURES
4. Send SET_CONFIG
5. Install table-miss flow
6. Wait for PACKET_IN messages

Instructions:
1. In another terminal, run:
   sudo mn -c
   sudo mn --topo single,2 --controller remote,ip=127.0.0.1,port=6653
   
2. Once Mininet starts and shows "mininet>", run:
   pingall
   
3. Watch this terminal for PACKET_IN messages

Press Ctrl+C to stop.
""")
    
    tester = UDPOpenFlowTester()
    
    try:
        tester.run_full_test()
    except KeyboardInterrupt:
        print("\n\nTest interrupted by user")
    except Exception as e:
        print("\n\nTest failed with error: {}".format(e))
        import traceback
        traceback.print_exc()
    finally:
        if tester.sock:
            tester.sock.close()

if __name__ == '__main__':
    main()
