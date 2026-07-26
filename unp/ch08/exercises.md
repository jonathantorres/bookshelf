## Chapter 8 - Elementary UDP Sockets

#### 8.1

There is some difference, the call to `read` returns 4,096 bytes but `recvfrom` returns 2,048.

#### 8.2

The value of `clilen` may be too large, and for an UDP socket the behaviour is undefined.

#### 8.3

See `8.3.client.c` and `8.3.server.c`

#### 8.4

The ICMP error of "Destination Port Unreachable" is returned.

#### 8.5

It may have a socket receive buffer, but it's never used. Most kernels do not allocate memory for these buffers.

#### 8.6

This apears to be the case, the source IP address is the one that was bound by the client, not the outgoing interface.

#### 8.7

Adding a `printf` on both the client and the server causes delays. Adding it to the client causes the server to receive more datagrams, and adding it to the server makes the server lose some datagrams.

#### 8.8

See `8.8.c`

#### 8.9

See `8.9.c`
