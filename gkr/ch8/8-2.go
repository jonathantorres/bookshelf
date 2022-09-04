package main

import (
	"fmt"
	"io"
	"os"
)

func main() {
	f, err := os.Open("8-2.go")
	if err != nil {
		fmt.Printf("%s\n", err)
		os.Exit(1)
	}
	_, err = io.Copy(os.Stdout, f)
	if err != nil {
		fmt.Printf("%s\n", err)
		os.Exit(1)
	}
	f.Close()
}
