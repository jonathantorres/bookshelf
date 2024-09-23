CFLAGS := gcc -std=gnu11 -Wall -Wextra -Wpedantic
PROGS := 19.2 19.3 19.4 19.10 19.10.child
LIBS := ../code/lib/error.o ../code/lib/pathalloc.o ../code/lib/lockreg.o ../code/lib/signalintr.o ../code/lib/clrfl.o ../code/lib/tellwait.o ../code/sockets/initsrv1.o ../code/lib/recvfd.o ../code/lib/sendfd.o ../code/lib/ttymodes.o ../code/lib/ptyfork.o ../code/lib/writen.o ../code/lib/linux_ptyopen.o

$(PROGS):%: ./%.c
	$(CFLAGS) $^ $(LIBS) -o $@
	./$@

.PHONY: clean
clean:
	rm -f ./*.o ./*.h.gch
	rm -f $(PROGS)
