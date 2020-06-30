package main

// Exercise 4.9

import (
	"fmt"
	"io/ioutil"
	"os"
	"strings"
)

func main() {
	file, err := ioutil.ReadFile("words.txt")
	counts := map[string]int{}
	if err != nil {
		fmt.Fprintf(os.Stderr, "Failure reading file %s\n", err)
		os.Exit(1)
	}
	parts := strings.Split(string(file), " ")
	for _, s := range parts {
		word := strings.Trim(s, ".,?")
		counts[word]++
	}
	fmt.Printf("word\tcount\n")
	for k, v := range counts {
		fmt.Printf("%s\t%d\n", k, v)
	}
}
