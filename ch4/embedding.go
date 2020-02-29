package main

import (
	"fmt"
)

type Point struct {
	X int
	Y int
}

type Circle struct {
	Point
	Radius int
}

type Wheel struct {
	Circle
	Spokes int
}

var w Wheel

func main() {
	w.X = 8
	w.Y = 8
	w.Radius = 5
	w.Spokes = 20
	fmt.Println(w)

	dunlop := Wheel{
		Circle: Circle{
			Point: Point{
				X: 10,
				Y: 10,
			},
			Radius: 10,
		},
		Spokes: 40,
	}
	fmt.Println(dunlop)
}
