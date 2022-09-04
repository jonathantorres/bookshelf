CFLAGS := gcc -std=gnu11 -Wall -Wextra -pthread

stat: stat.c
	$(CFLAGS) stat.c -o stat
lfiles: lfiles.c
	$(CFLAGS) lfiles.c -o lfiles
tail: tail.c
	$(CFLAGS) tail.c -o tail
rsearch: rsearch.c
	$(CFLAGS) rsearch.c -o rsearch
clean:
	rm -f stat lfiles tail rsearch
