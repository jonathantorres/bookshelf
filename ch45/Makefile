CFLAGS := gcc -std=gnu11 -Wall -Wextra -pthread

checkxor: checkxor.c
	$(CFLAGS) checkxor.c -o checkxor
checkfletcher: checkfletcher.c
	$(CFLAGS) checkfletcher.c -o checkfletcher
createcsum: createcsum.c
	$(CFLAGS) createcsum.c -o createcsum
checkcsum: checkcsum.c
	$(CFLAGS) checkcsum.c -o checkcsum
compare: compare.c
	$(CFLAGS) compare.c -o compare
crc: crc.c
	$(CFLAGS) crc.c -o crc
clean:
	rm -f checkxor checkfletcher createcsum checkcsum compare crc
