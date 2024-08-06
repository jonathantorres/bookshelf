CFLAGS := gcc -std=c11 -Wall -Wextra -Wpedantic
PROGS := 3.5 3.7 3.10 3.18 3.21 3.24 3.25 3.26 3.27 3.28 3.31    \
		 3.35 3.54 3.57 3.58 3.60 3.61 3.62 3.63 3.71 3.73 3.74

$(PROGS):%: ./%.c
	$(CFLAGS) $^ -o $@ -lm
	./$@

.PHONY: clean
clean:
	rm -f ./*.o ./*.h.gch
	rm -f $(PROGS)
