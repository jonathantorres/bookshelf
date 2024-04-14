package main

import (
	"bufio"
	"fmt"
	"os"

	"github.com/jonathantorres/gopl/ch7/eval"
)

func main() {
	s := bufio.NewScanner(os.Stdin)
	for s.Scan() {
		l := s.Text()
		exp, err := eval.Parse(l)
		if err != nil {
			fmt.Fprintf(os.Stderr, "parse error %s\n", err)
			continue
		}
		vars := make(map[eval.Var]bool)
		err = exp.Check(vars)
		if err != nil {
			fmt.Fprintf(os.Stderr, "check error %s\n", err)
			continue
		}
		if len(vars) == 0 {
			fmt.Printf("%v\n", exp.Eval(nil))
			continue
		}
		env := make(map[eval.Var]float64)
		for v := range vars {
			var val float64
			fmt.Printf("provide a value for %s: ", v)
			_, err = fmt.Fscanf(os.Stdin, "%f", &val)
			if err != nil {
				fmt.Fprintf(os.Stderr, "could not parse value of %s, skipping\n", v)
				continue
			}
			env[v] = val
		}
		fmt.Printf("%s = %v\n", eval.Format(exp), exp.Eval(env))
	}
	if err := s.Err(); err != nil {
		fmt.Fprintf(os.Stderr, "scan error %s\n", err)
	}
}
