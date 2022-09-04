package main

import "fmt"

func main() {
	var x uint = 150
	n := 3
	fmt.Printf("%d rightrot -> %d\n", x, rightrot(x, n)) // expected result: 210
}

func rightrot(x uint, n int) uint {
	b := getbits(x, n-1, n)
	nx := x >> n
	return setbits(nx, 7, n, b)
}

func setbits(x uint, p int, n int, y uint) uint {
	ry := getbits(y, n-1, n)
	ry = ry << (p + 1 - n)
	var m uint = ((1 << n) - 1) << (p + 1 - n)
	return x ^ ((x ^ ry) & uint(m))
}

func getbits(x uint, p int, n int) uint {
	return (x >> (p + 1 - n)) & ^(^uint(0) << n)
}
