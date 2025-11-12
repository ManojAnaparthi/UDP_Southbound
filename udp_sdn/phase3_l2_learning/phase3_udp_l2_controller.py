#!/usr/bin/env python3
"""
Phase 3: Ryu UDP Controller with L2 Learning
=============================================

Complete L2 learning switch over UDP:
- MAC address learning from PACKET_IN
- Flow installation for known MAC pairs
- Packet flooding for unknown destinations
- Per-switch forwarding tables

Author: UDP SDN Project
Date: November 12, 2025
"""

from ryu.base import app_manager
from ryu.ofproto import ofproto_v1_3
import socket
import struct
import threading
import logging
from datetime import datetime

# Configure logging
logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s - %(name)s - %(levelname)s - %(message)s'
)
logger = logging.getLogger(__name__)


class UDPOpenFlowL2Controller(app_manager.RyuApp):
    """
    L2 learning switch controller over UDP.
    
    Implements:
    - OpenFlow 1.3 protocol over UDP
    - MAC address learning
    - Dynamic flow installation
    - Packet flooding for unknown destinations
    """
    
    OFP_VERSIONS = [ofproto_v1_3.OFP_VERSION]
    
    # OpenFlow message types
    OFPT_HELLO = 0
    OFPT_ERROR = 1
    OFPT_ECHO_REQUEST = 2
    OFPT_ECHO_REPLY = 3
    OFPT_FEATURES_REQUEST = 5
    OFPT_FEATURES_REPLY = 6
    OFPT_SET_CONFIG = 9
    OFPT_PACKET_IN = 10
    OFPT_FLOW_MOD = 14
    OFPT_PACKET_OUT = 13
    
    # OpenFlow ports
    OFPP_FLOOD = 0xfffffffb
    OFPP_CONTROLLER = 0xfffffffd
    OFPP_ANY = 0xffffffff
    
    def __init__(self, *args, **kwargs):
        super(UDPOpenFlowL2Controller, self).__init__(*args, **kwargs)
        
        # UDP configuration
        self.udp_host = '0.0.0.0'
        self.udp_port = 6653
        
        # Switch tracking
        self.switches = {}  # addr -> {datapath_id, version, last_seen}
        self.dpid_to_addr = {}  # datapath_id -> addr (for reverse lookup)
        
        # MAC learning tables (per switch)
        self.mac_to_port = {}  # datapath_id -> {mac_address: port_no}
        
        # Initialize UDP socket
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sock.bind((self.udp_host, self.udp_port))
        
        logger.info("="*70)
        logger.info("UDP OpenFlow L2 Learning Controller Starting")
        logger.info("="*70)
        logger.info("Listening on {}:{}".format(self.udp_host, self.udp_port))
        
        # Start UDP listener thread
        self.running = True
        self.listener_thread = threading.Thread(target=self._udp_listener)
        self.listener_thread.daemon = True
        self.listener_thread.start()
        
        logger.info("UDP listener thread started")
        logger.info("L2 learning enabled")
    
    def _udp_listener(self):
        """Background thread to receive UDP messages."""
        logger.debug("UDP listener active, waiting for messages...")
        
        while self.running:
            try:
                data, addr = self.sock.recvfrom(65535)
                self._handle_udp_message(data, addr)
            except Exception as e:
                logger.error("Error in UDP listener: {}".format(e))
    
    def _handle_udp_message(self, data, addr):
        """Parse and route OpenFlow message."""
        if len(data) < 8:
            logger.warning("Message too short from {}: {} bytes".format(addr, len(data)))
            return
        
        # Parse OpenFlow header
        version, msg_type, length, xid = struct.unpack('!BBHI', data[:8])
        
        # Route message to handler
        if msg_type == self.OFPT_HELLO:
            self._handle_hello(data, addr, version, xid)
        elif msg_type == self.OFPT_ECHO_REQUEST:
            self._handle_echo_request(data, addr, version, xid)
        elif msg_type == self.OFPT_FEATURES_REPLY:
            self._handle_features_reply(data, addr, version, xid)
        elif msg_type == self.OFPT_PACKET_IN:
            self._handle_packet_in(data, addr, version, xid)
    
    def _send_message(self, data, addr):
        """Send OpenFlow message via UDP."""
        try:
            self.sock.sendto(data, addr)
        except Exception as e:
            logger.error("Failed to send to {}: {}".format(addr, e))
    
    def _handle_hello(self, data, addr, version, xid):
        """Handle HELLO message and initiate handshake."""
        logger.info("HELLO from {}:{}".format(addr[0], addr[1]))
        
        # Send HELLO reply
        hello_reply = struct.pack('!BBHI', version, self.OFPT_HELLO, 8, xid)
        self._send_message(hello_reply, addr)
        
        # Send FEATURES_REQUEST
        features_xid = xid + 1
        features_request = struct.pack('!BBHI', 
                                      version, 
                                      self.OFPT_FEATURES_REQUEST, 
                                      8, 
                                      features_xid)
        self._send_message(features_request, addr)
    
    def _handle_echo_request(self, data, addr, version, xid):
        """Handle ECHO_REQUEST (keepalive)."""
        echo_reply = struct.pack('!BBHI', version, self.OFPT_ECHO_REPLY, 8, xid)
        self._send_message(echo_reply, addr)
    
    def _handle_features_reply(self, data, addr, version, xid):
        """Handle FEATURES_REPLY and install table-miss flow."""
        if len(data) < 32:
            logger.warning("FEATURES_REPLY too short: {} bytes".format(len(data)))
            return
        
        # Extract datapath ID
        dpid_bytes = data[8:16]
        dpid = struct.unpack('!Q', dpid_bytes)[0]
        
        logger.info("="*70)
        logger.info("Switch connected: DPID 0x{:016x} from {}:{}".format(
            dpid, addr[0], addr[1]))
        logger.info("="*70)
        
        # Track switch (update address if reconnected)
        self.switches[addr] = {
            'datapath_id': dpid,
            'version': version,
            'last_seen': datetime.now()
        }
        self.dpid_to_addr[dpid] = addr
        
        # Initialize MAC table for this switch
        if dpid not in self.mac_to_port:
            self.mac_to_port[dpid] = {}
            logger.info("Initialized MAC table for DPID 0x{:016x}".format(dpid))
        
        # Configure switch to send full packets to controller
        self._send_set_config(addr, version)
        
        # Install table-miss flow
        self._install_table_miss_flow(addr, dpid, version)
    
    def _send_set_config(self, addr, version):
        """
        Send SET_CONFIG to configure switch.
        
        Sets miss_send_len to 0xffff (no limit) so switch sends full
        packets to controller on table-miss.
        """
        logger.info("Sending SET_CONFIG (miss_send_len=0xffff)")
        
        xid = 0x00100000
        flags = 0  # OFPC_FRAG_NORMAL
        miss_send_len = 0xffff  # Send full packet to controller
        
        # Build SET_CONFIG message
        # struct ofp_switch_config {
        #     struct ofp_header header;
        #     uint16_t flags;
        #     uint16_t miss_send_len;
        # };
        config_body = struct.pack('!HH', flags, miss_send_len)
        total_len = 8 + len(config_body)  # Header + config
        
        header = struct.pack('!BBHI', version, self.OFPT_SET_CONFIG, total_len, xid)
        set_config = header + config_body
        
        self._send_message(set_config, addr)
        logger.info("  -> SET_CONFIG sent")
    
    def _install_table_miss_flow(self, addr, dpid, version):
        """Install table-miss flow (priority=0, action=CONTROLLER)."""
        logger.info("Installing table-miss flow on DPID 0x{:016x}".format(dpid))
        
        xid = 0x10000000
        
        # Build FLOW_MOD message
        flow_mod = self._build_flow_mod(
            version=version,
            xid=xid,
            priority=0,
            match_fields=[],  # Match all
            instructions=[('OUTPUT', self.OFPP_CONTROLLER, 0xffff)]
        )
        
        self._send_message(flow_mod, addr)
        logger.info("  -> Table-miss flow installed")
    
    def _handle_packet_in(self, data, addr, version, xid):
        """
        Handle PACKET_IN with L2 learning logic.
        
        Steps:
        1. Parse PACKET_IN to extract in_port and Ethernet frame
        2. Learn source MAC -> port mapping
        3. Lookup destination MAC
        4. If known: install flow
        5. If unknown: flood packet
        """
        if len(data) < 32:
            return
        
        # Get switch info
        switch_info = self.switches.get(addr)
        if not switch_info:
            logger.warning("PACKET_IN from unknown switch {}".format(addr))
            return
        
        dpid = switch_info['datapath_id']
        
        # Parse PACKET_IN (OpenFlow 1.3)
        # Header (8) + buffer_id (4) + total_len (2) + reason (1) + 
        # table_id (1) + cookie (8) + match...
        
        buffer_id = struct.unpack('!I', data[8:12])[0]
        total_len = struct.unpack('!H', data[12:14])[0]
        
        # Parse match to get in_port
        # Match starts at offset 24
        # match_type (2) + match_len (2) + OXM TLVs...
        match_offset = 24
        match_type, match_len = struct.unpack('!HH', data[match_offset:match_offset+4])
        
        in_port = None
        # Parse OXM TLVs to find OFPXMT_OFB_IN_PORT
        tlv_offset = match_offset + 4
        match_end = match_offset + ((match_len + 7) // 8) * 8  # Padded to 8 bytes
        
        while tlv_offset < match_end and tlv_offset < len(data) - 4:
            if tlv_offset + 4 > len(data):
                break
            oxm_class = struct.unpack('!H', data[tlv_offset:tlv_offset+2])[0]
            oxm_field_len = struct.unpack('!B', data[tlv_offset+2:tlv_offset+3])[0]
            oxm_field = (oxm_field_len >> 1) & 0x7f
            oxm_len = oxm_field_len & 0x01
            length = struct.unpack('!B', data[tlv_offset+3:tlv_offset+4])[0]
            
            # OFPXMT_OFB_IN_PORT = 0 (field number)
            if oxm_class == 0x8000 and oxm_field == 0:
                in_port = struct.unpack('!I', data[tlv_offset+4:tlv_offset+8])[0]
                break
            
            tlv_offset += 4 + length
        
        # Ethernet frame starts after match (padded)
        frame_offset = match_end + 2  # +2 for padding
        if frame_offset >= len(data):
            logger.warning("No Ethernet frame in PACKET_IN")
            return
        
        frame = data[frame_offset:]
        
        if len(frame) < 14:
            logger.warning("Ethernet frame too short: {} bytes".format(len(frame)))
            return
        
        # Parse Ethernet header
        dst_mac = frame[0:6]
        src_mac = frame[6:12]
        
        dst_mac_str = ':'.join('{:02x}'.format(b) for b in dst_mac)
        src_mac_str = ':'.join('{:02x}'.format(b) for b in src_mac)
        
        logger.info("PACKET_IN from DPID 0x{:016x}".format(dpid))
        logger.info("  In Port: {}".format(in_port if in_port else "Unknown"))
        logger.info("  Src MAC: {}".format(src_mac_str))
        logger.info("  Dst MAC: {}".format(dst_mac_str))
        
        # Learn source MAC
        if in_port:
            if src_mac_str not in self.mac_to_port.get(dpid, {}):
                logger.info("  -> Learning: {} at port {}".format(src_mac_str, in_port))
                self.mac_to_port[dpid][src_mac_str] = in_port
            
            # Lookup destination MAC
            out_port = self.mac_to_port.get(dpid, {}).get(dst_mac_str)
            
            if out_port:
                logger.info("  -> Destination known: port {}".format(out_port))
                logger.info("  -> Installing flow for {} -> {}".format(src_mac_str, dst_mac_str))
                self._install_l2_flow(addr, dpid, version, src_mac, dst_mac, out_port)
                
                # Also send this packet out
                self._send_packet_out(addr, version, buffer_id, in_port, out_port, frame)
            else:
                logger.info("  -> Destination unknown, flooding")
                self._send_packet_out(addr, version, buffer_id, in_port, self.OFPP_FLOOD, frame)
    
    def _install_l2_flow(self, addr, dpid, version, src_mac, dst_mac, out_port):
        """Install flow for specific MAC pair."""
        xid = 0x20000000
        
        # Match on destination MAC
        match_fields = [
            ('ETH_DST', dst_mac)
        ]
        
        # Output to learned port
        instructions = [
            ('OUTPUT', out_port, 0)  # No max_len for normal output
        ]
        
        flow_mod = self._build_flow_mod(
            version=version,
            xid=xid,
            priority=1,  # Higher than table-miss
            idle_timeout=30,  # Remove after 30s of inactivity
            hard_timeout=300,  # Remove after 5 minutes
            match_fields=match_fields,
            instructions=instructions
        )
        
        self._send_message(flow_mod, addr)
        logger.info("  -> Flow installed (priority=1, idle=30s, hard=300s)")
    
    def _send_packet_out(self, addr, version, buffer_id, in_port, out_port, frame):
        """Send PACKET_OUT to forward/flood packet."""
        xid = 0x30000000
        
        # PACKET_OUT structure:
        # header (8) + buffer_id (4) + in_port (4) + actions_len (2) + 
        # pad (6) + actions + data
        
        # Build OUTPUT action
        action_type = 0  # OFPAT_OUTPUT
        action_len = 16
        max_len = 0 if out_port != self.OFPP_CONTROLLER else 0xffff
        
        action = struct.pack('!HHIH', action_type, action_len, out_port, max_len)
        action += b'\x00' * 6  # Padding
        
        actions_len = len(action)
        
        # Build PACKET_OUT
        packet_out = struct.pack('!BBHI', version, self.OFPT_PACKET_OUT, 0, xid)
        packet_out += struct.pack('!IIHxxxxxx', buffer_id, in_port if in_port else 0xffffffff, actions_len)
        packet_out += action
        
        # Add frame data if not buffered
        if buffer_id == 0xffffffff:
            packet_out += frame
        
        # Update length
        total_len = len(packet_out)
        packet_out = struct.pack('!BBHI', version, self.OFPT_PACKET_OUT, total_len, xid) + packet_out[8:]
        
        self._send_message(packet_out, addr)
    
    def _build_flow_mod(self, version, xid, priority, match_fields=None, 
                       instructions=None, idle_timeout=0, hard_timeout=0):
        """
        Build FLOW_MOD message (OpenFlow 1.3).
        
        Args:
            version: OpenFlow version
            xid: Transaction ID
            priority: Flow priority
            match_fields: List of (field_name, value) tuples
            instructions: List of (action_name, port, max_len) tuples
            idle_timeout: Idle timeout in seconds
            hard_timeout: Hard timeout in seconds
        """
        if match_fields is None:
            match_fields = []
        if instructions is None:
            instructions = []
        
        # Build match
        match_tlvs = b''
        for field_name, value in match_fields:
            if field_name == 'ETH_DST':
                # OXM_OF_ETH_DST (oxm_class=0x8000, field=3, len=6)
                oxm_header = struct.pack('!HBB', 0x8000, (3 << 1), 6)
                match_tlvs += oxm_header + value
        
        match_len = 4 + len(match_tlvs)  # type(2) + length(2) + TLVs
        match_padded_len = ((match_len + 7) // 8) * 8
        match_padding = b'\x00' * (match_padded_len - match_len)
        
        match = struct.pack('!HH', 1, match_len) + match_tlvs + match_padding
        
        # Build instructions
        inst_data = b''
        for action_name, port, max_len in instructions:
            if action_name == 'OUTPUT':
                # Build OUTPUT action (16 bytes total)
                action_type = 0  # OFPAT_OUTPUT
                action_len = 16
                action = struct.pack('!HHIH', action_type, action_len, port, max_len)
                action += b'\x00' * 6  # Padding to 16 bytes
                
                # Build APPLY_ACTIONS instruction
                inst_type = 4  # OFPIT_APPLY_ACTIONS
                inst_len = 8 + len(action)  # Header (8) + actions
                inst = struct.pack('!HHI', inst_type, inst_len, 0)  # type, len, padding
                inst += action
                inst_data += inst
        
        # Build FLOW_MOD body (48 bytes + match + instructions)
        cookie = 0
        cookie_mask = 0
        table_id = 0
        command = 0  # OFPFC_ADD
        buffer_id = 0xffffffff
        out_port = 0xffffffff
        out_group = 0xffffffff
        flags = 0x0001  # OFPFF_SEND_FLOW_REM
        
        # Pack flow_mod body (correct format for OpenFlow 1.3)
        flow_body = struct.pack('!QQ', cookie, cookie_mask)
        flow_body += struct.pack('!BBHHHIII', 
                               table_id, command, idle_timeout, hard_timeout,
                               priority, buffer_id, out_port, out_group)
        flow_body += struct.pack('!HH', flags, 0)  # flags + pad
        
        # Assemble: header + body + match + instructions
        flow_mod = flow_body + match + inst_data
        
        # Add header with correct length
        total_len = 8 + len(flow_mod)
        header = struct.pack('!BBHI', version, self.OFPT_FLOW_MOD, total_len, xid)
        
        return header + flow_mod


if __name__ == '__main__':
    # When run directly, start controller
    logger.info("Starting UDP OpenFlow L2 Learning Controller...")
    controller = UDPOpenFlowL2Controller()
    
    try:
        # Keep alive
        import time
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        logger.info("\nShutting down...")
        controller.running = False
        controller.sock.close()
