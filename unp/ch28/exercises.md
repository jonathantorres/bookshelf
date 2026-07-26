## Chapter 28 - Raw Sockets

#### 28.1

The version number field, the fragment header and the next header field are not available to applications.

#### 28.2

At some point the client's socket receive buffer will fill, causing the daemon's `write` to block. This will prevent the daemon from handling any more data on any of its sockets. One solution is to set it's end of the connection to non-blocking and ignore any `EWOULDBLOCK` errors.

#### 28.3

Most BSD kernels allow broadcasting on a raw socket.

#### 28.4

In this case the kernel will choose the outgoing interface by searching the routing table for `224.0.0.1`.
