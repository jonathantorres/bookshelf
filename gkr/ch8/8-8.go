package main

import "fmt"

func main() {
	mem := make([]byte, 100)
	copy(mem, []byte("Jonathan Torres"))
	fmt.Printf("%s\n", string(mem))
}
