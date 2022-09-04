## 14. Interlude: Memory API (Answers)

1. See `null.c`. The program will segfault

2. Debug information on the program and where it segfaults

3. A lot of output, but readable, it states in what line of the C program the segfault happens

4. Valgrind reports the lost memory on the program (since it wasn't freed)

5. Nothing, runs normally without crashing. Valgrind reports an invalid read, probably since 100 is out of bounds

6. Program runs, valgrind reports access to freed memory

7. Program runs, compiler emits a warning, valgrind also reports an invalid read

8. See `ex8.c` which is a dynamic array

9. Read the manuals
