## Chapter 27 - IP Options

#### 27.1

Nothing changes, since a strict route is the same as a loose source route.

#### 27.2

We would need to place a `NULL` byte `\0` at the end of the buffer.

#### 27.3

`ping` receives a complete IP header since it creates a raw socket. This header includes any IP options.

#### 27.4

This is because `rlogind` is invoked by `inetd`

#### 27.5

It doesn't really matter since that fifth argument is a pointer to the length instead of the actual length.
