CFLAGS := gcc -std=c11 -Wall -Wextra -Wpedantic
PROGS := 5.9 5.12 5.17 5.18 5.19

$(PROGS):%: ./%.c
	$(CFLAGS) $^ -o $@ -lm
	./$@

.PHONY: clean
clean:
	rm -f ./*.o ./*.h.gch
	rm -f $(PROGS)
