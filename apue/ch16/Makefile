CFLAGS := gcc -std=gnu11 -Wall -Wextra -Wpedantic
PROGS := 16.1 16.2 16.3 16.4 16.5 16.6
LIBS := ../code/lib/error.o ../code/lib/pathalloc.o ../code/lib/lockreg.o ../code/lib/signalintr.o ../code/lib/clrfl.o ../code/lib/tellwait.o ../code/sockets/initsrv1.o

$(PROGS):%: ./%.c
	$(CFLAGS) $^ $(LIBS) -o $@
	./$@

.PHONY: clean
clean:
	rm -f ./*.o ./*.h.gch
	rm -f $(PROGS)
