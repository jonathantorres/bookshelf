package main

import (
	"fmt"
)

func main() {
	var a int
	mscanf("%d\n", &a)
	fmt.Printf("%d\n", a)
}

func mscanf(fm string, ap ...interface{}) int {
	n, _ := fmt.Scanf(fm, ap...)
	return n
}
