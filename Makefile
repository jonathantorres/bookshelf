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
# Chapter 6 Programs
tcp_srvd: ch6/tcp_srvd.c
	$(CFLAGS) ch6/tcp_srvd.c -o bin/tcp_srvd
spp: ch6/spp.c
	$(CFLAGS) ch6/spp.c -o bin/spp
rresvport: ch6/rresvport.c
	$(CFLAGS) ch6/rresvport.c -o bin/rresvport
tcp_print: ch6/tcp_print.c
	$(CFLAGS) ch6/tcp_print.c -o bin/tcp_print
select: ch6/select.c
	$(CFLAGS) ch6/select.c -o bin/select
writev_srv: ch6/writev_srv.c
	$(CFLAGS) ch6/writev_srv.c -o bin/writev_srv
writev_cli: ch6/writev_cli.c
	$(CFLAGS) ch6/writev_cli.c -o bin/writev_cli
# Chapter 11 Program
ping: ch11/ping.c
	$(CFLAGS) ch11/ping.c -o bin/ping
# Chapter 12 Programs
tftp_cli: ch12/tftp_cli.c
	$(CFLAGS) ch12/tftp_cli.c -o bin/tftp_cli
tftp_srv: ch12/tftp_srv.c
	$(CFLAGS) ch12/tftp_srv.c -o bin/tftp_srv
clean:
	rm -f ./*.o ch*/*.h.gch
	rm -Rf ./bin && mkdir bin && touch ./bin/.gitkeep
