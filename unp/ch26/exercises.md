## Chapter 26 - Threads

#### 26.1

In the forked example, there are 101 descriptors in use, the listening socket and the 100 clients. The threaded server has also 101 descriptors but each thread (client) is handling one descriptor.

#### 26.2

The final two segments of the TCP connection are not exchanged. This will eventually timeout the client's connection.

#### 26.3

See `26.3.c`

#### 26.4

See `26.4.c`
