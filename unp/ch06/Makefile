CFLAGS := gcc -std=gnu11 -Wall -Wextra -Wpedantic
PROGS := 6.4 6.5 6.8
LIBS := ../code/libunp.a

$(PROGS):%: ./%.c
	$(CFLAGS) $^ $(LIBS) -o $@
	./$@

.PHONY: clean
clean:
	rm -f ./*.o ./*.h.gch
	rm -f $(PROGS)
