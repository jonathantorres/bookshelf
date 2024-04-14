package main

import (
	"fmt"

	"github.com/jonathantorres/gopl/ch2/2-1/tempconv"
)

func main() {
	c := tempconv.Celsius(100.0)
	f := tempconv.Fahrenheit(38.0)
	k := tempconv.Kelvin(22.0)

	fmt.Printf("%s = %s\n", c, tempconv.CToF(c))
	fmt.Printf("%s = %s\n", c, tempconv.CToK(c))
	fmt.Printf("%s = %s\n", f, tempconv.FToC(f))
	fmt.Printf("%s = %s\n", f, tempconv.FToK(f))
	fmt.Printf("%s = %s\n", k, tempconv.KToC(k))
	fmt.Printf("%s = %s\n", k, tempconv.KToF(k))
}
