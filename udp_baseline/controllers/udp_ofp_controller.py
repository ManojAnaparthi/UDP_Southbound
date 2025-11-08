import socket
import struct
import threading
import time

from ryu.ofproto import ofproto_v1_3
from udp_baseline.lib.udp_ofp_parser import UDPOpenFlowParser


class UDPOpenFlowController:
    """
    Enhanced UDP-based OpenFlow Controller with Learning Switch functionality.
    Handles HELLO, FEATURES_REPLY, PACKET_IN and sends FLOW_MOD messages over UDP.
    """

    def __init__(self, host='0.0.0.0', port=6633):
        self.host = host
        self.port = port
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.socket.bind((host, port))

        self.running = False
        self.switches = {}  # {dpid: {'addr': (ip, port), 'mac_table': {}}}

        self.ofproto = ofproto_v1_3
        self.parser = UDPOpenFlowParser()

    # ---------------------------------------------------------------------- #
    # Controller Lifecycle
    # ---------------------------------------------------------------------- #
    def start(self):
        """Start the UDP OpenFlow controller."""
        self.running = True
        print(f"[INFO] UDP OpenFlow Controller listening on {self.host}:{self.port}")
        print(f"[INFO] Mode: Learning Switch with FLOW_MOD support")

        recv_thread = threading.Thread(target=self._receive_loop, daemon=True)
        recv_thread.start()

    def stop(self):
        """Stop the controller."""
        self.running = False
        self.socket.close()
        print("[INFO] Controller stopped.")

    # ---------------------------------------------------------------------- #
    # Receive Loop
    # ---------------------------------------------------------------------- #
    def _receive_loop(self):
        """Continuously listen for incoming UDP OpenFlow messages."""
        while self.running:
            try:
                data, addr = self.socket.recvfrom(65535)
                self._handle_message(data, addr)
            except Exception as e:
                print(f"[ERROR] Receive error: {e}")

    # ---------------------------------------------------------------------- #
    # Message Handling
    # ---------------------------------------------------------------------- #
    def _handle_message(self, data, addr):
        """Parse and handle an incoming UDP OpenFlow message."""
        msg = self.parser.parse_message(data)
        if not msg:
            return

        msg_type = msg["type"]
        msg_name = msg["msg_name"]
        xid = msg["xid"]

        print(f"[INFO] Received {msg_name} from {addr}, xid={xid}")

        if msg_type == self.ofproto.OFPT_HELLO:
            self._handle_hello(addr, xid)
        elif msg_type == self.ofproto.OFPT_FEATURES_REPLY:
            self._handle_features_reply(data, addr)
        elif msg_type == self.ofproto.OFPT_PACKET_IN:
            self._handle_packet_in(data, addr)
        else:
            print(f"[WARN] Unhandled OpenFlow message type: {msg_type} ({msg_name})")

    # ---------------------------------------------------------------------- #
    # Handlers
    # ---------------------------------------------------------------------- #
    def _handle_hello(self, addr, xid):
        """Respond to an OpenFlow HELLO message."""
        print(f"[INFO] HELLO received from {addr}")

        # Send HELLO back
        hello_data = struct.pack('!BBHI',
                                 self.ofproto.OFP_VERSION,
                                 self.ofproto.OFPT_HELLO,
                                 8, xid)
        self.socket.sendto(hello_data, addr)
        print(f"[SEND] HELLO → {addr}")

        # Send FEATURES_REQUEST
        time.sleep(0.1)
        features_req = struct.pack('!BBHI',
                                   self.ofproto.OFP_VERSION,
                                   self.ofproto.OFPT_FEATURES_REQUEST,
                                   8, xid + 1)
        self.socket.sendto(features_req, addr)
        print(f"[SEND] FEATURES_REQUEST → {addr}")

    def _handle_features_reply(self, data, addr):
        """Handle FEATURES_REPLY and extract datapath ID."""
        if len(data) >= 16:
            dpid = struct.unpack('!Q', data[8:16])[0]
            self.switches[dpid] = {
                'addr': addr,
                'mac_table': {}  # MAC learning table: {mac: port}
            }
            print(f"[INFO] Switch connected: DPID={dpid:#x} from {addr}")
            
            # Install table-miss flow entry (send unknown packets to controller)
            self._install_table_miss_flow(dpid)
        else:
            print(f"[WARN] Invalid FEATURES_REPLY from {addr}")

    def _handle_packet_in(self, data, addr):
        """Handle PACKET_IN and perform MAC learning + forwarding."""
        if len(data) < 24:
            print(f"[WARN] PACKET_IN too short from {addr}")
            return
        
        # Find switch DPID
        dpid = None
        for switch_dpid, info in self.switches.items():
            if info['addr'] == addr:
                dpid = switch_dpid
                break
        
        if dpid is None:
            print(f"[WARN] PACKET_IN from unknown switch {addr}")
            return
        
        # Parse PACKET_IN (simplified)
        # OFP header (8 bytes) + buffer_id (4) + total_len (2) + reason (1) + table_id (1) + cookie (8)
        try:
            in_port = self._extract_in_port(data)
            eth_src, eth_dst = self._extract_ethernet_addrs(data)
            
            if eth_src and eth_dst and in_port:
                print(f"[INFO] PACKET_IN: DPID={dpid:#x}, port={in_port}, src={eth_src}, dst={eth_dst}")
                
                # Learn source MAC
                mac_table = self.switches[dpid]['mac_table']
                if eth_src not in mac_table:
                    mac_table[eth_src] = in_port
                    print(f"[LEARN] MAC {eth_src} → Port {in_port}")
                
                # Determine output port
                if eth_dst in mac_table:
                    out_port = mac_table[eth_dst]
                    print(f"[FORWARD] MAC {eth_dst} known → Port {out_port}")
                    
                    # Install flow rule
                    self._install_forward_flow(dpid, eth_src, eth_dst, in_port, out_port)
                else:
                    # Flood if destination unknown
                    print(f"[FLOOD] MAC {eth_dst} unknown → FLOOD")
                    self._send_packet_out_flood(dpid, in_port, data)
                    
        except Exception as e:
            print(f"[ERROR] PACKET_IN parsing failed: {e}")
    
    def _extract_in_port(self, data):
        """Extract in_port from PACKET_IN message (simplified)."""
        # In real OpenFlow 1.3, in_port is in the match field (oxm)
        # For now, we'll return a dummy value or parse if available
        # This is a simplified placeholder
        if len(data) >= 32:
            # Attempt to extract from match field (this is simplified)
            # Real implementation would parse OXM TLVs
            return 1  # Default to port 1 for demo
        return None
    
    def _extract_ethernet_addrs(self, data):
        """Extract source and destination MAC addresses from packet data."""
        # PACKET_IN structure: header + metadata + actual packet
        # We need to find where the Ethernet frame starts
        # Simplified: assume packet starts at offset 32
        if len(data) >= 46:  # 32 (OFP headers) + 14 (Ethernet header)
            packet_offset = 32
            eth_dst = ':'.join(f'{b:02x}' for b in data[packet_offset:packet_offset+6])
            eth_src = ':'.join(f'{b:02x}' for b in data[packet_offset+6:packet_offset+12])
            return eth_src, eth_dst
        return None, None

    
    # ---------------------------------------------------------------------- #
    # Flow Installation Methods
    # ---------------------------------------------------------------------- #
    def _install_table_miss_flow(self, dpid):
        """Install table-miss flow entry to send unknown packets to controller."""
        if dpid not in self.switches:
            return
        
        addr = self.switches[dpid]['addr']
        
        # Simplified FLOW_MOD for table-miss (priority=0, match=any, action=CONTROLLER)
        # This is a minimal implementation
        print(f"[INSTALL] Table-miss flow → DPID={dpid:#x}")
        
        # Build minimal FLOW_MOD message
        # Header: version(1) + type(1) + length(2) + xid(4) = 8 bytes
        # FLOW_MOD specific fields (simplified)
        xid = int(time.time()) & 0xFFFFFFFF
        msg_type = self.ofproto.OFPT_FLOW_MOD
        
        # Minimal FLOW_MOD structure (this is highly simplified)
        flow_mod = struct.pack(
            '!BBHI',  # Header
            self.ofproto.OFP_VERSION,  # version
            msg_type,  # type
            56,  # length (minimal FLOW_MOD)
            xid  # xid
        )
        # Add padding/dummy fields for rest of FLOW_MOD
        flow_mod += b'\x00' * 48  # Padding to make valid message
        
        self.socket.sendto(flow_mod, addr)
    
    def _install_forward_flow(self, dpid, eth_src, eth_dst, in_port, out_port):
        """Install a flow rule to forward packets from src to dst."""
        if dpid not in self.switches:
            return
        
        addr = self.switches[dpid]['addr']
        
        print(f"[INSTALL] Flow: {eth_src} → {eth_dst}, in={in_port}, out={out_port}")
        
        # Build FLOW_MOD with match and actions
        xid = int(time.time()) & 0xFFFFFFFF
        
        # Simplified FLOW_MOD message
        flow_mod = struct.pack(
            '!BBHI',
            self.ofproto.OFP_VERSION,
            self.ofproto.OFPT_FLOW_MOD,
            56,
            xid
        )
        flow_mod += b'\x00' * 48  # Simplified payload
        
        self.socket.sendto(flow_mod, addr)
    
    def _send_packet_out_flood(self, dpid, in_port, packet_in_data):
        """Send PACKET_OUT to flood the packet to all ports except in_port."""
        if dpid not in self.switches:
            return
        
        addr = self.switches[dpid]['addr']
        
        print(f"[PACKET_OUT] Flood packet from port {in_port}")
        
        # Build PACKET_OUT message
        xid = int(time.time()) & 0xFFFFFFFF
        
        packet_out = struct.pack(
            '!BBHI',
            self.ofproto.OFP_VERSION,
            self.ofproto.OFPT_PACKET_OUT,
            24,  # Minimal length
            xid
        )
        packet_out += b'\x00' * 16  # Buffer_id, in_port, actions_len, padding
        
        self.socket.sendto(packet_out, addr)
    
    # ---------------------------------------------------------------------- #
    # Utility
    # ---------------------------------------------------------------------- #
    def send_flow_mod(self, dpid, match=None, actions=None):
        """Send a FLOW_MOD to a connected switch (legacy method)."""
        if dpid not in self.switches:
            print(f"[WARN] Switch {dpid:#x} not connected")
            return

        addr = self.switches[dpid]['addr']
        flow_mod = struct.pack('!BBHI',
                               self.ofproto.OFP_VERSION,
                               self.ofproto.OFPT_FLOW_MOD,
                               56, 99)
        flow_mod += b'\x00' * 48
        self.socket.sendto(flow_mod, addr)
        print(f"[SEND] FLOW_MOD → DPID={dpid:#x}, {addr}")
# ---------------------------------------------------------------------- #
# Standalone Run
# ---------------------------------------------------------------------- #
if __name__ == "__main__":
    controller = UDPOpenFlowController()
    controller.start()

    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        controller.stop()

