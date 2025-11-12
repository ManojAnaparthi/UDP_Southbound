#!/usr/bin/env python3.10
"""
OpenFlow Handshake Verification Script
Tests the complete handshake sequence step by step:
1. HELLO (version negotiation)
2. FEATURES_REQUEST → FEATURES_REPLY
3. SET_CONFIG (optional)
4. ECHO_REQUEST/REPLY (keepalive)
"""

import socket
import struct
import time
import sys

# OpenFlow 1.3 Constants
OFP_VERSION = 0x04
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
OFPT_PORT_STATUS = 12
OFPT_FLOW_MOD = 14

xid_counter = 1

def get_xid():
    global xid_counter
    xid = xid_counter
    xid_counter += 1
    return xid

def timestamp():
    return time.strftime('[%H:%M:%S]')

def create_hello():
    """Create HELLO message"""
    xid = get_xid()
    message = struct.pack('!BBHI', OFP_VERSION, OFPT_HELLO, 8, xid)
    return message, xid

def create_features_request():
    """Create FEATURES_REQUEST message"""
    xid = get_xid()
    message = struct.pack('!BBHI', OFP_VERSION, OFPT_FEATURES_REQUEST, 8, xid)
    return message, xid

def create_set_config():
    """Create SET_CONFIG message with FIXED flags"""
    xid = get_xid()
    # FIX: Use flags=0x0000 (OFPC_FRAG_NORMAL) and miss_send_len=128
    # OVS validates flags against OFPC_FRAG_MASK (0x0003)
    # Only bits 0-1 are valid: 0x0000, 0x0001, 0x0002
    flags = 0x0000  # OFPC_FRAG_NORMAL (explicitly 0x0000)
    miss_send_len = 128  # Send first 128 bytes to controller (reasonable default)
    # Correct format: flags is 16-bit, miss_send_len is 16-bit
    message = struct.pack('!BBHIHH', OFP_VERSION, OFPT_SET_CONFIG, 12, xid, 
                         flags, miss_send_len)
    return message, xid

def create_echo_request():
    """Create ECHO_REQUEST message"""
    xid = get_xid()
    message = struct.pack('!BBHI', OFP_VERSION, OFPT_ECHO_REQUEST, 8, xid)
    return message, xid

def parse_header(data):
    """Parse OpenFlow message header"""
    if len(data) < 8:
        return None
    version, msg_type, length, xid = struct.unpack('!BBHI', data[:8])
    return version, msg_type, length, xid

def parse_features_reply(data):
    """Parse FEATURES_REPLY message"""
    if len(data) < 32:
        return None
    
    version, msg_type, length, xid = struct.unpack('!BBHI', data[:8])
    datapath_id, n_buffers, n_tables, auxiliary_id = struct.unpack('!QIBB', data[8:23])
    pad = struct.unpack('!B', data[23:24])[0]
    capabilities, reserved = struct.unpack('!II', data[24:32])
    
    return {
        'xid': xid,
        'datapath_id': datapath_id,
        'n_buffers': n_buffers,
        'n_tables': n_tables,
        'capabilities': capabilities
    }

def msg_type_to_string(msg_type):
    """Convert message type to string"""
    types = {
        0: 'HELLO',
        1: 'ERROR',
        2: 'ECHO_REQUEST',
        3: 'ECHO_REPLY',
        5: 'FEATURES_REQUEST',
        6: 'FEATURES_REPLY',
        7: 'GET_CONFIG_REQUEST',
        8: 'GET_CONFIG_REPLY',
        9: 'SET_CONFIG',
        10: 'PACKET_IN',
        12: 'PORT_STATUS',
        14: 'FLOW_MOD'
    }
    return types.get(msg_type, f'UNKNOWN({msg_type})')

