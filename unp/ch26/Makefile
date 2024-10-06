CFLAGS := gcc -std=gnu11 -Wall -Wextra -Wpedantic
PROGS := 26.3 26.4
LIBS := ../code/libunp.a

$(PROGS):%: ./%.c
	$(CFLAGS) $^ $(LIBS) -o $@
	./$@

.PHONY: clean
clean:
	rm -f ./*.o ./*.h.gch
	rm -f $(PROGS)
