package main

import "fmt"

type Person struct {
	Name string
}

type Android struct {
	Model string
	Person
}

func (p *Person) talk() {
	fmt.Println("Hi, my name is", p.Name)
}

func main() {
	p := Person{Name: "Jonathan"}
	an := Android{Model: "12323"}
	an.Name = "Barry"
	p.talk()
	an.talk()
}
