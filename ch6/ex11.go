package main

import (
	"fmt"
)

func main() {
	x, y := 1, 2
	z, w := 10, 100
	swap(&x, &y)
	swap(&z, &w)
	fmt.Println(x, y)
	fmt.Println(z, w)
}

func swap(x *int, y *int) {
	*x, *y = *y, *x
}
