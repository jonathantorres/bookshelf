CFLAGS := gcc -std=gnu11 -Wall -Wextra -pthread

fork-join: fork-join.c
	$(CFLAGS) fork-join.c -o fork-join
rendezvous: rendezvous.c
	$(CFLAGS) rendezvous.c -o rendezvous
barrier: barrier.c
	$(CFLAGS) barrier.c -o barrier
reader-writer: reader-writer.c
	$(CFLAGS) reader-writer.c -o reader-writer
reader-writer-nostarve: reader-writer-nostarve.c
	$(CFLAGS) reader-writer-nostarve.c -o reader-writer-nostarve
mutex-nostarve: mutex-nostarve.c
	$(CFLAGS) mutex-nostarve.c -o mutex-nostarve

clean:
	rm -f fork-join rendezvous barrier reader-writer reader-writer-nostarve mutex-nostarve
