## Chapter 7 - Socket Options

#### 7.1

See `7.1.c`

#### 7.2

See `7.2.c`

#### 7.3

See `7.3.c`

#### 7.4

Once the first client connects, but if the second client calls `bind` in between the first client's call to `bind` and `connect` the error `EADDRINUSE` is returned.

#### 7.5

A host with multicast support supports the `-A` option, as expected. This would need to be specified, otherwise binding any other address won't work.

#### 7.6

Using the same host with multicast support, the experiment only works by using the `SO_REUSEPORT` option.

#### 7.7

In the case of the `ping` program, this option has no effect since the `SO_DEBUG` option only applies to TCP.

#### 7.8

See Timeline below:

![diagram](https://github.com/jonathantorres/bookshelf/blob/master/unp/img/7.8.png)

#### 7.9

See Timeline below:

![diagram](https://github.com/jonathantorres/bookshelf/blob/master/unp/img/7.9.png)

#### 7.10

See Timeline below:

![diagram](https://github.com/jonathantorres/bookshelf/blob/master/unp/img/7.10.png)

#### 7.11

Click [here](https://datatracker.ietf.org/doc/html/rfc1122) to see the RFC. The recommended delay must be less than 0.5 seconds.

#### 7.12

The server spends most of its time blocked on the call to `accept`. The `read` call on the server's child process will return an error of `ETIMEDOUT` sometime after the client's host crashes.

#### 7.13

The client spends most of its time blocked on the call to `fgets`, if the server host crashes a read or a write to the socket from the client will return an error.

#### 7.14

The client spends most of it's time blocked on the call to `select`, this will return a pending error of `ETIMEDOUT` when the server host crashes.

#### 7.15

Two segments are exchanged. The keep-alive probe and the ACK to the probe.

#### 7.16

The fourth argument to `socket` contained socket options, `SO_ACCEPTCON` was available to set a socket as a listening socket.
