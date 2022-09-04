CFLAGS = -Wall -g -DNDEBUG

all:
	cc -c -o ex22.o ex22.c
	cc ex22_main.c ex22.o -o ex22_main
	./ex22_main

clean:
	rm -fR ex22_main.dSYM
	rm -fR ex22_main
	rm -fR ex22.o
