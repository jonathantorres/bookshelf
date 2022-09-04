## Answers to exercises

1. See `rmt.c`

2. Works by sending a response to the client before doing the write, it would work almost the same as the previous exercise

3. The `read` or the `write` is set to the current terminal (tty)

4. I would think that an exclusion lock is needed (similar to the file locks that we created in chapter 3), so that the operations on the file are atomic