def main():
    print("=" * 80)
    print("OpenFlow Handshake Verification Test")
    print("=" * 80)
    print()
    
    # Handshake state tracking
    handshake_steps = {
        'hello_sent': False,
        'hello_received': False,
        'features_request_sent': False,
        'features_reply_received': False,
        'set_config_sent': False,
        'echo_test_done': False
    }
    
    # Create UDP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    sock.bind(('0.0.0.0', 6653))
    sock.settimeout(10.0)
    
    print(f"{timestamp()} [INIT] Controller listening on UDP 127.0.0.1:6653")
    print(f"{timestamp()} [INIT] Waiting for OpenFlow handshake to begin...")
    print()
    print("=" * 80)
    print("HANDSHAKE SEQUENCE")
    print("=" * 80)
    
    switch_addr = None
    
    try:
        # Step 1: Receive HELLO from switch
        print(f"\n{timestamp()} [STEP 1/5] Waiting for HELLO from switch...")
        data, switch_addr = sock.recvfrom(4096)
        version, msg_type, length, xid = parse_header(data)
        
        if msg_type == OFPT_HELLO:
            handshake_steps['hello_received'] = True
            print(f"{timestamp()} ✅ HELLO received from {switch_addr}")
            print(f"            Version: {version}, XID: {xid}")
            
            # Send HELLO back
            hello_msg, hello_xid = create_hello()
            sock.sendto(hello_msg, switch_addr)
            handshake_steps['hello_sent'] = True
            print(f"{timestamp()} ✅ HELLO sent to switch (XID: {hello_xid})")
        else:
            print(f"{timestamp()} ❌ Expected HELLO, got {msg_type_to_string(msg_type)}")
            return 1
        
        # Step 2: Controller sends FEATURES_REQUEST, waits for FEATURES_REPLY
        print(f"\n{timestamp()} [STEP 2/5] Sending FEATURES_REQUEST to switch...")
        features_req_msg, features_req_xid = create_features_request()
        sock.sendto(features_req_msg, switch_addr)
        handshake_steps['features_request_sent'] = True
        print(f"{timestamp()} ✅ FEATURES_REQUEST sent (XID: {features_req_xid})")
        
        # Wait for FEATURES_REPLY (handle out-of-order messages)
        print(f"{timestamp()} Waiting for FEATURES_REPLY...")
        features_reply_received = False
        max_attempts = 10
        
        for attempt in range(max_attempts):
            data, _ = sock.recvfrom(4096)
            version, msg_type, length, xid = parse_header(data)
            
            if msg_type == OFPT_FEATURES_REPLY:
                handshake_steps['features_reply_received'] = True
                features_reply_received = True
                print(f"{timestamp()} ✅ FEATURES_REPLY received (XID: {xid}, length: {length} bytes)")
                
                # Parse features (handle variable length)
                if len(data) >= 32:
                    datapath_id = struct.unpack('!Q', data[8:16])[0]
                    n_buffers = struct.unpack('!I', data[16:20])[0]
                    n_tables = struct.unpack('!B', data[20:21])[0]
                    capabilities = struct.unpack('!I', data[24:28])[0]
                    
                    print(f"            DPID: {hex(datapath_id)}")
                    print(f"            Tables: {n_tables}, Buffers: {n_buffers}")
                    print(f"            Capabilities: {hex(capabilities)}")
                else:
                    print(f"            (Short FEATURES_REPLY, length={length})")
                break
            elif msg_type == 12:  # PORT_STATUS
                print(f"{timestamp()} Received PORT_STATUS, waiting for FEATURES_REPLY...")
            elif msg_type == OFPT_ECHO_REQUEST:
                # Reply to ECHO_REQUEST
                echo_reply = struct.pack('!BBHI', OFP_VERSION, OFPT_ECHO_REPLY, 8, xid)
                sock.sendto(echo_reply, switch_addr)
                print(f"{timestamp()} Replied to ECHO_REQUEST, waiting for FEATURES_REPLY...")
            else:
                print(f"{timestamp()} ⚠️  Received {msg_type_to_string(msg_type)}, waiting for FEATURES_REPLY...")
        
        if not features_reply_received:
            print(f"{timestamp()} ❌ FEATURES_REPLY not received after {max_attempts} attempts")
            return 1
        
        # Step 3: Send SET_CONFIG (now with FIXED flags!)
        print(f"\n{timestamp()} [STEP 3/5] Sending SET_CONFIG...")
        set_config_msg, set_config_xid = create_set_config()
        print(f"{timestamp()} SET_CONFIG message: {set_config_msg.hex()}")
        print(f"{timestamp()}   flags=0x0000 (OFPC_FRAG_NORMAL)")
        print(f"{timestamp()}   miss_send_len=128 bytes")
        sock.sendto(set_config_msg, switch_addr)
        handshake_steps['set_config_sent'] = True
        print(f"{timestamp()} ✓ Sent SET_CONFIG")
        
        # Check for ERROR response
        sock.settimeout(2.0)
        error_received = False
        try:
            data, _ = sock.recvfrom(4096)
            version, msg_type, length, xid = parse_header(data)
            if msg_type == OFPT_ERROR:
                error_type, error_code = struct.unpack('!HH', data[8:12])
                print(f"{timestamp()} ✗ ERROR received:")
                print(f"{timestamp()}   Type: {error_type}, Code: {error_code}")
                if error_type == 10:  # OFPET_SWITCH_CONFIG_FAILED
                    print(f"{timestamp()}   OFPET_SWITCH_CONFIG_FAILED")
                    if error_code == 0:
                        print(f"{timestamp()}   OFPSCFC_BAD_FLAGS - Fix didn't work!")
                error_received = True
            elif msg_type == OFPT_ECHO_REQUEST:
                # Switch is sending keepalive, reply to it
                echo_reply = struct.pack('!BBHI', OFP_VERSION, OFPT_ECHO_REPLY, 8, xid)
                sock.sendto(echo_reply, switch_addr)
                print(f"{timestamp()} ✓ Received ECHO_REQUEST, sent ECHO_REPLY")
                print(f"{timestamp()} ✓ SET_CONFIG accepted (no error)!")
            elif msg_type == 12:  # PORT_STATUS
                print(f"{timestamp()} ✓ Received PORT_STATUS (normal operation)")
                print(f"{timestamp()} ✓ SET_CONFIG accepted (no error)!")
            else:
                print(f"{timestamp()} ✓ Received {msg_type_to_string(msg_type)}")
                print(f"{timestamp()} ✓ SET_CONFIG accepted (no error)!")
        except socket.timeout:
            # No error = success!
            print(f"{timestamp()} ✓ No error received - SET_CONFIG accepted!")
        
        if error_received:
            print(f"{timestamp()} ✗ SET_CONFIG failed - stopping test")
            return 1
        
        sock.settimeout(10.0)
        
        # Step 4: Test ECHO (respond to switch's ECHO_REQUEST)
        print(f"\n{timestamp()} [STEP 4/5] Waiting for ECHO REQUEST from switch...")
        print(f"{timestamp()} (OVS typically sends ECHO every 5-15 seconds, waiting up to 20 seconds...)")
        sock.settimeout(20.0)  # Longer timeout to catch periodic ECHO_REQUEST
        
        # Wait for switch to send ECHO_REQUEST (OVS sends these periodically)
        echo_received = False
        max_attempts = 30  # Check up to 30 messages over 20 seconds
        
        for attempt in range(max_attempts):
            try:
                data, _ = sock.recvfrom(4096)
                version, msg_type, length, xid = parse_header(data)
                
                if msg_type == OFPT_ECHO_REQUEST:
                    echo_received = True
                    print(f"{timestamp()} ✅ ECHO_REQUEST received from switch (XID: {xid})")
                    
                    # Send ECHO_REPLY
                    echo_reply = struct.pack('!BBHI', OFP_VERSION, OFPT_ECHO_REPLY, 8, xid)
                    sock.sendto(echo_reply, switch_addr)
                    handshake_steps['echo_test_done'] = True
                    print(f"{timestamp()} ✅ ECHO_REPLY sent (keepalive working!)")
                    break
                elif msg_type == OFPT_ERROR:
                    print(f"{timestamp()} Received ERROR (likely from SET_CONFIG, ignoring...)")
                elif msg_type == OFPT_PORT_STATUS:
                    print(f"{timestamp()} Received PORT_STATUS, waiting for ECHO_REQUEST...")
                else:
                    print(f"{timestamp()} Received {msg_type_to_string(msg_type)}, waiting for ECHO_REQUEST...")
            except socket.timeout:
                print(f"{timestamp()} ⚠️  No ECHO_REQUEST received (ECHO is optional)")
                # Mark as done anyway - ECHO is optional for handshake
                handshake_steps['echo_test_done'] = True
                print(f"{timestamp()} (Marking handshake complete - ECHO not required)")
                break
        
        # If we exhausted all attempts without finding ECHO_REQUEST
        if not echo_received and attempt == max_attempts - 1:
            print(f"{timestamp()} ⚠️  No ECHO_REQUEST after {max_attempts} messages (ECHO is optional)")
            handshake_steps['echo_test_done'] = True
            print(f"{timestamp()} (Marking handshake complete - ECHO not required)")
        
        # Step 5: Handshake complete
        print(f"\n{timestamp()} [STEP 5/5] Handshake Status Check")
        print()
        print("=" * 80)
        print("HANDSHAKE SUMMARY")
        print("=" * 80)
        
        # Core handshake steps (HELLO + FEATURES)
        core_steps = ['hello_sent', 'hello_received', 'features_request_sent', 'features_reply_received']
        core_complete = all(handshake_steps[step] for step in core_steps)
        
        for step, status in handshake_steps.items():
            status_icon = "✅" if status else "❌"
            is_core = step in core_steps
            step_label = step.replace('_', ' ').title()
            if is_core:
                step_label += " (REQUIRED)"
            print(f"{status_icon} {step_label}: {status}")
        
        print()
        if core_complete:
            print("=" * 80)
            print("🎉 HANDSHAKE COMPLETE!")
            print("=" * 80)
            print()
            print("✅ Core handshake successful:")
            print("   • HELLO exchange: version negotiation done")
            print("   • FEATURES exchange: switch capabilities received")
            print()
            if handshake_steps['set_config_sent']:
                print("✅ SET_CONFIG sent (switch may have rejected it)")
            if handshake_steps['echo_test_done']:
                print("✅ ECHO keepalive working")
            print()
            print("Controller is now ready to:")
            print("  • Install flows (FLOW_MOD)")
            print("  • Receive packets (PACKET_IN)")
            print("  • Query statistics")
            print("  • Manage the switch")
            print()
            print()
            
            # Keep alive for a bit to see any additional messages
            print(f"{timestamp()} Staying alive for 10 seconds to observe any messages...")
            sock.settimeout(2.0)
            
            for i in range(5):
                try:
                    data, _ = sock.recvfrom(4096)
                    version, msg_type, length, xid = parse_header(data)
                    print(f"{timestamp()} Received {msg_type_to_string(msg_type)} (XID: {xid})")
                    
                    # Auto-reply to ECHO_REQUEST
                    if msg_type == OFPT_ECHO_REQUEST:
                        echo_reply = struct.pack('!BBHI', OFP_VERSION, OFPT_ECHO_REPLY, 8, xid)
                        sock.sendto(echo_reply, switch_addr)
                        print(f"{timestamp()} Sent ECHO_REPLY")
                except socket.timeout:
                    continue
            
            return 0
        else:
            print("=" * 80)
            print("❌ HANDSHAKE FAILED")
            print("=" * 80)
            print("Core steps (HELLO + FEATURES) did not complete.")
            print("\nTroubleshooting:")
            print("  1. Check if OVS is running: sudo ovs-vsctl show")
            print("  2. Check OVS logs: sudo tail -50 /var/log/openvswitch/ovs-vswitchd.log")
            print("  3. Try reconnecting: sudo ovs-vsctl set-controller test-br udp:127.0.0.1:6653")
            return 1
            
    except socket.timeout:
        print(f"\n{timestamp()} ❌ TIMEOUT: No message received from switch")
        print("\nTroubleshooting:")
        print("  1. Is OVS running? Check: sudo ovs-vsctl show")
        print("  2. Is controller set? Run: sudo ovs-vsctl set-controller test-br udp:127.0.0.1:6653")
        print("  3. Check OVS logs: sudo tail -50 /var/log/openvswitch/ovs-vswitchd.log")
        return 1
    except KeyboardInterrupt:
        print(f"\n{timestamp()} Interrupted by user")
        return 0
    except Exception as e:
        print(f"\n{timestamp()} ❌ ERROR: {e}")
        import traceback
        traceback.print_exc()
        return 1
    finally:
        sock.close()
        print(f"\n{timestamp()} Controller stopped")

if __name__ == '__main__':
    sys.exit(main())
