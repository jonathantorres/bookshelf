## Chapter 14 - Advanced I/O

#### 14.1

See `14.1.c`

#### 14.2

The `fd_set` type is a struct with an array of long integers, each bit in the array represents a file descriptor. The four `FD_*` macros maniputate these bits according to the operation.

#### 14.3

In some systems the `FD_SETSIZE` constant can be changed or declared before including the `<sys/select.h>` header

#### 14.4

Comparison of functions:

| select functions | signal functions |
| ---------------- | ---------------- |
| FD_ZERO          | sigemptyset      |
| FD_SET           | sigaddset        |
| FD_CLR           | sigdelset        |
| FD_ISSET         | sigismember      |

#### 14.5

STREAMS have been dropped from most UNIX systems and are now deprecated. Skipping this exercise

#### 14.6

See `14.6.c`

#### 14.7

No, this is currently not possible, when we call `fork` all locks are released from the child process so it cannot start with it's own locks.

#### 14.8

On my Linux machine `PIPE_BUF` is 4,096 bytes

#### 14.9

The break-even point seems to be on a file of approximately 358MB of space

#### 14.10

See `14.10.c`

#### 14.11

See `14.11.c`
