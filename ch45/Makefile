CFLAGS := gcc -std=gnu11 -Wall -Wextra -pthread

checkxor: checkxor.c
	$(CFLAGS) checkxor.c -o checkxor
checkfletcher: checkfletcher.c
	$(CFLAGS) checkfletcher.c -o checkfletcher
createcsum: createcsum.c
	$(CFLAGS) createcsum.c -o createcsum
checkcsum: checkcsum.c
	$(CFLAGS) checkcsum.c -o checkcsum
clean:
	rm -f checkxor checkfletcher createcsum checkcsum
