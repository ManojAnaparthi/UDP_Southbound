from ryu.ofproto import ofproto_v1_3
import struct

class UDPOpenFlowParser:
    def __init__(self):
        self.ofproto = ofproto_v1_3
        
    def parse_message(self, data):
        """Parse minimal OpenFlow message from UDP packet"""
        if len(data) < 8:
            print("Invalid OpenFlow packet (too short)")
            return None

        # OpenFlow header format: version(1), type(1), length(2), xid(4)
        version, msg_type, msg_len, xid = struct.unpack('!BBHI', data[:8])

        if version != self.ofproto.OFP_VERSION:
            print(f"Unsupported OpenFlow version: {version}")
            return None

        msg_name = self._msg_type_to_name(msg_type)
        print(f"Parsed OpenFlow header → version={version}, type={msg_type} ({msg_name}), len={msg_len}, xid={xid}")

        # Return a simple structured dictionary
        return {
            'version': version,
            'type': msg_type,
            'msg_name': msg_name,
            'length': msg_len,
            'xid': xid,
            'raw_data': data
        }

    def _msg_type_to_name(self, msg_type):
        """Map type number to a readable message name"""
        mapping = {
            self.ofproto.OFPT_HELLO: 'HELLO',
            self.ofproto.OFPT_ERROR: 'ERROR',
            self.ofproto.OFPT_ECHO_REQUEST: 'ECHO_REQUEST',
            self.ofproto.OFPT_ECHO_REPLY: 'ECHO_REPLY',
            self.ofproto.OFPT_FEATURES_REQUEST: 'FEATURES_REQUEST',
            self.ofproto.OFPT_FEATURES_REPLY: 'FEATURES_REPLY',
            self.ofproto.OFPT_PACKET_IN: 'PACKET_IN',
            self.ofproto.OFPT_FLOW_MOD: 'FLOW_MOD'
        }
        return mapping.get(msg_type, f'UNKNOWN({msg_type})')
