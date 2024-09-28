CFLAGS := gcc -std=gnu11 -Wall -Wextra -Wpedantic
PROGS := 8.3.client 8.3.server 8.8 8.9
LIBS := ../code/libunp.a

$(PROGS):%: ./%.c
	$(CFLAGS) $^ $(LIBS) -o $@
	./$@

.PHONY: clean
clean:
	rm -f ./*.o ./*.h.gch
	rm -f $(PROGS)
