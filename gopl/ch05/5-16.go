package main

import (
	"fmt"
	"strings"
)

func main() {
	s := []string{"one", "two", "three", "four"}
	fmt.Println(join(",", "s1", "s2", "s3", "s4"))
	fmt.Println(join(","))
	fmt.Println(join(",", s...))
}

func join(sep string, elems ...string) string {
	return strings.Join(elems, sep)
}
