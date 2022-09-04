CC = gcc
CFLAGS = -Werror -Wextra -Wall -pedantic

.DEFAULT_GOAL: dv_route

.PHONY: clean cleanall

node0.o: node0.c node0.h
	$(CC) $(CFLAGS) -c node0.c

node1.o: node1.c node1.h
	$(CC) $(CFLAGS) -c node1.c

node2.o: node2.c node2.h
	$(CC) $(CFLAGS) -c node2.c

node3.o: node3.c node3.h
	$(CC) $(CFLAGS) -c node3.c

main.o: main.c main.h
	$(CC) $(CFLAGS) -c main.c

dv_route: node0.o node1.o node2.o node3.o main.o
	$(CC) $(CFLAGS) node0.o node1.o node2.o node3.o main.o -o dv_route

clean:
	rm -f dv_route

cleanall: clean
	rm -f node0.o node1.o node2.o node3.o main.o
