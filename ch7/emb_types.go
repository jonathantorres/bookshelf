package main

import (
	"fmt"
)

// this is just a Person type
type Person struct {
	Name string
}

// this Person type has a Talk() method
func (p *Person) Talk() string {
	return "hi!, my name is " + p.Name
}

// Now, this is an Android type
// using embedded types like this
// an Android has all the fields and methods
// from the Person as well (kinda like inheritance right?)
type Android struct {
	Person // embedded type!
	Model  string
}

func main() {
	p := Person{}
	p.Name = "Jonathan"

	a := Android{}
	a.Model = "T1000"
	a.Name = "Bishop"

	fmt.Println(p.Talk())
	fmt.Println(a.Talk())
}
