package main

import (
	"fmt"
)

type Human struct {
	firstName string
	lastName  string
	age       int
}

var me = Human{
	firstName: "Jonathan",
	lastName:  "Torres",
	age:       33,
}

func main() {
	fmt.Println("aiiight")
	fmt.Println(me)

	anotherHuman := Human{}
	fmt.Println(anotherHuman)
}
