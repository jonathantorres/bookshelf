CFLAGS := gcc -std=gnu11 -Wall -Wextra -Wpedantic
PROGS := 1 2 3 4 5 6 7 8

$(PROGS):%: ./%.c
	$(CFLAGS) $^ $(LIBS) -o $@
	./$@

.PHONY: clean
clean:
	rm -f ./*.o ./*.h.gch
	rm -f $(PROGS)

