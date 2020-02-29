package main

import "fmt"

func main() {
	var my_name string = "Jonathan Torres"
	fmt.Println("Hello, my name is " + my_name)

	// assigning variables
	var x string
	x = "first"
	fmt.Println(x)
	x = "second"
	fmt.Println(x)

	// concatenate strings
	var y string = "foo"
	var z string = "bar"
	y += z
	fmt.Println(y)

	// equality comparison
	var hi string = "hello"
	var world string = "world"
	fmt.Println(hi == world)

	// create the variable and infer the type
	yes := "yes"
	fmt.Println(yes)

	// creating multiple variables
	var (
		a = 1
		b = 2
		c = 3
	)
	fmt.Println(a)
	fmt.Println(b)
	fmt.Println(c)
}
