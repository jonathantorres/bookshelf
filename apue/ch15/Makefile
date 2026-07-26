CFLAGS := gcc -std=gnu11 -Wall -Wextra -Wpedantic
PROGS := 15.1 15.3 15.5 15.10 15.12 15.15 15.16 15.17
LIBS := ../code/lib/error.o ../code/lib/pathalloc.o ../code/lib/lockreg.o ../code/lib/signalintr.o ../code/lib/clrfl.o ../code/lib/tellwait.o

$(PROGS):%: ./%.c
	$(CFLAGS) $^ $(LIBS) -o $@
	./$@

.PHONY: clean
clean:
	rm -f ./*.o ./*.h.gch
	rm -f $(PROGS)
