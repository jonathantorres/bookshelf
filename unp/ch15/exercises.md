## Chapter 15 - Unix Domain Protocols

#### 15.1

The `connect` from the client will fail since the file has been removed from the filesystem.

#### 15.2

The client won't be able to connect to the server since the socket must be open and bound to the specified path.

#### 15.3

No bytes are `read` by the client. In this case the server prints "Datagram from (no pathname bound)" since no path is bound to the client's socket.

#### 15.4

See `15.4.c`

#### 15.5

See `15.5.c`
