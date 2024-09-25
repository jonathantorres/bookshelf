CFLAGS := gcc -std=gnu11 -Wall -Wextra -Wpedantic
PROGS := 20.6 20.7
LIBS := ../code/lib/error.o ../code/lib/lockreg.o ../code/lib/libapue.a ../code/db/libapue_db.a

$(PROGS):%: ./%.c
	$(CFLAGS) $^ $(LIBS) -o $@
	./$@

.PHONY: clean
clean:
	rm -f ./*.o ./*.h.gch
	rm -f $(PROGS)
