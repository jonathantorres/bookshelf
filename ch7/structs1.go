package main

import (
	"fmt"
)

// Creating the "Circle" type or struct
type Circle struct {
	x float64
	y float64
	r float64
}

// creating the area() method
// on the Circle type
// if we want to change the values of any fields
// we must pass a Circle pointer
func (c *Circle) area() float64 {
	return c.x * c.y * c.y
}

func main() {
	// creating an instance of Circle
	c := Circle{x: 5, y: 3, r: 1}

	// accesing fields or properties
	c.x = 10

	// calling the area() method on the circle
	c.area()

	fmt.Println(c.area())
	fmt.Println(c)
	fmt.Println(c.x, c.y, c.r)
}
