CFLAGS := gcc -std=gnu11 -Wall -Wextra -pthread

udpclient: udpclient.c udp.h
	$(CFLAGS) udpclient.c -o udpclient
udpserver: udpserver.c udp.h
	$(CFLAGS) udpserver.c -o udpserver
clean:
	rm -f udpclient udpserver
