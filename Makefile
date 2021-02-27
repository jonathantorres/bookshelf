CFLAGS := gcc -std=c11 -Wall -Wextra -pthread

# Chapter 2 programs
daemon: ch2/daemon.c
	$(CFLAGS) ch2/daemon.c -o bin/daemon
access: ch2/access.c
	$(CFLAGS) ch2/access.c -o bin/access
sleep: ch2/sleep.c
	$(CFLAGS) ch2/sleep.c -o bin/sleep
system: ch2/system.c
	$(CFLAGS) ch2/system.c -o bin/system
# Chapter 3 programs
filelock: ch3/filelock.c
	$(CFLAGS) ch3/filelock.c -o bin/filelock
reclock: ch3/reclock.c
	$(CFLAGS) ch3/reclock.c -o bin/reclock
multi_buff_cli: ch3/multi_buff_cli.c
	$(CFLAGS) ch3/multi_buff_cli.c -o bin/multi_buff_cli
multi_buff_srv: ch3/multi_buff_srv.c
	$(CFLAGS) ch3/multi_buff_srv.c -o bin/multi_buff_srv

clean:
	rm -f ./*.o ch*/*.h.gch
	rm -Rf ./bin && mkdir bin && touch ./bin/.gitkeep
