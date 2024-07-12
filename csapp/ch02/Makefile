CFLAGS := gcc -std=c11 -Wall -Wextra -Wpedantic
PROGS := 2.13 2.27 2.30 2.36 2.42 2.53 2.55 2.56 2.57

$(PROGS):%: ./%.c
	$(CFLAGS) $^ -o $@
	./$@

.PHONY: clean
clean:
	rm -f ./*.o ./*.h.gch
	rm -f $(PROGS)
