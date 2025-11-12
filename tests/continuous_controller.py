#!/usr/bin/env python3
"""
Continuous UDP OpenFlow Controller
Stays alive and logs all messages
"""

import socket
import struct
import time
import binascii
import threading
import sys

OFPV_1_3 = 0x04
OFPT_HELLO = 0
OFPT_ERROR = 1
OFPT_ECHO_REQUEST = 2
OFPT_ECHO_REPLY = 3
OFPT_FEATURES_REQUEST = 5
OFPT_FEATURES_REPLY = 6
OFPT_PACKET_IN = 10
OFPT_FLOW_MOD = 14

ERROR_TYPES = {
    0: "OFPET_HELLO_FAILED",
    1: "OFPET_BAD_REQUEST",
    2: "OFPET_BAD_ACTION",
    3: "OFPET_BAD_INSTRUCTION",
    4: "OFPET_BAD_MATCH",
    5: "OFPET_FLOW_MOD_FAILED",
    10: "OFPET_SWITCH_CONFIG_FAILED",
}

xid_counter = 1

def get_xid():
    global xid_counter
    xid = xid_counter
    xid_counter += 1
    return xid

def build_ofp_header(version, msg_type, length, xid):
    return struct.pack('!BBHI', version, msg_type, length, xid)

class ContinuousController:
    def __init__(self):
        self.sock = None
        self.switches = {}
        self.running = True
        self.packet_in_count = 0
        self.echo_count = 0
        
    def start(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sock.bind(('0.0.0.0', 6653))
        self.sock.settimeout(1.0)
        print("[{}] Controller listening on port 6653".format(time.strftime("%H:%M:%S")))
        
        # Start echo pinger
        threading.Thread(target=self._echo_pinger, daemon=True).start()
        print("[{}] ECHO keepalive started".format(time.strftime("%H:%M:%S")))
        
    def _echo_pinger(self):
        while self.running:
            time.sleep(5)
            for addr in list(self.switches.keys()):
                xid = get_xid()
                msg = build_ofp_header(OFPV_1_3, OFPT_ECHO_REQUEST, 8, xid)
                self.sock.sendto(msg, addr)
                
    def _handle_hello(self, data, addr):
        print("[{}] HELLO from {}".format(time.strftime("%H:%M:%S"), addr))
        # Send HELLO reply
        xid = get_xid()
        msg = build_ofp_header(OFPV_1_3, OFPT_HELLO, 8, xid)
        self.sock.sendto(msg, addr)
        
        # Send FEATURES_REQUEST
        xid = get_xid()
        msg = build_ofp_header(OFPV_1_3, OFPT_FEATURES_REQUEST, 8, xid)
        self.sock.sendto(msg, addr)
        print("[{}] Sent HELLO + FEATURES_REQUEST".format(time.strftime("%H:%M:%S")))
        
    def _handle_features_reply(self, data, addr):
        if len(data) >= 16:
            dpid = struct.unpack('!Q', data[8:16])[0]
            print("[{}] FEATURES_REPLY from {}, DPID: {:016x}".format(
                time.strftime("%H:%M:%S"), addr, dpid))
            self.switches[addr] = {'dpid': dpid}
            
            # Install table-miss flow
            self._install_table_miss(addr)
            
    def _install_table_miss(self, addr):
        xid = get_xid()
        
        # Build flow_mod for table-miss
        cookie = 0
        cookie_mask = 0
        table_id = 0
        command = 0
        idle_timeout = 0
        hard_timeout = 0
        priority = 0
        buffer_id = 0xffffffff
        out_port = 0xffffffff
        out_group = 0xffffffff
        flags = 0
        
        flow_body = struct.pack('!QQ', cookie, cookie_mask)
        flow_body += struct.pack('!BBHHHIII', 
                               table_id, command, idle_timeout, hard_timeout,
                               priority, buffer_id, out_port, out_group)
        flow_body += struct.pack('!HH', flags, 0)
        
        # Match (match all)
        match_type = 1
        match_length = 4
        match = struct.pack('!HH', match_type, match_length)
        match += b'\x00' * 4  # Pad to 8 bytes
        
        # Instruction: APPLY_ACTIONS with OUTPUT to CONTROLLER
        inst_type = 4
        action_type = 0
        action_len = 16
        action_port = 0xfffffffd  # OFPP_CONTROLLER
        action_max_len = 0xffff
        
        action = struct.pack('!HHI', action_type, action_len, action_port)
        action += struct.pack('!H', action_max_len)
        action += b'\x00' * 6
        
        inst_len = 8 + len(action)
        instruction = struct.pack('!HH', inst_type, inst_len)
        instruction += b'\x00' * 4
        instruction += action
        
        flow_mod = flow_body + match + instruction
        total_len = 8 + len(flow_mod)
        
        header = build_ofp_header(OFPV_1_3, OFPT_FLOW_MOD, total_len, xid)
        message = header + flow_mod
        
        self.sock.sendto(message, addr)
        print("[{}] Installed table-miss flow ({} bytes)".format(
            time.strftime("%H:%M:%S"), len(message)))
        
    def _handle_echo_request(self, data, addr, xid):
        msg = build_ofp_header(OFPV_1_3, OFPT_ECHO_REPLY, 8, xid)
        self.sock.sendto(msg, addr)
        self.echo_count += 1
        
    def _handle_packet_in(self, data, addr):
        self.packet_in_count += 1
        print("[{}] ✓✓✓ PACKET_IN #{} from {} ✓✓✓".format(
            time.strftime("%H:%M:%S"), self.packet_in_count, addr))
        if len(data) > 8:
            print("    Payload: {}".format(binascii.hexlify(data[8:32]).decode()))
            
    def _handle_error(self, data, addr):
        if len(data) >= 12:
            err_type, err_code = struct.unpack('!HH', data[8:12])
            err_data = data[12:]
            err_type_name = ERROR_TYPES.get(err_type, "UNKNOWN")
            print("[{}] ERROR from {}: type={} ({}) code={}".format(
                time.strftime("%H:%M:%S"), addr, err_type, err_type_name, err_code))
            if len(err_data) >= 8:
                bad_ver, bad_type, bad_len, bad_xid = struct.unpack('!BBHI', err_data[:8])
                print("    Offending: ver={} type={} len={} xid={}".format(
                    bad_ver, bad_type, bad_len, bad_xid))
                print("    Hex: {}".format(binascii.hexlify(err_data[:64]).decode()))
                
    def run(self):
        print("\n" + "="*60)
        print("CONTINUOUS UDP OPENFLOW CONTROLLER")
        print("="*60)
        print("Waiting for switches to connect...")
        print("Press Ctrl+C to stop\n")
        
        try:
            while self.running:
                try:
                    data, addr = self.sock.recvfrom(65535)
                    if len(data) < 8:
                        continue
                        
                    version, msg_type, length, xid = struct.unpack('!BBHI', data[:8])
                    
                    if msg_type == OFPT_HELLO:
                        self._handle_hello(data, addr)
                    elif msg_type == OFPT_FEATURES_REPLY:
                        self._handle_features_reply(data, addr)
                    elif msg_type == OFPT_ECHO_REQUEST:
                        self._handle_echo_request(data, addr, xid)
                    elif msg_type == OFPT_PACKET_IN:
                        self._handle_packet_in(data, addr)
                    elif msg_type == OFPT_ERROR:
                        self._handle_error(data, addr)
                        
                except socket.timeout:
                    continue
                    
        except KeyboardInterrupt:
            print("\n\n[{}] Stopping controller...".format(time.strftime("%H:%M:%S")))
            print("Statistics:")
            print("  PACKET_IN received: {}".format(self.packet_in_count))
            print("  ECHO handled: {}".format(self.echo_count))
            print("  Switches connected: {}".format(len(self.switches)))
        finally:
            self.running = False
            if self.sock:
                self.sock.close()

if __name__ == '__main__':
    controller = ContinuousController()
    controller.start()
    controller.run()
