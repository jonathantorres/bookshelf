package main

import "fmt"

func main() {
	var x uint = 225
	p := 4
	n := 2
	fmt.Printf("%d inverted = %d\n", x, invert(x, p, n))
}

func invert(x uint, p int, n int) uint {
	b := getbits(x, p, n)
	return setbits(x, p, n, ^b)
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
