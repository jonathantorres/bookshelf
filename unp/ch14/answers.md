## Answers to exercises

1. The server will have to capture the returned status code from the `execl`, use the socket to send this returned status code back to the client

2. Either would probably work fine, but I would first implement it with stream pipes. We can create a separate pipe to send the `stderr` file descriptor

3. They're not exactly the same, but if a signal is not supported in a different variation of Unix, it is ignored

4. Because the client can't encrypt the password, since it belongs to the user in the remote system. The `/etc/passwd` on the remote system is needed for that

5. It needs to know if the user can `access` it first, because the file can exist without having the proper privileges to open.
