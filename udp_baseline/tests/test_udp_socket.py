import socket

# Test UDP socket binding
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(('0.0.0.0', 6633))
print(f"UDP socket listening on port 6633")

# Wait for messages
while True:
    data, addr = sock.recvfrom(65535)
    print(f"Received {len(data)} bytes from {addr}")

