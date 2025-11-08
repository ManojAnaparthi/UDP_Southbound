#!/usr/bin/env python3
"""
Simple unit test for UDP OpenFlow message handling.

Tests basic UDP socket operations and OpenFlow message parsing
without requiring full OVS installation.
"""

import socket
import struct
import sys
from pathlib import Path

# Add project root to path
PROJECT_ROOT = Path(__file__).parent.parent.parent
sys.path.insert(0, str(PROJECT_ROOT))

def test_udp_socket_creation():
    """Test basic UDP socket creation and binding"""
    print("[TEST] UDP socket creation...")
    
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        sock.bind(('127.0.0.1', 0))  # Bind to random port
        
        port = sock.getsockname()[1]
        print(f"[✓] UDP socket created and bound to port {port}")
        
        sock.close()
        return True
    except Exception as e:
        print(f"[✗] Failed to create UDP socket: {e}")
        return False

def test_openflow_message_structure():
    """Test OpenFlow message structure"""
    print("[TEST] OpenFlow message structure...")
    
    # OpenFlow 1.3 HELLO message
    version = 4      # OpenFlow 1.3
    msg_type = 0     # HELLO
    length = 8       # Header only
    xid = 12345      # Transaction ID
    
    msg = struct.pack('!BBHI', version, msg_type, length, xid)
    
    if len(msg) == 8:
        print(f"[✓] OpenFlow HELLO message created: {len(msg)} bytes")
        
        # Unpack and verify
        v, t, l, x = struct.unpack('!BBHI', msg)
        if v == version and t == msg_type and l == length and x == xid:
            print(f"[✓] Message unpacked correctly: v={v}, type={t}, len={l}, xid={x}")
            return True
        else:
            print("[✗] Message unpacking failed")
            return False
    else:
        print(f"[✗] Wrong message size: {len(msg)}")
        return False

def test_udp_send_receive():
    """Test UDP send and receive"""
    print("[TEST] UDP send/receive...")
    
    try:
        # Create server socket
        server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        server.bind(('127.0.0.1', 0))
        server.settimeout(2.0)  # 2 second timeout
        
        server_port = server.getsockname()[1]
        print(f"[INFO] Server listening on port {server_port}")
        
        # Create client socket
        client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        
        # Send OpenFlow HELLO
        hello_msg = struct.pack('!BBHI', 4, 0, 8, 999)
        client.sendto(hello_msg, ('127.0.0.1', server_port))
        print(f"[INFO] Client sent HELLO message")
        
        # Receive on server
        data, addr = server.recvfrom(65535)
        print(f"[✓] Server received {len(data)} bytes from {addr}")
        
        # Verify message
        v, t, l, x = struct.unpack('!BBHI', data)
        if v == 4 and t == 0 and l == 8 and x == 999:
            print(f"[✓] Received valid HELLO message: xid={x}")
        else:
            print(f"[✗] Invalid message: v={v}, t={t}, l={l}, x={x}")
            return False
        
        # Send reply
        reply_msg = struct.pack('!BBHI', 4, 0, 8, 999)
        server.sendto(reply_msg, addr)
        print(f"[INFO] Server sent HELLO reply")
        
        # Receive reply on client
        client.settimeout(2.0)
        data, addr = client.recvfrom(65535)
        print(f"[✓] Client received {len(data)} bytes")
        
        server.close()
        client.close()
        
        return True
        
    except socket.timeout:
        print("[✗] Socket timeout - no data received")
        return False
    except Exception as e:
        print(f"[✗] UDP send/receive failed: {e}")
        return False

def test_message_boundary_preservation():
    """Test that UDP preserves message boundaries"""
    print("[TEST] Message boundary preservation...")
    
    try:
        server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        server.bind(('127.0.0.1', 0))
        server.settimeout(2.0)
        
        server_port = server.getsockname()[1]
        
        client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        
        # Send three separate messages
        msg1 = struct.pack('!BBHI', 4, 0, 8, 1)
        msg2 = struct.pack('!BBHI', 4, 0, 8, 2)
        msg3 = struct.pack('!BBHI', 4, 0, 8, 3)
        
        client.sendto(msg1, ('127.0.0.1', server_port))
        client.sendto(msg2, ('127.0.0.1', server_port))
        client.sendto(msg3, ('127.0.0.1', server_port))
        
        print("[INFO] Sent 3 separate messages")
        
        # Receive three separate messages
        xids = []
        for i in range(3):
            data, _ = server.recvfrom(65535)
            _, _, _, xid = struct.unpack('!BBHI', data)
            xids.append(xid)
            print(f"[INFO] Received message {i+1}: xid={xid}")
        
        if xids == [1, 2, 3]:
            print("[✓] Message boundaries preserved correctly")
            server.close()
            client.close()
            return True
        else:
            print(f"[✗] Message boundaries corrupted: {xids}")
            server.close()
            client.close()
            return False
            
    except Exception as e:
        print(f"[✗] Boundary test failed: {e}")
        return False

def main():
    print("\n" + "="*60)
    print(" UDP OpenFlow Unit Tests")
    print("="*60 + "\n")
    
    tests = [
        test_udp_socket_creation,
        test_openflow_message_structure,
        test_udp_send_receive,
        test_message_boundary_preservation,
    ]
    
    passed = 0
    total = len(tests)
    
    for test in tests:
        if test():
            passed += 1
        print()
    
    print("="*60)
    print(f" Results: {passed}/{total} tests passed")
    print("="*60 + "\n")
    
    return 0 if passed == total else 1

if __name__ == "__main__":
    sys.exit(main())
