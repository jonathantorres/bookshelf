package main

// Exercise 1.3

import (
	"fmt"
	"os"
	"strings"
	"time"
)

func main() {
	iterStart := time.Now()
	runIterVersion()
	iterEnd := time.Now()
	iterDur := iterEnd.Sub(iterStart)

	joinStart := time.Now()
	runJoinVersion()
	joinEnd := time.Now()
	joinDur := joinEnd.Sub(joinStart)
	fmt.Println("loop version duration:", iterDur)
	fmt.Println("join version duration:", joinDur)
}

func runJoinVersion() {
	fmt.Println(strings.Join(os.Args[:], " "))
}

func runIterVersion() {
	var s, sep string
	for i := 0; i < len(os.Args); i++ {
		s += sep + os.Args[i]
		sep = " "
	}
	fmt.Println(s)
}
