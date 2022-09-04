package main

import (
	"fmt"
	"os"
	"strings"
)

func main() {
	echo1(os.Stdout, os.Args[1:])
	echo2(os.Stdout, os.Args)
	echo3(os.Stdout, os.Args)
}

func echo1(out *os.File, args []string) {
	s, sep := "", ""
	for _, arg := range args {
		s += sep + arg
		sep = " "
	}
	fmt.Fprintf(out, "%s\n", s)
}

func echo2(out *os.File, args []string) {
	for i, arg := range args {
		fmt.Fprintf(out, "%d %s\n", i, arg)
	}
}

func echo3(out *os.File, args []string) {
	fmt.Fprintf(out, "%s\n", strings.Join(args, " "))
}
