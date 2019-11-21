CFLAGS := gcc -std=gnu11 -Wall -Wextra

3-2: 3-2.c
	$(CFLAGS) 3-2.c -o 3-2

3-16: 3-16.c hash_table.o array.o linked_list.o binary_tree.o
	$(CFLAGS) 3-16.c hash_table.o array.o linked_list.o binary_tree.o -o 3-16
	
3-17: 3-17.c
	$(CFLAGS) 3-17.c -o 3-17

3-20: 3-20.c
	$(CFLAGS) 3-20.c -o 3-20

3-21: 3-21.c binary_tree.o
	$(CFLAGS) 3-21.c binary_tree.o -o 3-21

3-22: 3-22.c linked_list.o binary_tree.o
	$(CFLAGS) 3-22.c linked_list.o binary_tree.o -o 3-22

3-23: 3-23.c
	$(CFLAGS) 3-23.c -o 3-23

# Compiling objects
linked_list.o: linked_list.c linked_list.h
	$(CFLAGS) -c linked_list.c linked_list.h
array.o: array.c array.h
	$(CFLAGS) -c array.c array.h
hash_table.o: hash_table.c hash_table.h
	$(CFLAGS) -c hash_table.c hash_table.h
binary_tree.o: binary_tree.c binary_tree.h
	$(CFLAGS) -c binary_tree.c binary_tree.h

clean:
	rm -f ./*.o ./*.h.gch *.out
	rm -f ./3-2 ./3-16 ./3-20 ./3-22 ./3-23
