import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(('0.0.0.0', 6633))

while True:
    data, addr = sock.recvfrom(65535)
    print(f"Echo: {len(data)} bytes from {addr}")
    sock.sendto(data, addr)

