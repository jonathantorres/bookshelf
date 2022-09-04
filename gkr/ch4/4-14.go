package main

import "fmt"

func main() {
	x, y := 3, 7
	fmt.Printf("x=%d, y=%d\n", x, y)
	swap(&x, &y)
	fmt.Printf("x=%d, y=%d\n", x, y)
}

func swap(x *int, y *int) {
	tmp := *x
	*x = *y
	*y = tmp
}
