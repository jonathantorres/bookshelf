CFLAGS := gcc -std=gnu11 -Wall -Wextra -Wpedantic
PROGS := 5.1
LIBS := ../code/lib/error.o ../code/lib/pathalloc.o

$(PROGS):%: ./%.c
	$(CFLAGS) $^ $(LIBS) -o $@
	./$@

.PHONY: clean
clean:
	rm -f ./*.o ./*.h.gch
	rm -f $(PROGS)
