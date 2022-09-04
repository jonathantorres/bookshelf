package main

import (
	"fmt"
	"math"
)

type Circle struct {
	x float64
	y float64
	r float64
}

func circleArea(c *Circle) float64 {
	return math.Pi * c.r * c.r
}

func main() {
	c := Circle{x: 10, y: 15, r: 12}
	fmt.Println(circleArea(&c))
}
