# gopl
Exercises and answers to questions from the "The Go Programming Language" book.

![Book Cover](https://github.com/jonathantorres/gopl/blob/master/cover.jpg)

## Compile and run programs
After cloning your repository, you can run any of the solutions with `go run`. For example, to run exercise 6 of chapter 1:
```bash
git clone git@github.com:jonathantorres/gopl.git
cd gopl
go run ch1/1-6.go
```

If there's a folder for the exercise, then it means that it has more than 1 file, in that case you can run it and/or build it with `go build`:
```bash
cd gopl/ch1/1-3
go build
./1-3
```