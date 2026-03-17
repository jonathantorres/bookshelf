CFLAGS := gcc -std=gnu11 -Wall -Wextra -Wpedantic
PROGS := 7.1 7.2 7.3
LIBS := ../code/libunp.a

$(PROGS):%: ./%.c
	$(CFLAGS) $^ $(LIBS) -o $@
	./$@

.PHONY: clean
clean:
	rm -f ./*.o ./*.h.gch
	rm -f $(PROGS)
