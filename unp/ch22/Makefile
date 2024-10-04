CFLAGS := gcc -std=gnu11 -Wall -Wextra -Wpedantic
PROGS := 22.3 22.5 22.6
LIBS := ../code/libunp.a

$(PROGS):%: ./%.c
	$(CFLAGS) $^ $(LIBS) -o $@
	./$@

.PHONY: clean
clean:
	rm -f ./*.o ./*.h.gch
	rm -f $(PROGS)
