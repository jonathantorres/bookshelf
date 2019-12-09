CFLAGS := gcc -std=gnu11 -Wall -Wextra

4-37: 4-37.c array.o bubble_sort.o insertion_sort.o selection_sort.o merge_sort.o quick_sort.o priority_queue.o
	$(CFLAGS) 4-37.c array.o bubble_sort.o insertion_sort.o selection_sort.o merge_sort.o quick_sort.o priority_queue.o -o 4-37

# Compiling objects
array.o: array.c array.h
	$(CFLAGS) -c array.c array.h
bubble_sort.o: bubble_sort.c bubble_sort.h
	$(CFLAGS) -c bubble_sort.c bubble_sort.h
insertion_sort.o: insertion_sort.c insertion_sort.h
	$(CFLAGS) -c insertion_sort.c insertion_sort.h
selection_sort.o: selection_sort.c selection_sort.h
	$(CFLAGS) -c selection_sort.c selection_sort.h
merge_sort.o: merge_sort.c merge_sort.h
	$(CFLAGS) -c merge_sort.c merge_sort.h
quick_sort.o: quick_sort.c quick_sort.h
	$(CFLAGS) -c quick_sort.c quick_sort.h
priority_queue.o: priority_queue.c priority_queue.h
	$(CFLAGS) -c priority_queue.c priority_queue.h

clean:
	rm -f ./*.o ./*.h.gch *.out
	rm -f ./4-37
