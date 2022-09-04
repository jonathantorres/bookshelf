package main

import "fmt"

func zero(xptr *int) {
	*xptr = 0
}

func main() {
	x := 3
	fmt.Println(x)
	zero(&x)
	fmt.Println(x)
}
