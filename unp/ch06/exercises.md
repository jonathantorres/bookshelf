## Chapter 6 - I/O Multiplexing: The select and poll Functions

#### 6.1

It is done by storing the array of integers inside of a structure (`struct`)

#### 6.2

To prevent the `write` from blocking.

#### 6.3

Since both descriptors are readable, only one test is performed, which will make the client terribly inefficient.

#### 6.4

See `6.4.c`

#### 6.5

See `6.5.c`

#### 6.6

`shutdown` will always send the FIN packet and terminate the connection, `close` does this same thing only if the reference count on the file descriptor is 1.

#### 6.7

`read` will return an error and the `Read` wrapper function will terminate the server program.

#### 6.8

See `6.8.c`
