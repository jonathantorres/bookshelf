CPPFLAGS = g++ -g -std=c++11 -Wall -Wextra
CH0_PROGS = 0-0 0-1 0-2 0-3 0-4 0-5               \
            0-6 0-7 0-8 0-9 0-10
CH1_PROGS = 1-0 1-1 1-2 1-3 1-4 1-5 1-6
CH2_PROGS = 2-0 2-1 2-2 2-3 2-4 2-5               \
            2-6 2-7 2-8 2-9 2-10
CH3_PROGS = 3-0 3-1 3-2 3-3 3-4 3-5 3-6
CH4_PROGS = 4-0 4-1 4-2 4-3 4-4 4-5 4-6           \
            4-7 4-8
CH5_PROGS = 5-0 5-1 5-2 5-3 5-4 5-5 5-6           \
            5-7 5-8 5-9 5-10 5-11
CH6_PROGS = 6-0 6-1 6-2 6-3 6-4 6-5 6-6           \
            6-7 6-8 6-9
CH7_PROGS = 7-0 7-1 7-2 7-3 7-4 7-5 7-6           \
            7-7 7-8 7-9
CH8_PROGS = 8-0 8-1 8-2 8-3 8-4 8-5 8-6           \
            8-7 8-8
CH9_PROGS = 9-0 9-1 9-2 9-3 9-4 9-5 9-6           \
            9-7

# chapter 0 programs
$(CH0_PROGS):%: ch00/%.cpp
	$(CPPFLAGS) $^ -o bin/$@
	./bin/$@

# chapter 1 programs
$(CH1_PROGS):%: ch01/%.cpp
	$(CPPFLAGS) $^ -o bin/$@
	./bin/$@

# chapter 2 programs
$(CH2_PROGS):%: ch02/%.cpp
	$(CPPFLAGS) $^ -o bin/$@
	./bin/$@

# chapter 3 programs
$(CH3_PROGS):%: ch03/%.cpp
	$(CPPFLAGS) $^ -o bin/$@
	./bin/$@

# chapter 4 programs
$(CH4_PROGS):%: ch04/%.cpp
	$(CPPFLAGS) $^ -o bin/$@
	./bin/$@

# chapter 5 programs
$(CH5_PROGS):%: ch05/%.cpp
	$(CPPFLAGS) $^ -o bin/$@
	./bin/$@

# chapter 6 programs
$(CH6_PROGS):%: ch06/%.cpp
	$(CPPFLAGS) $^ -o bin/$@
	./bin/$@

# chapter 7 programs
$(CH7_PROGS):%: ch07/%.cpp
	$(CPPFLAGS) $^ -o bin/$@
	./bin/$@

# chapter 8 programs
$(CH8_PROGS):%: ch08/%.cpp
	$(CPPFLAGS) $^ -o bin/$@
	./bin/$@

# chapter 9 programs
$(CH9_PROGS):%: ch09/%.cpp
	$(CPPFLAGS) $^ -o bin/$@
	./bin/$@

.PHONY: clean
clean:
	rm -f ./*.o ./*.h.gch
	rm -fr ./bin
	mkdir ./bin && touch ./bin/.gitkeep
