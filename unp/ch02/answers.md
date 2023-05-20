## Answers to exercises

1. It has no effect on the parent process. The updated values are sent to any child process that is invoked.

2. None, since the user id of the process is being set to the user id of the current process. Done when a program is executed as root, but we want to change it's user id as the current logged in user.

3. It's stored in an internal thread-specific memory, they return a pointer to the structure.

4. The encrypted password is substituted by an asteric, and the actual encrypted password is stored in the `/etc/shadow` file, which can be read only by the superuser.

5. See `access.c`

6. No, I don't think it makes a difference, is basically the same thing. Now, I don't think that the operating system will allow both process to write to the same file at the same time.

7. See `sleep.c`

8. Because the parent needs the process id of the child so that the program can continue as the child process if it wishes to do so. Also there's no system call to get the process id of the child from the parent, other than by using the returned process id from the `fork` system call.

9. See `system.c`

10. No, they are completely independent.
