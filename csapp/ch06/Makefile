CFLAGS := gcc -std=c11 -Wall -Wextra -Wpedantic
PROGS := 6.7 6.45 6.46

$(PROGS):%: ./%.c
	$(CFLAGS) $^ -o $@ -lm
	./$@

.PHONY: clean
clean:
	rm -f ./*.o ./*.h.gch
	rm -f $(PROGS)
