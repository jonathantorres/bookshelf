CFLAGS := gcc -std=c11 -Wall -Wextra

1-1: ch1/1-1.c
	$(CFLAGS) ch1/1-1.c -o bin/1-1
	./bin/1-1
1-2: ch1/1-2.c
	$(CFLAGS) ch1/1-2.c -o bin/1-2
	./bin/1-2
1-3: ch1/1-3.c
	$(CFLAGS) ch1/1-3.c -o bin/1-3
	./bin/1-3
1-4: ch1/1-4.c
	$(CFLAGS) ch1/1-4.c -o bin/1-4
	./bin/1-4
1-5: ch1/1-5.c
	$(CFLAGS) ch1/1-5.c -o bin/1-5
	./bin/1-5

clean:
	rm -f ./*.o ch*/*.h.gch
	rm -Rf ./bin && mkdir bin && touch ./bin/.gitkeep
