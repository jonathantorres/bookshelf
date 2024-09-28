CFLAGS := gcc -std=gnu11 -Wall -Wextra -Wpedantic
PROGS := 11.1 11.2 11.4 11.5 11.6 11.8
LIBS := ../code/libunp.a

$(PROGS):%: ./%.c
	$(CFLAGS) $^ $(LIBS) -o $@
	./$@

.PHONY: clean
clean:
	rm -f ./*.o ./*.h.gch
	rm -f $(PROGS)
