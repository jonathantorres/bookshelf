package main

import "fmt"

func main() {
	var x uint = 150
	var y uint = 100
	p := 3
	n := 4
	fmt.Printf("%d set-> %d = %d\n", x, y, setbits(x, p, n, y))
}

func setbits(x uint, p int, n int, y uint) uint {
	ry := getbits(y, n-1, n)
	ry = ry << (p + 1 - n)
	var m uint = ((1 << n) - 1) << (p + 1 - n)
	return x ^ ((x ^ ry) & m)
}

func getbits(x uint, p int, n int) uint {
	return (x >> (p + 1 - n)) & ^(^uint(0) << n)
}
