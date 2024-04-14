package main

import (
	"fmt"
	"os"

	"github.com/jonathantorres/gopl/ch7/7-14/eval"
)

func main() {
	// operation added: min
	// 11 min 10 = 10
	e := eval.Min{"min", eval.Literal(11), eval.Literal(10)}
	err := e.Check(nil)
	if err != nil {
		fmt.Fprintf(os.Stderr, "%s\n", err)
		os.Exit(1)
	}
	fmt.Fprintf(os.Stdout, "%s = %v\n", eval.Format(e), e.Eval(nil))
}
