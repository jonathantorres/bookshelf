## Chapter 7 - Process Environment

#### 7.1

In some systems the returned value from `main` is the amount of bytes written with `printf`

#### 7.2

The output occurs when a newline is encountered on the input, this would be the case as long as the buffer is line-buffered

#### 7.3

No, these values are not stored anywhere else in the environment

#### 7.4

It provides a way to terminate the process when dereferencing a NULL pointer

#### 7.5

- The type alias is: `typedef void Exitfunc(void);`
- The new function prototype is: `int atexit(Exitfunc *func);`

#### 7.6

Yes, the array is initialized to zero, but this does not guarantee that these are the correct default values for `long`s and pointers

#### 7.7

These values are dynamic and are not known until the program is executed

#### 7.8

Because the executable file also contains symbol table information that is useful for debugging the program

#### 7.9

Most of the data in the executable comes from the standard C library

#### 7.10

No, since it dereferences a variable that is out of scope
