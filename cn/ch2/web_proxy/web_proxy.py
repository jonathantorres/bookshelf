from socket import *

server_port = 8899
server_so = socket(AF_INET, SOCK_STREAM)

server_so.bind(('', server_port))
server_so.listen(5)

while True:
    print('Listening to port ' + str(server_port))
    client_so, addr = server_so.accept()
    print('Received from: ', addr)
    message = client_so.recv(4096).decode()
    filename = message.split()[1].partition("//")[2].replace('/', '_')
    file_exist = False
    try:
        f = open(filename, "r")
        outputdata = f.readlines()
        file_exist = True
        for i in range(0, len(outputdata)):
            client_so.send(outputdata[i].encode())
        print('Read file from cache')
    except IOError:
        print('File Exist: ', file_exist)
        if not file_exist:
            print('Creating socket on proxy')
            c = socket(AF_INET, SOCK_STREAM)
            hostn = message.split()[1].partition("//")[2].partition("/")[0]
            try:
                c.connect((hostn, 8080))
                print('Socket connected to port 8080 of the host')
                c.sendall(message.encode())
                buff = c.recv(4096)
                client_so.sendall(buff)
                tmp_file = open("./" + filename, "w")
                tmp_file.writelines(buff.decode().replace('\r\n', '\n'))
                tmp_file.close()
            except:
                print("Illegal request")
        else:
            print('File Not Found!')
    client_so.close()
server_so.close()
