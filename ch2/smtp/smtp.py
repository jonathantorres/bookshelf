import base64
from socket import *

msg = "\r\n I love computer networks!"
endmsg = "\r\n.\r\n"

# Choose a mail server (e.g. Google mail server) and call it mailserver
mailserver =  'smtp.163.com'
username = 'your_username@163.com'
password = 'your_password'
sender = username
recipient = username

client_so = socket(AF_INET, SOCK_STREAM)
client_so.settimeout(10)
client_so.connect((mailserver, 25))
recv = client_so.recv(1024)
print(recv)
if recv[:3] != b'220':
    print('220 reply not received from server.')
    exit(0)

helo_cmd = b'HELO Alice\r\n'
client_so.send(helo_cmd)
recv = client_so.recv(1024)
print(recv)
if recv[:3] != b'250':
    print('250 reply not received from server.')
    exit(0)

client_so.send(b'AUTH LOGIN\r\n')
recv = client_so.recv(1024)
print(recv)
if recv[:3] != b'334':
    print('334 reply not received from server.')
    exit(0)

client_so.send(base64.b64encode(bytes(username, 'ascii')) + b'\r\n')
recv = client_so.recv(1024)
print(recv)
if recv[:3] != b'334':
    print('334 reply not received from server.')
    exit(0)

client_so.send(base64.b64encode(bytes(password, 'ascii')) + b'\r\n')
recv = client_so.recv(1024)
print(recv)
if recv[:3] != b'235':
    print('235 reply not received from server.')
    exit(0)

client_so.send(b'MAIL FROM: <' + bytes(sender, 'ascii') + b'>\r\n')
recv = client_so.recv(1024)
print(recv)
if recv[:3] != b'250':
    print('250 reply not received from server.')
    exit(0)

client_so.send(b'RCPT TO: <'+ bytes(recipient, 'ascii') + b'>\r\n')
recv = client_so.recv(1024)
print(recv)
if recv[:3] != b'250':
    print('250 reply not received from server.')
    exit(0)

client_so.send(b'DATA\r\n')
recv = client_so.recv(1024)
print(recv)
if recv[:3] != b'354':
    print('354 reply not received from server.')
    exit(0)

# Send message data.
client_so.send(b'Subject: test message\r\n')
client_so.send(b'From:""< ' + bytes(sender, 'ascii') + b'>\r\n')
client_so.send(b'To:""< ' + bytes(recipient, 'ascii') + b'>\r\n')
client_so.send(bytes(msg, encoding='ascii'))
client_so.send(bytes(endmsg, encoding='ascii'))
recv = client_so.recv(1024)
print(recv)
if recv[:3] != b'250':
    print('250 reply not received from server.')
    exit(0)

client_so.send(b'QUIT\r\n')
recv = client_so.recv(1024)
print(recv)
if recv[:3] != b'221':
    print('250 reply not received from server.')
    exit(0)
