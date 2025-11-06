from udp_baseline.lib.udp_ofp_parser import UDPOpenFlowParser
import struct

parser = UDPOpenFlowParser()

# Create test HELLO message
hello_data = struct.pack('!BBHI', 4, 0, 8, 1)  # version=4, type=0 (HELLO)

msg = parser.parse_message(hello_data)
print(f"Parsed message: {msg}")

