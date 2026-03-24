## Chapter 10 - Signals

#### 10.1

The program terminates the first time it catches one of the signals.

#### 10.2

See `10.2.c`

#### 10.3

Stack frames when running the program:

![diagram](https://github.com/jonathantorres/bookshelf/blob/master/apue/img/10.3.png)

#### 10.4

This causes a race condition when `alarm` is called for the first time and the call to `setjmp`. Specifically when the alarm goes off and the process is blocked by the kernel (due to scheduling) in between those two calls.

#### 10.5

See `10.5.c`

#### 10.6

See `10.6.c`

#### 10.7

By calling `_exit` we would not know that the process was terminated by the `SIGABRT` signal.

#### 10.8

The real user ID gives more information to the receiver of the signal, otherwise `kill` would not work properly.

#### 10.9

See `10.9.c`

#### 10.10

See `10.10.c`

#### 10.11

See `10.11.c`

#### 10.12

See `10.12.c`
