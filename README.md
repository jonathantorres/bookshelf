# Go Intro
Exercises and answers to questions from the "Introducing Go" book.  

![Book Cover](https://github.com/jonathantorres/gointro/blob/master/cover.jpg)

## Compile and run programs
After cloning the repository somewhere in your `GOPATH` location, to compile and run the programs, you have a few options:
1. Run a program with `go build`, specifying the location of the program you want to run. For example, to build and run the `helloworld` program from chapter 1 you'll do `go build gointro/ch1/helloworld` to compile the program and `./helloworld` to run it.
2. You can also `cd` into the specific project directory of a chapter and compile and run directly from there. For example, to build and run the `helloworld` program from chapter 1 you'll do:
```
cd $GOPATH/gointro/ch1/helloworld
go build
./helloworld
```
