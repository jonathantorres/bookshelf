## Chapter 8 - Process Control

#### 8.1

See `8.1.c`

#### 8.2

See `8.2.c`

#### 8.3

This is another race condition, we have the parent send it's output first, but it may terminate before the child does (this would depend on the scheduling algorithm of the kernel). When the parent terminates, the shell starts the next program, and it interferes with the output of the previous child.

#### 8.4

`/home/sar/bin/testinterp` is also printed for `argv[2]`

#### 8.5

There is no function to return the saved set-user-ID, so we must save it using the effective user ID when the program begins

#### 8.6

See `8.6.c`
