CFLAGS := gcc -std=gnu11 -Wall -Wextra -Wpedantic
PROGS := 17.2 17.4
LIBS := ../code/lib/error.o ../code/lib/pathalloc.o ../code/lib/lockreg.o ../code/lib/signalintr.o ../code/lib/clrfl.o ../code/lib/tellwait.o ../code/sockets/initsrv1.o ../code/lib/recvfd.o ../code/lib/sendfd.o

$(PROGS):%: ./%.c
	$(CFLAGS) $^ $(LIBS) -o $@
	./$@

.PHONY: clean
clean:
	rm -f ./*.o ./*.h.gch
	rm -f $(PROGS)
