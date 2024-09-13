CFLAGS := gcc -std=gnu11 -Wall -Wextra -Wpedantic
PROGS := 1.2 1.3 1.4 1.5
LIBS := ../code/libunp.a

$(PROGS):%: ./%.c
	$(CFLAGS) $^ $(LIBS) -o $@
	./$@

.PHONY: clean
clean:
	rm -f ./*.o ./*.h.gch
	rm -f $(PROGS)
