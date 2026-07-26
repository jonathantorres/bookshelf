## Chapter 15 - Interprocess Communication

#### 15.1

See `15.1.c`

#### 15.2

The parent process will terminate after writing the last line to the pipe causing the read end to be closed. The parent will also be probably running ahead of the child by one pipe buffer.

#### 15.3

See `15.3.c`

#### 15.4

The parent process will terminate after writing the last line to the pipe causing the read end to be closed. The parent will also be probably running ahead of the child by one pipe buffer.

#### 15.5

See `15.5.c`

#### 15.6

`pclose` will return an error since there is no children process to wait for.

#### 15.7

`select` will indicate that the file descriptor is readable, once all the data is read it will return EOF.

#### 15.8

The data written to the child's standard error will be displayed at the same time as the parent's.

#### 15.9

When `cmdstring` is finished by the child process forked by the shell, the shell will exit.

#### 15.10

See `15.10.c`

#### 15.11

To read the message queue, the process would need to know the ID of the queue and for the queue to have read-access for everyone.

#### 15.12

See `15.12.c`

#### 15.13

The linked list should be built using the pointers with offsets to other objects in the shared memory segment. These are formed by subtracting the start of the segment from the address of the object.

#### 15.14

Timeline below:

| parent | child | shared | update returns |
| ------ | ----- | ------ | -------------- |
|        |       | 0      |                |
|        | 1     |        |                |
| 0      |       |        |                |
|        |       |        | 0              |
|        |       | 1      |                |
|        |       | 2      |                |
|        |       |        | 1              |
|        | 3     |        |                |
| 2      |       |        |                |
|        |       | 3      |                |
|        |       |        | 2              |
|        |       | 4      |                |
|        |       |        | 3              |
|        | 5     |        |                |
| 4      |       |        |                |

#### 15.15

See `15.15.c`

#### 15.16

See `15.16.c`

#### 15.17

See `15.17.c`
