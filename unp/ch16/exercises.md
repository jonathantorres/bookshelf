## Chapter 16 - Nonblocking I/O

#### 16.1

Because the file descriptor is shared between the client and the server. If we call `close` only the reference count on the descriptor is decremented, with `shutdown` we can force the closing of the connection.

#### 16.2

The parent will write to a socket that received a FIN, this will cause the server to receive a RST.

#### 16.3

The child will receive a PID of 1 (the init process). When it sends the `SIGTERM` signal to it, this call will fail.

#### 16.4

This test prevents unnecessary calls to `select` since the socket is already writable.

#### 16.5

It can happen when a server sends data right after `accept` returns and the client is busy when the second packet of the 3-way handshake arrives to complete the connection with this client.
