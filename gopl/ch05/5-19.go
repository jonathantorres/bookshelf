package main

import "fmt"

func main() {
	fmt.Println(f())
}

func f() (n interface{}) {
	defer func() {
		if r := recover(); r != nil {
			n = r
		}
	}()
	panic(1)
}
