CFLAGS := gcc -std=gnu11 -Wall -Wextra -Wpedantic
PROGS := 14.1 14.6 14.10 14.11
LIBS := ../code/lib/error.o ../code/lib/pathalloc.o ../code/lib/lockreg.o ../code/lib/signalintr.o

$(PROGS):%: ./%.c
	$(CFLAGS) $^ $(LIBS) -o $@
	./$@

.PHONY: clean
clean:
	rm -f ./*.o ./*.h.gch
	rm -f $(PROGS)
