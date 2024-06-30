### Exercise 5.52
A rudimentary Scheme interpreter.

### Compile
compile the program using the `go` toolchain and `make`. This would create the `scm` binary inside the `bin` directory
```bash
$ make
```

### Usage
After compiling, run the Scheme interpreter by starting the REPL:
```bash
./bin/scm
```

### Generate Go Instructions
Run the program that will compile the metacircular evaluator and send this output to the translator wchich will translate the Lisp-like instructions into Go-like instructions. This would generate a file named `eval.go`, this generated code is already checked-in into this repository:
```bash
guile 5.52.scm | php translate.php > eval.go
```


