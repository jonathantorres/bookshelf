from socket import *

port = 9999
server_so = socket(AF_INET, SOCK_STREAM)
server_so.bind(('', port))
server_so.listen()

while True:
    print('Listening to port ' + str(port))
    con_so, addr = server_so.accept()
    try:
        message = str(con_so.recv(4096), encoding='utf-8')
        if not message:
            con_so.close()
            continue
        print(message)
        con_so.send(bytes('Message received\n', encoding='utf-8'))
        con_so.close()
    except IOError:
        con_so.send(bytes('There was an error!\n', encoding='utf-8'))
        con_so.close()

server_so.close()
