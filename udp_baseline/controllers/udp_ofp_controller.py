import socket
import struct
import threading
import time

from ryu.ofproto import ofproto_v1_3
from udp_baseline.lib.udp_ofp_parser import UDPOpenFlowParser


class UDPOpenFlowController:
    """
    Lightweight UDP-based OpenFlow Controller for Phase 3B.
    Handles HELLO, FEATURES_REPLY, and PACKET_IN messages over UDP.
    """

    def __init__(self, host='0.0.0.0', port=6633):
        self.host = host
        self.port = port
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.socket.bind((host, port))

        self.running = False
        self.switches = {}  # {dpid: {'addr': (ip, port)}}

        self.ofproto = ofproto_v1_3
        self.parser = UDPOpenFlowParser()

    # ---------------------------------------------------------------------- #
    # Controller Lifecycle
    # ---------------------------------------------------------------------- #
    def start(self):
        """Start the UDP OpenFlow controller."""
        self.running = True
        print(f"[INFO] UDP OpenFlow Controller listening on {self.host}:{self.port}")

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
            self.switches[dpid] = {'addr': addr}
            print(f"[INFO] Switch connected: DPID={dpid:#x} from {addr}")
        else:
            print(f"[WARN] Invalid FEATURES_REPLY from {addr}")

    def _handle_packet_in(self, data, addr):
        """Handle PACKET_IN (for logging/demo)."""
        print(f"[INFO] PACKET_IN received from {addr}, length={len(data)}")

    # ---------------------------------------------------------------------- #
    # Utility
    # ---------------------------------------------------------------------- #
    def send_flow_mod(self, dpid, match=None, actions=None):
        """Send a dummy FLOW_MOD to a connected switch."""
        if dpid not in self.switches:
            print(f"[WARN] Switch {dpid:#x} not connected")
            return

        addr = self.switches[dpid]['addr']
        flow_mod = struct.pack('!BBHI',
                               self.ofproto.OFP_VERSION,
                               self.ofproto.OFPT_FLOW_MOD,
                               8, 99)
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

