## Chapter 22 - Advanced UDP Sockets

#### 22.1

This is to prevent `sock_ntop` from overwriting its buffer twice.

#### 22.2

Yes, but only if the reply contains 0 bytes of user data.

#### 22.3

See `22.3.c`

#### 22.4

This is usually done by creating one socket per interface address and send the reply from the same socket.

#### 22.5

See `22.5.c`

#### 22.6

See `22.6.c`
