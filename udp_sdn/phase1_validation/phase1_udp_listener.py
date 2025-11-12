#!/usr/bin/env python3
"""
Phase 1: Minimal UDP Listener for OVS OpenFlow Messages
========================================================

Purpose:
  Validate that OVS can send OpenFlow messages over UDP.
  Capture and decode HELLO, ECHO_REQUEST, and PACKET_IN messages.

Usage:
  1. Terminal 1: python3 phase1_udp_listener.py
  2. Terminal 2: sudo ovs-vsctl set-controller br-udp-test udp:127.0.0.1:6653

Expected Results:
  - HELLO message (8 bytes, type 0x00)
  - ECHO_REQUEST messages (8 bytes, type 0x02)
  - PACKET_IN messages (variable size, type 0x0a)
"""

import socket
import struct
import sys
from datetime import datetime

# OpenFlow message types
OF_MESSAGE_TYPES = {
    0x00: "HELLO",
    0x01: "ERROR",
    0x02: "ECHO_REQUEST",
    0x03: "ECHO_REPLY",
    0x04: "EXPERIMENTER",
    0x05: "FEATURES_REQUEST",
    0x06: "FEATURES_REPLY",
    0x07: "GET_CONFIG_REQUEST",
    0x08: "GET_CONFIG_REPLY",
    0x09: "SET_CONFIG",
    0x0a: "PACKET_IN",
    0x0b: "FLOW_REMOVED",
    0x0c: "PORT_STATUS",
    0x0d: "PACKET_OUT",
    0x0e: "FLOW_MOD",
    0x0f: "GROUP_MOD",
    0x10: "PORT_MOD",
    0x11: "TABLE_MOD",
}

# OpenFlow versions
OF_VERSIONS = {
    0x01: "1.0",
    0x02: "1.1",
    0x03: "1.2",
    0x04: "1.3",
    0x05: "1.4",
    0x06: "1.5",
}


def parse_openflow_header(data):
    """
    Parse OpenFlow message header.
    
    Header format (8 bytes):
      - version (1 byte)
      - type (1 byte)
      - length (2 bytes)
      - xid (4 bytes)
    """
    if len(data) < 8:
        return None
    
    version, msg_type, length, xid = struct.unpack('!BBHI', data[:8])
    
    return {
        'version': version,
        'version_str': OF_VERSIONS.get(version, "Unknown({:#x})".format(version)),
        'type': msg_type,
        'type_str': OF_MESSAGE_TYPES.get(msg_type, "Unknown({:#x})".format(msg_type)),
        'length': length,
        'xid': xid,
        'payload': data[8:length] if length <= len(data) else data[8:]
    }


def log_message(msg_info, addr, data):
    """Log received OpenFlow message with details."""
    timestamp = datetime.now().strftime("%H:%M:%S.%f")[:-3]
    
    print("\n" + "="*70)
    print("[{}] Message from {}:{}".format(timestamp, addr[0], addr[1]))
    print("="*70)
    print("  Version:    OpenFlow {} (0x{:02x})".format(msg_info['version_str'], msg_info['version']))
    print("  Type:       {} (0x{:02x})".format(msg_info['type_str'], msg_info['type']))
    print("  Length:     {} bytes".format(msg_info['length']))
    print("  XID:        0x{:08x}".format(msg_info['xid']))
    raw_hex = ''.join('{:02x}'.format(b) for b in data[:min(32, len(data))])
    print("  Raw Data:   {}".format(raw_hex))
    
    if msg_info['payload']:
        print("  Payload:    {} bytes".format(len(msg_info['payload'])))
        if len(msg_info['payload']) <= 64:
            payload_hex = ''.join('{:02x}'.format(b) for b in msg_info['payload'])
            print("              {}".format(payload_hex))
    
    print("="*70)


def main():
    """Main UDP listener loop."""
    HOST = '0.0.0.0'  # Listen on all interfaces
    PORT = 6653        # Standard OpenFlow port
    
    print("="*70)
    print("Phase 1: OVS UDP Validation - Minimal Listener")
    print("="*70)
    print("Starting UDP listener on {}:{}".format(HOST, PORT))
    print("Waiting for OpenFlow messages from OVS...")
    print("\nTo connect OVS switch:")
    print("  sudo ovs-vsctl set-controller br-udp-test udp:127.0.0.1:6653")
    print("\nPress Ctrl+C to stop\n")
    
    # Create UDP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    
    try:
        sock.bind((HOST, PORT))
        print("✓ Successfully bound to {}:{}".format(HOST, PORT))
        print("✓ Socket ready, waiting for messages...\n")
        
        message_count = 0
        
        while True:
            # Receive data
            data, addr = sock.recvfrom(65535)  # Max UDP packet size
            message_count += 1
            
            print("\n>>> Message #{} received ({} bytes)".format(message_count, len(data)))
            
            # Parse OpenFlow header
            msg_info = parse_openflow_header(data)
            
            if msg_info:
                log_message(msg_info, addr, data)
                
                # Special handling for specific message types
                if msg_info['type'] == 0x00:  # HELLO
                    print("  Note: HELLO received - switch attempting handshake")
                    print("        (Not replying - this is validation only)")
                
                elif msg_info['type'] == 0x02:  # ECHO_REQUEST
                    print("  Note: ECHO_REQUEST received - keepalive message")
                    print("        (Not replying - this is validation only)")
                
                elif msg_info['type'] == 0x0a:  # PACKET_IN
                    print("  Note: PACKET_IN received - switch forwarding packet")
                    print("        This means switch is sending data plane packets!")
                
            else:
                print("  WARNING: Could not parse OpenFlow header (too short?)")
                raw_hex = ''.join('{:02x}'.format(b) for b in data)
                print("  Raw Data: {}".format(raw_hex))
    
    except KeyboardInterrupt:
        print("\n\n" + "="*70)
        print("Shutting down... Received {} messages total".format(message_count))
        print("="*70)
    
    except Exception as e:
        print("\nERROR: {}".format(e), file=sys.stderr)
        import traceback
        traceback.print_exc()
        return 1
    
    finally:
        sock.close()
        print("Socket closed.")
    
    return 0


if __name__ == "__main__":
    sys.exit(main())
