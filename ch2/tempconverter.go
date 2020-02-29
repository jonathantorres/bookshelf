package main

import (
	"fmt"
	"vamos/go_programming/ch2/tempconv"
)

func main() {
	var c tempconv.Celsius = 40
	var f tempconv.Fahrenheit = 55

	fmt.Println(tempconv.CToF(c))
	fmt.Println(tempconv.FToC(f))
	fmt.Println(tempconv.CToK(c))
	fmt.Println(tempconv.FToK(f))
}
