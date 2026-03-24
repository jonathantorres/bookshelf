## Chapter 5 - Standard I/O Library

#### 5.1

See `5.1.c`

#### 5.2

The input is printed normally, the caveat is that `fgets` is called more times due to the buffer being so small

#### 5.3

It means that no characters are written to standard output

#### 5.4

The loop never ends if the platform in which this code is compiled represents characters (the `char` type) as an unsigned number

#### 5.5

This is due to the limit on the amount of characters for a filename in a UNIX system

#### 5.6

You would call `fsync` after calling `fflush` on the stream

#### 5.7

`fgets` flushes the stream automatically
