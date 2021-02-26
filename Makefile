CFLAGS := gcc -std=c11 -Wall -Wextra

# Chapter 2 programs
daemon: ch2/daemon.c
	$(CFLAGS) ch2/daemon.c -o bin/daemon
access: ch2/access.c
	$(CFLAGS) ch2/access.c -o bin/access
sleep: ch2/sleep.c
	$(CFLAGS) ch2/sleep.c -o bin/sleep
system: ch2/system.c
	$(CFLAGS) ch2/system.c -o bin/system

clean:
	rm -f ./*.o ch*/*.h.gch
	rm -Rf ./bin && mkdir bin && touch ./bin/.gitkeep
