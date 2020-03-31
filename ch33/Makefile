CFLAGS := gcc -std=gnu11 -Wall -Wextra -pthread

tcpserver: tcpserver.c
	$(CFLAGS) tcpserver.c -o tcpserver
serverselect: serverselect.c
	$(CFLAGS) serverselect.c -o serverselect
httpserver: httpserver.c
	$(CFLAGS) httpserver.c -o httpserver
asynchttpserver: asynchttpserver.c
	$(CFLAGS) asynchttpserver.c -o asynchttpserver

clean:
	rm -f tcpserver serverselect httpserver asynchttpserver
