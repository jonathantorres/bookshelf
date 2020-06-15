package main

import "fmt"

type Vehicle struct {
	model string
	year  int
}

func (v *Vehicle) start() {
	fmt.Println("Vehicle starts!")
}

type Compact struct {
	brand string
	Vehicle
}

func (c *Compact) start() {
	c.Vehicle.start()
	fmt.Println("Compact starts!")
}

func main() {
	b := Compact{}
	b.brand = "Nissan"
	b.model = "Altima"
	b.year = 2005
	b.start()
}
