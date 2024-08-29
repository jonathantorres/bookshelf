CFLAGS := gcc -std=gnu11 -Wall -Wextra -Wpedantic
PROGS := 2.3
LIBS := ../code/lib/error.o

$(PROGS):%: ./%.c
	$(CFLAGS) $^ $(LIBS) -o $@
	./$@

.PHONY: clean
clean:
	rm -f ./*.o ./*.h.gch
	rm -f $(PROGS)
