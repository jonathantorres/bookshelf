## Chapter 19 - Pseudo Terminals

#### 19.1

It happens because both programs run with superuser privileges, their respective calls to `chown` and `chmod` execute successfully.

#### 19.2

See `19.2.c`

#### 19.3

See `19.3.c`

#### 19.4

See `19.4.c`

#### 19.5

No, this is not allowed since the `F_SETFL` command of `fcntl` does not change the read-write status.

#### 19.6

The login shell is a background process group and the session leader. `pty` and `cat` are the foreground process group.

#### 19.7

The `cat` program terminates first, followed by `pty`'s child process and then it's parent process.

#### 19.8

See `19.8.sh`

#### 19.9

The PTY slave has echo disabled, anything that `pty` reads from standard input and anything that is written to the PTY master is always echoed.

#### 19.10

See `19.10.c` and `19.10.child.c`
