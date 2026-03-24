## Chapter 3 - File I/O

#### 3.1

They are unbuffered for the user process, but there is internal buffering done by the kernel before writing/reading the contents to/from disk.

#### 3.2

See `3.2.c`

#### 3.3

Only `fd1` is affected by a `fcntl` on `fd1`. On the other hand both `fd1` and `fd2` are affected by a `fcntl` with a command of `F_SETFL` on `fd1`.
![diagram](https://github.com/jonathantorres/bookshelf/blob/master/apue/img/3.3.png)

#### 3.4

If we assume that `fd = 1`:
![diagram](https://github.com/jonathantorres/bookshelf/blob/master/apue/img/3.4a.png)

If we assume that `fd = 3`:
![diagram](https://github.com/jonathantorres/bookshelf/blob/master/apue/img/3.4b.png)

#### 3.5

The first redirects `stdout` and `stderr` to `outfile`, the second redirects `stdout` to `outfile` and `stderr` is redirected to the terminal

#### 3.6

Yes, you can `read` from anywhere in the file using `lseek`, but when you `write` to the file, regardless of where the file position is in the file, the `write` will be issued at the end of the file due to the append flag.
