package main

import (
	"bufio"
	"fmt"
	"os"
)

const MaxLine = 100

func main() {
	if len(os.Args) != 3 {
		fmt.Printf("error: the program takes 2 arguments\n")
		os.Exit(1)
	}
	f1, err := os.Open(os.Args[1])
	if err != nil {
		fmt.Printf("%s\n", err)
		os.Exit(1)
	}
	f2, err := os.Open(os.Args[1])
	if err != nil {
		fmt.Printf("%s\n", err)
		os.Exit(1)
	}
	defer func() {
		var err error
		err = f1.Close()
		if err != nil {
			fmt.Printf("%s\n", err)
			os.Exit(1)
		}
		err = f2.Close()
		if err != nil {
			fmt.Printf("%s\n", err)
			os.Exit(1)
		}
	}()
	s1 := bufio.NewScanner(f1)
	s2 := bufio.NewScanner(f2)
	for s1.Scan() && s2.Scan() {
		l1 := s1.Text()
		l2 := s2.Text()
		if l1 == l2 {
			fmt.Printf("%s\n", l1)
			fmt.Printf("%s\n", l2)
			return
		}
	}
	if err = s1.Err(); err != nil {
		fmt.Printf("%s\n", err)
		os.Exit(1)
	}
	if err = s2.Err(); err != nil {
		fmt.Printf("%s\n", err)
		os.Exit(1)
	}
	fmt.Printf("Identical lines\n")
}
