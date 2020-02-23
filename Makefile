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
1-16: ch1/1-16.c
	$(CFLAGS) ch1/1-16.c -o bin/1-16
	./bin/1-16
1-17: ch1/1-17.c
	$(CFLAGS) ch1/1-17.c -o bin/1-17
	./bin/1-17
1-18: ch1/1-18.c
	$(CFLAGS) ch1/1-18.c -o bin/1-18
	./bin/1-18
1-19: ch1/1-19.c
	$(CFLAGS) ch1/1-19.c -o bin/1-19
	./bin/1-19
1-20: ch1/1-20.c
	$(CFLAGS) ch1/1-20.c -o bin/1-20
	./bin/1-20
1-21: ch1/1-21.c
	$(CFLAGS) ch1/1-21.c -o bin/1-21
	./bin/1-21
1-22: ch1/1-22.c
	$(CFLAGS) ch1/1-22.c -o bin/1-22
	./bin/1-22
1-23: ch1/1-23.c
	$(CFLAGS) ch1/1-23.c -o bin/1-23
	./bin/1-23
1-24: ch1/1-24.c
	$(CFLAGS) ch1/1-24.c -o bin/1-24
	./bin/1-24

2-1: ch2/2-1.c
	$(CFLAGS) ch2/2-1.c -o bin/2-1
	./bin/2-1
2-2: ch2/2-2.c
	$(CFLAGS) ch2/2-2.c -o bin/2-2
	./bin/2-2
2-3: ch2/2-3.c
	$(CFLAGS) ch2/2-3.c -o bin/2-3
	./bin/2-3
2-4: ch2/2-4.c
	$(CFLAGS) ch2/2-4.c -o bin/2-4
	./bin/2-4
2-5: ch2/2-5.c
	$(CFLAGS) ch2/2-5.c -o bin/2-5
	./bin/2-5
2-6: ch2/2-6.c
	$(CFLAGS) ch2/2-6.c -o bin/2-6
	./bin/2-6
2-7: ch2/2-7.c
	$(CFLAGS) ch2/2-7.c -o bin/2-7
	./bin/2-7
2-8: ch2/2-8.c
	$(CFLAGS) ch2/2-8.c -o bin/2-8
	./bin/2-8
2-9: ch2/2-9.c
	$(CFLAGS) ch2/2-9.c -o bin/2-9
	./bin/2-9
2-10: ch2/2-10.c
	$(CFLAGS) ch2/2-10.c -o bin/2-10
	./bin/2-10

clean:
	rm -f ./*.o ch*/*.h.gch
	rm -Rf ./bin && mkdir bin && touch ./bin/.gitkeep
