from socket import *
import random

# Create a UDP socket
server_so = socket(AF_INET, SOCK_DGRAM)
server_so.bind(('', 12000))

while True:
    rand = random.randint(0, 10)
    message, address = server_so.recvfrom(1024)
    message = message.upper()
    if rand < 4:
        continue
    server_so.sendto(message, address)
