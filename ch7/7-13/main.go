package main

import (
	"fmt"
	"os"

	"github.com/jonathantorres/gopl/ch7/7-13/eval"
)

func main() {
	e, err := eval.Parse("2*2 + (44 + 12)")
	if err != nil {
		fmt.Fprintf(os.Stderr, "%s\n", err)
	}
	fmt.Fprintf(os.Stdout, "%s = %v\n", eval.Format(e), e.Eval(nil))
	fmt.Fprintf(os.Stdout, "%s\n", e)
}
