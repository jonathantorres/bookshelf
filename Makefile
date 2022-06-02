CPPFLAGS = g++ -g -std=c++11 -Wall -Wextra
CH0_PROGS = 0-0 0-1 0-2 0-3 0-4 0-5     \
            0-6 0-7 0-8 0-9 0-10
CH1_PROGS = 1-0 1-1 1-2 1-3 1-4 1-5 1-6

# chapter 0 programs
$(CH0_PROGS):%: ch00/%.cpp
	$(CPPFLAGS) $^ -o bin/$@
	./bin/$@

# chapter 1 programs
$(CH1_PROGS):%: ch01/%.cpp
	$(CPPFLAGS) $^ -o bin/$@
	./bin/$@

.PHONY: clean
clean:
	rm -f ./*.o ./*.h.gch
	rm -fr ./bin
	mkdir ./bin && touch ./bin/.gitkeep
