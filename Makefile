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
1-6: ch1/1-6.c
	$(CFLAGS) ch1/1-6.c -o bin/1-6
	./bin/1-6
1-7: ch1/1-7.c
	$(CFLAGS) ch1/1-7.c -o bin/1-7
	./bin/1-7
1-8: ch1/1-8.c
	$(CFLAGS) ch1/1-8.c -o bin/1-8
	./bin/1-8
1-9: ch1/1-9.c
	$(CFLAGS) ch1/1-9.c -o bin/1-9
	./bin/1-9
1-10: ch1/1-10.c
	$(CFLAGS) ch1/1-10.c -o bin/1-10
	./bin/1-10
1-12: ch1/1-12.c
	$(CFLAGS) ch1/1-12.c -o bin/1-12
	./bin/1-12
1-13: ch1/1-13.c
	$(CFLAGS) ch1/1-13.c -o bin/1-13
	./bin/1-13
1-14: ch1/1-14.c
	$(CFLAGS) ch1/1-14.c -o bin/1-14
	./bin/1-14
1-15: ch1/1-15.c
	$(CFLAGS) ch1/1-15.c -o bin/1-15
	./bin/1-15

clean:
	rm -f ./*.o ch*/*.h.gch
	rm -Rf ./bin && mkdir bin && touch ./bin/.gitkeep
