package main

import "fmt"

func main() {
	defer func() {
		msg := recover()
		fmt.Println(msg)
	}()
	panic("WHOOPS!")
}
