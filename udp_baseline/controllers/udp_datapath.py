# Wrapper for datapath using UDP

class UDPDatapath:
    def __init__(self, socket, addr, dpid):
        self.socket = socket
        self.address = addr  # (ip, port) tuple
        self.id = dpid
        self.ofproto = None
        self.ofproto_parser = None
        
    def send_msg(self, msg):
        """Send message to switch via UDP"""
        msg_data = msg.serialize()
        return self.socket.sendto(msg_data, self.address)

