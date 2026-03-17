CFLAGS := gcc -std=gnu11 -Wall -Wextra -Wpedantic
PROGS := 4.2 4.4 4.5
LIBS := ../code/libunp.a

$(PROGS):%: ./%.c
	$(CFLAGS) $^ $(LIBS) -o $@
	./$@

.PHONY: clean
clean:
	rm -f ./*.o ./*.h.gch
	rm -f $(PROGS)
