## Chapter 5 - TCP Client/Server Example

#### 5.1

The MSL on my Linux machine is 60 seconds.

#### 5.2

This causes a deadlock, since `fgets` does not support binary data.

#### 5.3

The only difference is on the carriage return (CR) sent by the telnet client. Other than that, the server should work the same regardless of the client.

#### 5.4

No, these two segments are not sent. After the server child is killed, an RST aborts the connection.

#### 5.5

Nothing changes in this case, the data segment sent in step 3 is never seen by the server and it sends an RST.

#### 5.6

See `5.6.c`

#### 5.7

If the server host supports the "weak end system model" everything should work fine.

#### 5.8

-22 in a little-endian system is represented as `0xffffffea`, on a big-endian system this would be `0xeaffffff` or -352,321,537. A similar problem happens with -77 which is interpreted as -1,275,068,417 in big-endian. Adding these yields -1,627,068,417 which is interpreted as `0xf3ffff9e` or -16,777,314 in a little-endian system.

#### 5.9

The technique is correct, but we would need the conversion routines to also support 64-bit values.

#### 5.10

The machine with the biggest address space will block when sending/receiving data because it will either send less data than expected in the case of a 32-bit client or will wait for more data than expected in the case of a 64-bit server.

#### 5.11

IP looks at the destination IP address and searches the routing table to determine the outgoing interface. The primary IP of this interface is used as the source IP address.
