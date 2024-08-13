CFLAGS := gcc -std=c11 -Wall -Wextra -Wpedantic
PROGS := 8.5 8.6 8.20 8.22

8.7: 8.7.c
	gcc csapp.c $^ -o $@
	./$@

8.24: 8.24.c
	gcc csapp.c $^ -o $@
	./$@

8.25: 8.25.c
	gcc csapp.c $^ -o $@
	./$@

8.26: 8.26.c
	gcc csapp.c $^ -o $@
	./$@

$(PROGS):%: ./%.c
	$(CFLAGS) $^ -o $@
	./$@

.PHONY: clean
clean:
	rm -f ./*.o ./*.h.gch
	rm -f $(PROGS) 8.7 8.24 8.25 8.26
