## Chapter 12 - Thread Control

#### 12.1

See `12.1.c`

#### 12.2

See `12.2.c`

#### 12.3

This could be done, but if any of the functions we call unmask a signal that we have blocked, then another signal handler could also change the internal state of a function and thus is no longer async-signal safe

#### 12.4

I could not test this thoroughly, but it seems that the program crashes due to an infinite loop

#### 12.5

`fork` is still useful for running a program from another program, for example a shell will do a `fork` before calling `exec` to execute the program in the child process

#### 12.6

See `12.6.c`

#### 12.7

No, this would be unsafe to do since the condition variable might have an internal mutex, which could cause a deadlock if its used after a process is forked
