#!/usr/bin/env python3
"""
Phase 2: Basic Ryu UDP Controller
==================================

Complete OpenFlow protocol handler over UDP:
- HELLO exchange
- FEATURES_REQUEST/REPLY
- ECHO_REQUEST/REPLY (keepalive)
- PACKET_IN processing
- Table-miss flow installation

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
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


class UDPOpenFlowController(app_manager.RyuApp):
    """
    Ryu controller that communicates with OVS over UDP.
    
    Implements OpenFlow 1.3 protocol over UDP sockets.
    """
    
    OFP_VERSIONS = [ofproto_v1_3.OFP_VERSION]
    
    # OpenFlow message types
    OFPT_HELLO = 0
    OFPT_ERROR = 1
    OFPT_ECHO_REQUEST = 2
    OFPT_ECHO_REPLY = 3
    OFPT_FEATURES_REQUEST = 5
    OFPT_FEATURES_REPLY = 6
    OFPT_PACKET_IN = 10
    OFPT_FLOW_MOD = 14
    OFPT_PACKET_OUT = 13
    
    def __init__(self, *args, **kwargs):
        super(UDPOpenFlowController, self).__init__(*args, **kwargs)
        
        # UDP configuration
        self.udp_host = '0.0.0.0'
        self.udp_port = 6653
        
        # Switch tracking
        self.switches = {}  # addr -> {datapath_id, version, last_seen}
        
        # Initialize UDP socket
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sock.bind((self.udp_host, self.udp_port))
        
        logger.info("="*70)
        logger.info("UDP OpenFlow Controller Starting")
        logger.info("="*70)
        logger.info("Listening on {}:{}".format(self.udp_host, self.udp_port))
        
        # Start UDP listener thread
        self.running = True
        self.listener_thread = threading.Thread(target=self._udp_listener)
        self.listener_thread.daemon = True
        self.listener_thread.start()
        
        logger.info("UDP listener thread started")
    
    def _udp_listener(self):
        """Background thread to receive UDP messages."""
        logger.info("UDP listener active, waiting for messages...")
        
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
        
        logger.debug("RX from {}:{} - Type:{} Len:{} XID:0x{:08x}".format(
            addr[0], addr[1], msg_type, length, xid))
        
        # Route message to handler
        if msg_type == self.OFPT_HELLO:
            self._handle_hello(data, addr, version, xid)
        elif msg_type == self.OFPT_ECHO_REQUEST:
            self._handle_echo_request(data, addr, version, xid)
        elif msg_type == self.OFPT_FEATURES_REPLY:
            self._handle_features_reply(data, addr, version, xid)
        elif msg_type == self.OFPT_PACKET_IN:
            self._handle_packet_in(data, addr, version, xid)
        else:
            logger.debug("Unhandled message type: {} from {}".format(msg_type, addr))
    
    def _send_message(self, data, addr):
        """Send OpenFlow message via UDP."""
        try:
            self.sock.sendto(data, addr)
            logger.debug("TX to {}:{} - {} bytes".format(addr[0], addr[1], len(data)))
        except Exception as e:
            logger.error("Failed to send to {}: {}".format(addr, e))
    
    def _handle_hello(self, data, addr, version, xid):
        """
        Handle HELLO message.
        
        OpenFlow handshake:
        1. Switch sends HELLO
        2. Controller sends HELLO reply
        3. Controller sends FEATURES_REQUEST
        """
        logger.info("="*70)
        logger.info("HELLO from {}:{}".format(addr[0], addr[1]))
        logger.info("="*70)
        logger.info("  OpenFlow Version: 0x{:02x}".format(version))
        logger.info("  XID: 0x{:08x}".format(xid))
        
        # Send HELLO reply (echo back the HELLO message)
        hello_reply = struct.pack('!BBHI', version, self.OFPT_HELLO, 8, xid)
        self._send_message(hello_reply, addr)
        logger.info("  -> Sent HELLO reply")
        
        # Send FEATURES_REQUEST
        features_xid = xid + 1
        features_request = struct.pack('!BBHI', 
                                      version, 
                                      self.OFPT_FEATURES_REQUEST, 
                                      8, 
                                      features_xid)
        self._send_message(features_request, addr)
        logger.info("  -> Sent FEATURES_REQUEST (XID: 0x{:08x})".format(features_xid))
    
    def _handle_echo_request(self, data, addr, version, xid):
        """
        Handle ECHO_REQUEST (keepalive).
        
        Reply with ECHO_REPLY to maintain connection.
        """
        logger.debug("ECHO_REQUEST from {}:{} (XID: 0x{:08x})".format(
            addr[0], addr[1], xid))
        
        # Send ECHO_REPLY (same format as request)
        echo_reply = struct.pack('!BBHI', version, self.OFPT_ECHO_REPLY, 8, xid)
        self._send_message(echo_reply, addr)
        logger.debug("  -> Sent ECHO_REPLY")
    
    def _handle_features_reply(self, data, addr, version, xid):
        """
        Handle FEATURES_REPLY.
        
        Extract switch capabilities and install table-miss flow.
        """
        if len(data) < 32:
            logger.warning("FEATURES_REPLY too short: {} bytes".format(len(data)))
            return
        
        # Parse FEATURES_REPLY (OpenFlow 1.3)
        # Header (8) + datapath_id (8) + n_buffers (4) + n_tables (1) + 
        # auxiliary_id (1) + pad (2) + capabilities (4) + reserved (4)
        header = data[:8]
        dpid_bytes = data[8:16]
        n_buffers = struct.unpack('!I', data[16:20])[0]
        n_tables = struct.unpack('!B', data[20:21])[0]
        
        # Datapath ID (switch unique ID)
        dpid = struct.unpack('!Q', dpid_bytes)[0]
        
        logger.info("="*70)
        logger.info("FEATURES_REPLY from {}:{}".format(addr[0], addr[1]))
        logger.info("="*70)
        logger.info("  Datapath ID: 0x{:016x}".format(dpid))
        logger.info("  N_buffers: {}".format(n_buffers))
        logger.info("  N_tables: {}".format(n_tables))
        logger.info("  Version: 0x{:02x}".format(version))
        
        # Track switch
        self.switches[addr] = {
            'datapath_id': dpid,
            'version': version,
            'last_seen': datetime.now()
        }
        
        logger.info("Switch 0x{:016x} registered".format(dpid))
        
        # Install table-miss flow (default: send to controller)
        self._install_table_miss_flow(addr, dpid, version)
    
    def _install_table_miss_flow(self, addr, dpid, version):
        """
        Install table-miss flow.
        
        Flow: priority=0, match=any, action=CONTROLLER
        This catches all unmatched packets and sends them to controller.
        """
        logger.info("Installing table-miss flow on switch 0x{:016x}".format(dpid))
        
        # Build FLOW_MOD message (simplified for table-miss)
        # This is a minimal OpenFlow 1.3 FLOW_MOD
        
        xid = 0x12345678
        
        # OpenFlow 1.3 FLOW_MOD structure
        # Header (8) + cookie (8) + cookie_mask (8) + table_id (1) + 
        # command (1) + idle_timeout (2) + hard_timeout (2) + priority (2) +
        # buffer_id (4) + out_port (4) + out_group (4) + flags (2) + pad (2)
        
        # FLOW_MOD header
        version_byte = version
        msg_type = self.OFPT_FLOW_MOD
        
        # Flow parameters
        cookie = 0
        cookie_mask = 0
        table_id = 0  # Table 0
        command = 0  # OFPFC_ADD
        idle_timeout = 0  # Permanent
        hard_timeout = 0  # Permanent
        priority = 0  # Lowest priority (table-miss)
        buffer_id = 0xffffffff  # No buffer
        out_port = 0xffffffff  # OFPP_ANY
        out_group = 0xffffffff  # OFPG_ANY
        flags = 1  # OFPFF_SEND_FLOW_REM
        pad = 0
        
        # Match structure (match all = empty match)
        # type=OFPMT_OXM (1), length=4, pad
        match_type = 1
        match_length = 4
        match_pad = b'\x00\x00\x00\x00'
        
        # Instructions: OUTPUT to CONTROLLER
        # instruction type=OFPIT_APPLY_ACTIONS (4), length=24
        inst_type = 4
        inst_length = 24
        inst_pad = 0
        
        # Action: OUTPUT to CONTROLLER
        # action type=OFPAT_OUTPUT (0), length=16
        action_type = 0
        action_length = 16
        output_port = 0xfffffffd  # OFPP_CONTROLLER
        max_len = 0xffff  # Send full packet
        action_pad = b'\x00\x00\x00\x00\x00\x00'
        
        # Build message
        flow_mod = struct.pack('!BBHI',  # Header
                              version_byte, msg_type, 0, xid)  # Length filled later
        flow_mod += struct.pack('!QQ',  # Cookie, cookie_mask
                               cookie, cookie_mask)
        flow_mod += struct.pack('!BBHHHIIIHxx',  # Table, command, timeouts, etc
                               table_id, command, idle_timeout, hard_timeout,
                               priority, buffer_id, out_port, out_group, flags)
        flow_mod += struct.pack('!HH',  # Match
                               match_type, match_length)
        flow_mod += match_pad
        flow_mod += struct.pack('!HHxxHHIH',  # Instructions + Action
                               inst_type, inst_length,
                               action_type, action_length, output_port, max_len)
        flow_mod += action_pad
        
        # Update length in header
        total_length = len(flow_mod)
        flow_mod = struct.pack('!BBHI', version_byte, msg_type, total_length, xid) + flow_mod[8:]
        
        self._send_message(flow_mod, addr)
        logger.info("  -> Sent FLOW_MOD ({} bytes)".format(total_length))
        logger.info("  -> Table-miss flow installed (priority=0, action=CONTROLLER)")
    
    def _handle_packet_in(self, data, addr, version, xid):
        """
        Handle PACKET_IN.
        
        Received when switch forwards packet to controller.
        """
        if len(data) < 32:
            logger.warning("PACKET_IN too short: {} bytes".format(len(data)))
            return
        
        # Get switch info
        switch_info = self.switches.get(addr, {'datapath_id': 'Unknown'})
        dpid = switch_info.get('datapath_id', 'Unknown')
        
        logger.info("PACKET_IN from switch 0x{:016x} ({} bytes)".format(dpid if dpid != 'Unknown' else 0, len(data)))
        
        # In Phase 3, we'll add MAC learning and flow installation here
        logger.debug("  (No action - Phase 2 basic handler)")


def main():
    """Main entry point."""
    from ryu.cmd import manager
    import sys
    
    # Set up Ryu manager arguments
    sys.argv = [
        'ryu-manager',
        '--verbose',
        '--observe-links'
    ]
    
    # Start Ryu manager (will load this app)
    manager.main()


if __name__ == '__main__':
    # When run directly, start controller
    logger.info("Starting UDP OpenFlow Controller...")
    controller = UDPOpenFlowController()
    
    try:
        # Keep alive
        import time
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        logger.info("\nShutting down...")
        controller.running = False
        controller.sock.close()
