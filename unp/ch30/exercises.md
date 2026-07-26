## Chapter 30 - Client/Server Design Alternatives

#### 30.1

The parent must keep the listening socket open in case it needs to `fork` more children at a later time.

#### 30.2

Yes, this can be done. In this setup, the parent does not receive an EOF when a child terminates, but it could use the `SIGCHLD` signal for this.
