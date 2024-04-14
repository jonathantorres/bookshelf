## Answers to exercises

1. That client connection will be rejected. Maybe another user will have to logout from their session

2. The standard terminal handler in System V does not support streams. It is not a streams device

3. Because it processes each character at a time

4. Is transferred as plaintext

5. Window changes from the server need to be sent before any other data. This way the window is updated accordingly

6. Both are read by the child process of the `rcmd` function

7. It sets the user id of the slave to the real uid of the calling process, the group id is set to an unspecified value (for example a tty) and the mode of the slave is set to `0620`

8. They're not that different, but `TELNET` is a protocol that is independent of the underlying operating system, `rlogin` is a BSD specific function

9. The figure stays the same, but the data does not go through the network, it's transferred locally on the same host

10. I think that using a modem only changes the underlying network for communication. The interaction of the processes at the kernel level between the local host and the remote host stay the same?
