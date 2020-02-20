CFLAGS := gcc -std=c11 -Wall -Wextra

1-1: ch1/1-1.c
	$(CFLAGS) ch1/1-1.c -o bin/1-1
	./bin/1-1
1-2: ch1/1-2.c
	$(CFLAGS) ch1/1-2.c -o bin/1-2
	./bin/1-2

clean:
	rm -f ./*.o ch*/*.h.gch
	rm -Rf ./bin && mkdir bin && touch ./bin/.gitkeep
