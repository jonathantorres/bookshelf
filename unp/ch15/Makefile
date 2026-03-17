CFLAGS := gcc -std=gnu11 -Wall -Wextra -Wpedantic
PROGS := 15.4 15.5
LIBS := ../code/libunp.a

$(PROGS):%: ./%.c
	$(CFLAGS) $^ $(LIBS) -o $@
	./$@

.PHONY: clean
clean:
	rm -f ./*.o ./*.h.gch
	rm -f $(PROGS)
