## Chapter 13 - Daemon Processes and the inetd Superserver

#### 13.1

`syslog` will log an error due to an invalid command-line argument.

#### 13.2

The TCP versions of `echo`, `discard` and `chargen` require a fork, on the other hand `time` and `daytime` do not require a fork as well as all the other 5 UDP services.

#### 13.3

This is a well-known DoS attack, one way to prevent this is to reject UDP datagrams to any internal server if the source port of the packet is also from an internal server.

#### 13.4

The IP Address of the client and the port come from the socket address structure returned by `accept`.
