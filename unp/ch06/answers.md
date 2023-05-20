## Answers to exercises

1. See `tcp_srvd.c`

2. ***Platform no longer supported***

3. The server won't be able to read the data, since it reads the input from the socket line by line, as text.

4. See `rresvport.c`

5. See `tcp_print.c`

6. See `select.c`

7. Definitely stream sockets, since it uses TCP and it guarantees the delivery of the messages, also different unrelated processes can comunicate using it

8. See `writev_srv.c` and `writev_cli.c`

9. ***Do a test on the different systems***
