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

        filename = message.split()[1]
        f = open(filename[1:])
        outputdata = f.read()
        outputdata_bytes = bytes(outputdata, encoding='gb18030')
        headers = 'HTTP/1.1 200 OK\nContent-Type: text/html; charset=utf-8\nContent-Length: {}\n\n'.format(len(outputdata_bytes))

        con_so.send(bytes(headers, encoding='utf-8'))
        con_so.send(outputdata_bytes)
        con_so.close()

    except IOError:
        outputdata_bytes = bytes('Not Found', encoding='utf-8')
        headers = 'HTTP/1.1 404 Not Found\nContent-Type: text/html; charset=utf-8\nContent-Length: {}\n\n'.format(len(outputdata_bytes))
        con_so.send(bytes(headers, encoding='utf-8'))
        con_so.send(outputdata_bytes)
        con_so.close()

server_so.close()
