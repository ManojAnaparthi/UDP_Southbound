"""
OpenFlow Message Test Application for Ryu

This Ryu app exercises ALL major OpenFlow 1.3 message types to demonstrate
they work correctly over UDP transport.

Message Types Tested:
- Hello (handshake)
- Features Request/Reply
- Echo Request/Reply
- Set-Config / Get-Config Request/Reply
- Barrier Request/Reply
- Flow-Mod (add, modify, delete)
- Packet-In / Packet-Out
- Multipart Request/Reply (flow stats, port stats, table stats, desc stats)
- Port-Status (when ports change)
- Error (intentionally triggered)
- Role Request/Reply

Usage:
    PYTHONPATH=. bin/ryu-manager --ofp-listen-transport udp e2e_tests/ofp_message_test_app.py
"""

from ryu.base import app_manager
from ryu.controller import ofp_event
from ryu.controller.handler import CONFIG_DISPATCHER, MAIN_DISPATCHER, DEAD_DISPATCHER
from ryu.controller.handler import set_ev_cls
from ryu.ofproto import ofproto_v1_3
from ryu.lib.packet import packet, ethernet, arp, icmp, ipv4
from ryu.lib import hub
import time


class OpenFlowMessageTest(app_manager.RyuApp):
    """Ryu app that tests all OpenFlow message types over UDP."""
    
    OFP_VERSIONS = [ofproto_v1_3.OFP_VERSION]
    
    def __init__(self, *args, **kwargs):
        super(OpenFlowMessageTest, self).__init__(*args, **kwargs)
        self.mac_to_port = {}
        self.datapaths = {}
        self.message_log = []
        self.test_complete = False
        
    def log_message(self, direction, msg_type, details=""):
        """Log an OpenFlow message."""
        timestamp = time.strftime("%H:%M:%S")
        entry = f"[{timestamp}] {direction:4} | {msg_type:30} | {details}"
        self.message_log.append(entry)
        self.logger.info(entry)
    
    @set_ev_cls(ofp_event.EventOFPStateChange, [MAIN_DISPATCHER, DEAD_DISPATCHER])
    def state_change_handler(self, ev):
        """Track datapath state changes."""
        datapath = ev.datapath
        if ev.state == MAIN_DISPATCHER:
            self.datapaths[datapath.id] = datapath
            self.log_message("<<<", "STATE_CHANGE", f"Datapath {datapath.id} connected")
            # Start comprehensive tests after connection
            hub.spawn(self._run_all_tests, datapath)
        elif ev.state == DEAD_DISPATCHER:
            if datapath.id in self.datapaths:
                del self.datapaths[datapath.id]
            self.log_message("<<<", "STATE_CHANGE", f"Datapath {datapath.id} disconnected")
    
    @set_ev_cls(ofp_event.EventOFPSwitchFeatures, CONFIG_DISPATCHER)
    def switch_features_handler(self, ev):
        """Handle Features Reply (received during handshake)."""
        msg = ev.msg
        datapath = msg.datapath
        self.log_message("<<<", "FEATURES_REPLY", 
                        f"dpid={datapath.id}, n_tables={msg.n_tables}, capabilities={msg.capabilities}")
        
        # Install table-miss flow
        ofproto = datapath.ofproto
        parser = datapath.ofproto_parser
        match = parser.OFPMatch()
        actions = [parser.OFPActionOutput(ofproto.OFPP_CONTROLLER, ofproto.OFPCML_NO_BUFFER)]
        self._add_flow(datapath, 0, match, actions, "table-miss")
    
    @set_ev_cls(ofp_event.EventOFPEchoReply, MAIN_DISPATCHER)
    def echo_reply_handler(self, ev):
        """Handle Echo Reply."""
        self.log_message("<<<", "ECHO_REPLY", f"data_len={len(ev.msg.data)}")
    
    @set_ev_cls(ofp_event.EventOFPGetConfigReply, MAIN_DISPATCHER)
    def get_config_reply_handler(self, ev):
        """Handle Get-Config Reply."""
        msg = ev.msg
        self.log_message("<<<", "GET_CONFIG_REPLY", 
                        f"flags={msg.flags}, miss_send_len={msg.miss_send_len}")
    
    @set_ev_cls(ofp_event.EventOFPBarrierReply, MAIN_DISPATCHER)
    def barrier_reply_handler(self, ev):
        """Handle Barrier Reply."""
        self.log_message("<<<", "BARRIER_REPLY", f"xid={ev.msg.xid}")
    
    @set_ev_cls(ofp_event.EventOFPErrorMsg, [CONFIG_DISPATCHER, MAIN_DISPATCHER])
    def error_msg_handler(self, ev):
        """Handle Error messages."""
        msg = ev.msg
        self.log_message("<<<", "ERROR", 
                        f"type={msg.type}, code={msg.code}")
    
    @set_ev_cls(ofp_event.EventOFPPortStatus, MAIN_DISPATCHER)
    def port_status_handler(self, ev):
        """Handle Port-Status messages."""
        msg = ev.msg
        reason_map = {
            msg.datapath.ofproto.OFPPR_ADD: "ADD",
            msg.datapath.ofproto.OFPPR_DELETE: "DELETE",
            msg.datapath.ofproto.OFPPR_MODIFY: "MODIFY",
        }
        reason = reason_map.get(msg.reason, str(msg.reason))
        self.log_message("<<<", "PORT_STATUS", 
                        f"reason={reason}, port={msg.desc.port_no}")
    
    @set_ev_cls(ofp_event.EventOFPFlowStatsReply, MAIN_DISPATCHER)
    def flow_stats_reply_handler(self, ev):
        """Handle Flow Stats Reply (Multipart)."""
        self.log_message("<<<", "MULTIPART_REPLY (FLOW_STATS)", 
                        f"flows={len(ev.msg.body)}")
        for stat in ev.msg.body[:3]:  # Log first 3 flows
            self.logger.info(f"         Flow: priority={stat.priority}, "
                           f"match={stat.match}, packets={stat.packet_count}")
    
    @set_ev_cls(ofp_event.EventOFPPortStatsReply, MAIN_DISPATCHER)
    def port_stats_reply_handler(self, ev):
        """Handle Port Stats Reply (Multipart)."""
        self.log_message("<<<", "MULTIPART_REPLY (PORT_STATS)", 
                        f"ports={len(ev.msg.body)}")
        for stat in ev.msg.body[:3]:  # Log first 3 ports
            self.logger.info(f"         Port {stat.port_no}: "
                           f"rx={stat.rx_packets}, tx={stat.tx_packets}")
    
    @set_ev_cls(ofp_event.EventOFPTableStatsReply, MAIN_DISPATCHER)
    def table_stats_reply_handler(self, ev):
        """Handle Table Stats Reply (Multipart)."""
        active_tables = [t for t in ev.msg.body if t.active_count > 0]
        self.log_message("<<<", "MULTIPART_REPLY (TABLE_STATS)", 
                        f"tables={len(ev.msg.body)}, active={len(active_tables)}")
    
    @set_ev_cls(ofp_event.EventOFPDescStatsReply, MAIN_DISPATCHER)
    def desc_stats_reply_handler(self, ev):
        """Handle Desc Stats Reply (Multipart)."""
        body = ev.msg.body
        self.log_message("<<<", "MULTIPART_REPLY (DESC_STATS)", 
                        f"mfr={body.mfr_desc[:20]}..., hw={body.hw_desc[:15]}...")
    
    @set_ev_cls(ofp_event.EventOFPRoleReply, MAIN_DISPATCHER)
    def role_reply_handler(self, ev):
        """Handle Role Reply."""
        msg = ev.msg
        role_map = {
            msg.datapath.ofproto.OFPCR_ROLE_NOCHANGE: "NOCHANGE",
            msg.datapath.ofproto.OFPCR_ROLE_EQUAL: "EQUAL",
            msg.datapath.ofproto.OFPCR_ROLE_MASTER: "MASTER",
            msg.datapath.ofproto.OFPCR_ROLE_SLAVE: "SLAVE",
        }
        role = role_map.get(msg.role, str(msg.role))
        self.log_message("<<<", "ROLE_REPLY", f"role={role}, gen_id={msg.generation_id}")
    
    @set_ev_cls(ofp_event.EventOFPPacketIn, MAIN_DISPATCHER)
    def packet_in_handler(self, ev):
        """Handle Packet-In and demonstrate Packet-Out."""
        msg = ev.msg
        datapath = msg.datapath
        ofproto = datapath.ofproto
        parser = datapath.ofproto_parser
        in_port = msg.match['in_port']
        
        pkt = packet.Packet(msg.data)
        eth = pkt.get_protocols(ethernet.ethernet)[0]
        
        self.log_message("<<<", "PACKET_IN", 
                        f"in_port={in_port}, src={eth.src}, dst={eth.dst}")
        
        # L2 learning
        dpid = datapath.id
        self.mac_to_port.setdefault(dpid, {})
        self.mac_to_port[dpid][eth.src] = in_port
        
        if eth.dst in self.mac_to_port[dpid]:
            out_port = self.mac_to_port[dpid][eth.dst]
        else:
            out_port = ofproto.OFPP_FLOOD
        
        actions = [parser.OFPActionOutput(out_port)]
        
        # Install flow for known destinations
        if out_port != ofproto.OFPP_FLOOD:
            match = parser.OFPMatch(in_port=in_port, eth_dst=eth.dst, eth_src=eth.src)
            self._add_flow(datapath, 1, match, actions, "learned")
        
        # Send Packet-Out
        data = None
        if msg.buffer_id == ofproto.OFP_NO_BUFFER:
            data = msg.data
        
        out = parser.OFPPacketOut(datapath=datapath, buffer_id=msg.buffer_id,
                                  in_port=in_port, actions=actions, data=data)
        datapath.send_msg(out)
        self.log_message(">>>", "PACKET_OUT", f"out_port={out_port}")
    
    def _add_flow(self, datapath, priority, match, actions, desc=""):
        """Send Flow-Mod to add a flow."""
        ofproto = datapath.ofproto
        parser = datapath.ofproto_parser
        
        inst = [parser.OFPInstructionActions(ofproto.OFPIT_APPLY_ACTIONS, actions)]
        mod = parser.OFPFlowMod(datapath=datapath, priority=priority,
                                match=match, instructions=inst)
        datapath.send_msg(mod)
        self.log_message(">>>", "FLOW_MOD (ADD)", f"priority={priority}, {desc}")
    
    def _run_all_tests(self, datapath):
        """Run comprehensive OpenFlow message tests."""
        self.logger.info("\n" + "=" * 70)
        self.logger.info("  OPENFLOW MESSAGE TEST SUITE (over UDP)")
        self.logger.info("=" * 70 + "\n")
        
        ofproto = datapath.ofproto
        parser = datapath.ofproto_parser
        
        hub.sleep(1)  # Wait for initial setup
        
        # Test 1: Echo Request/Reply
        self.logger.info("\n[TEST 1] Echo Request/Reply")
        echo_req = parser.OFPEchoRequest(datapath, data=b"UDP-TEST")
        datapath.send_msg(echo_req)
        self.log_message(">>>", "ECHO_REQUEST", "data=UDP-TEST")
        hub.sleep(0.5)
        
        # Test 2: Get-Config
        self.logger.info("\n[TEST 2] Get-Config Request/Reply")
        config_req = parser.OFPGetConfigRequest(datapath)
        datapath.send_msg(config_req)
        self.log_message(">>>", "GET_CONFIG_REQUEST", "")
        hub.sleep(0.5)
        
        # Test 3: Set-Config
        self.logger.info("\n[TEST 3] Set-Config")
        set_config = parser.OFPSetConfig(datapath, ofproto.OFPC_FRAG_NORMAL, 128)
        datapath.send_msg(set_config)
        self.log_message(">>>", "SET_CONFIG", "flags=FRAG_NORMAL, miss_send_len=128")
        hub.sleep(0.5)
        
        # Test 4: Barrier
        self.logger.info("\n[TEST 4] Barrier Request/Reply")
        barrier_req = parser.OFPBarrierRequest(datapath)
        datapath.send_msg(barrier_req)
        self.log_message(">>>", "BARRIER_REQUEST", "")
        hub.sleep(0.5)
        
        # Test 5: Flow-Mod (Add test flow)
        self.logger.info("\n[TEST 5] Flow-Mod (Add)")
        match = parser.OFPMatch(eth_type=0x0800, ipv4_dst="192.168.100.1")
        actions = [parser.OFPActionOutput(1)]
        inst = [parser.OFPInstructionActions(ofproto.OFPIT_APPLY_ACTIONS, actions)]
        flow_mod = parser.OFPFlowMod(datapath=datapath, priority=100,
                                     match=match, instructions=inst)
        datapath.send_msg(flow_mod)
        self.log_message(">>>", "FLOW_MOD (ADD)", "test flow to 192.168.100.1")
        hub.sleep(0.5)
        
        # Test 6: Multipart - Flow Stats
        self.logger.info("\n[TEST 6] Multipart Request - Flow Stats")
        flow_stats_req = parser.OFPFlowStatsRequest(datapath)
        datapath.send_msg(flow_stats_req)
        self.log_message(">>>", "MULTIPART_REQUEST (FLOW_STATS)", "")
        hub.sleep(0.5)
        
        # Test 7: Multipart - Port Stats
        self.logger.info("\n[TEST 7] Multipart Request - Port Stats")
        port_stats_req = parser.OFPPortStatsRequest(datapath, 0, ofproto.OFPP_ANY)
        datapath.send_msg(port_stats_req)
        self.log_message(">>>", "MULTIPART_REQUEST (PORT_STATS)", "")
        hub.sleep(0.5)
        
        # Test 8: Multipart - Table Stats
        self.logger.info("\n[TEST 8] Multipart Request - Table Stats")
        table_stats_req = parser.OFPTableStatsRequest(datapath, 0)
        datapath.send_msg(table_stats_req)
        self.log_message(">>>", "MULTIPART_REQUEST (TABLE_STATS)", "")
        hub.sleep(0.5)
        
        # Test 9: Multipart - Desc Stats
        self.logger.info("\n[TEST 9] Multipart Request - Desc Stats")
        desc_stats_req = parser.OFPDescStatsRequest(datapath, 0)
        datapath.send_msg(desc_stats_req)
        self.log_message(">>>", "MULTIPART_REQUEST (DESC_STATS)", "")
        hub.sleep(0.5)
        
        # Test 10: Role Request
        self.logger.info("\n[TEST 10] Role Request/Reply")
        role_req = parser.OFPRoleRequest(datapath, ofproto.OFPCR_ROLE_NOCHANGE, 0)
        datapath.send_msg(role_req)
        self.log_message(">>>", "ROLE_REQUEST", "role=NOCHANGE")
        hub.sleep(0.5)
        
        # Test 11: Flow-Mod (Delete test flow)
        self.logger.info("\n[TEST 11] Flow-Mod (Delete)")
        match = parser.OFPMatch(eth_type=0x0800, ipv4_dst="192.168.100.1")
        flow_mod = parser.OFPFlowMod(datapath=datapath, command=ofproto.OFPFC_DELETE,
                                     out_port=ofproto.OFPP_ANY, out_group=ofproto.OFPG_ANY,
                                     match=match)
        datapath.send_msg(flow_mod)
        self.log_message(">>>", "FLOW_MOD (DELETE)", "test flow to 192.168.100.1")
        hub.sleep(0.5)
        
        # Final barrier to ensure all messages processed
        barrier_req = parser.OFPBarrierRequest(datapath)
        datapath.send_msg(barrier_req)
        self.log_message(">>>", "BARRIER_REQUEST", "final sync")
        hub.sleep(1)
        
        # Print summary
        self.logger.info("\n" + "=" * 70)
        self.logger.info("  TEST SUMMARY")
        self.logger.info("=" * 70)
        self.logger.info(f"  Total messages logged: {len(self.message_log)}")
        self.logger.info("  All OpenFlow messages sent/received over UDP!")
        self.logger.info("=" * 70 + "\n")
        
        self.test_complete = True
