CFLAGS := gcc -std=c11 -Wall -Wextra
CH1_PROGS := 1-1 1-2 1-3 1-4 1-5       \
             1-6 1-7 1-8 1-9 1-10      \
             1-12 1-13 1-14 1-15       \
             1-16 1-17 1-18 1-19       \
             1-20 1-21 1-22 1-23 1-24

CH2_PROGS := 2-1 2-2 2-3 2-4 2-5       \
             2-6 2-7 2-8 2-9 2-10

CH3_PROGS := 3-1 3-2 3-3 3-4 3-5 3-6

CH4_PROGS := 4-1 4-2 4-3 4-4 4-5       \
             4-6 4-7 4-8 4-9 4-10      \
             4-11 4-12 4-13 4-14

CH5_PROGS := 5-1 5-2 5-3 5-4 5-5       \
             5-6 5-7 5-8 5-9 5-10      \
             5-11 5-12 5-13 5-14 5-15  \
             5-16 5-17 5-18 5-19 5-20

CH6_PROGS := 6-1 6-2 6-3 6-4 6-5 6-6

CH7_PROGS := 7-1 7-2 7-3 7-4 7-5       \
             7-6 7-7 7-8 7-9

CH8_PROGS := 8-1 8-2 8-3 8-4 8-5       \
             8-6 8-7 8-8

# chapter 1 programs
$(CH1_PROGS):%: ch1/%.c
	$(CFLAGS) $^ -o bin/$@
	./bin/$@

# chapter 2 programs
$(CH2_PROGS):%: ch2/%.c
	$(CFLAGS) $^ -o bin/$@
	./bin/$@

# chapter 3 programs
$(CH3_PROGS):%: ch3/%.c
	$(CFLAGS) $^ -o bin/$@
	./bin/$@

# chapter 4 programs
$(CH4_PROGS):%: ch4/%.c
	$(CFLAGS) $^ -o bin/$@
	./bin/$@

# chapter 5 programs
$(CH5_PROGS):%: ch5/%.c
	$(CFLAGS) $^ -o bin/$@
	./bin/$@

# chapter 6 programs
$(CH6_PROGS):%: ch6/%.c
	$(CFLAGS) $^ -o bin/$@
	./bin/$@

# chapter 7 programs
$(CH7_PROGS):%: ch7/%.c
	$(CFLAGS) $^ -o bin/$@
	./bin/$@

# chapter 8 programs
$(CH8_PROGS):%: ch8/%.c
	$(CFLAGS) $^ -o bin/$@
	./bin/$@

.PHONY: clean
clean:
	rm -f ./*.o ch*/*.h.gch
	rm -Rf ./bin && mkdir bin && touch ./bin/.gitkeep
