CFLAGS := gcc -std=gnu11 -Wall -Wextra

gettime: gettime.c
	$(CFLAGS) gettime.c -o gettime
simple_counter: simple_counter.c
	$(CFLAGS) simple_counter.c -o simple_counter
slop_counter: slop_counter.c
	$(CFLAGS) slop_counter.c -o slop_counter
list: list.c
	$(CFLAGS) list.c -o list
tree: tree.c
	$(CFLAGS) tree.c -o tree

clean:
	rm gettime simple_counter slop_counter list tree
