## Answers to exercises

1. Use a TCP socket instead of a UNIX domain socket, this way the data can be transferred through different process that are not running on the same system. See `lpr.c`

2. Same as the previous answer, use a TCP socket. See `lpr.c`

3. I would think the same as the two answers, use a TCP socket, it should work accross different OS's. See `lpr.c`
