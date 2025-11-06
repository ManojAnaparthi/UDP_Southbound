# Custom UDP socket handler for Ryu

import socket
import struct
from ryu.lib import hub

class UDPOpenFlowSocket:
    def __init__(self, address=('0.0.0.0', 6633)):
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.socket.bind(address)
        self.clients = {}  # Store {dpid: (ip, port)}
        self.recv_buffer = {}
        
    def recv_msg(self, max_size=65535):
        """Receive OpenFlow message over UDP"""
        data, addr = self.socket.recvfrom(max_size)
        return data, addr
        
    def send_msg(self, data, addr):
        """Send OpenFlow message over UDP"""
        return self.socket.sendto(data, addr)
        
    def close(self):
        self.socket.close()

