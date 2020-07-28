package main

// Exercise 9.4

import (
	"fmt"
)

func main() {
	nums := []int{1, 2, 3, 4, 5}
	bytwo := make(chan int)
	bythree := make(chan int)
	byfour := make(chan int)
	// printer
	fmt.Print("start: ")
	for _, i := range nums {
		fmt.Printf("%d,", i)
	}
	fmt.Println()

	go timesTwo(nums, bytwo)
	go timesThree(bytwo, bythree)
	go timesFour(bythree, byfour)

	// printer
	fmt.Print("end: ")
	for i := range byfour {
		fmt.Printf("%d,", i)
	}
	fmt.Println()
}

func timesTwo(nums []int, bytwo chan<- int) {
	for _, i := range nums {
		num := i * 2
		bytwo <- num
	}
	close(bytwo)
}

func timesThree(bytwo <-chan int, bythree chan<- int) {
	for i := range bytwo {
		num := i * 3
		bythree <- num
	}
	close(bythree)
}

func timesFour(bythree <-chan int, byfour chan<- int) {
	for i := range bythree {
		num := i * 4
		byfour <- num
	}
	close(byfour)
}
