CFLAGS := gcc -std=gnu11 -Wall -Wextra -Wpedantic
PROGS := syscall switch

$(PROGS):%: ./%.c
	$(CFLAGS) $^ -o $@
	./$@

.PHONY: clean
clean:
	rm -f ./*.o ./*.h.gch
	rm -f $(PROGS)

