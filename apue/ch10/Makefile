CFLAGS := gcc -std=gnu11 -Wall -Wextra -Wpedantic
PROGS := 10.2 10.5 10.6 10.9 10.10 10.11 10.12
LIBS := ../code/lib/error.o ../code/lib/pathalloc.o

$(PROGS):%: ./%.c
	$(CFLAGS) $^ $(LIBS) -o $@
	./$@

.PHONY: clean
clean:
	rm -f ./*.o ./*.h.gch
	rm -f $(PROGS)
