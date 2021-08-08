package main

import (
	"bufio"
	"fmt"
	"os"
)

const (
	MaxLine  = 1000
	PageRows = 50
)

func main() {
	var pages, rows int
	if len(os.Args) == 1 {
		fmt.Printf("Not enough arguments!\n")
		os.Exit(1)
	}
	for i, n := range os.Args {
		if i == 0 {
			continue
		}
		f, err := os.Open(n)
		if err != nil {
			fmt.Printf("%s\n", err)
			os.Exit(1)
		}
		pages = count_pages(f)
		fmt.Printf("File: %s, %d", n, pages)
		if pages > 1 {
			fmt.Printf(" pages")
		} else {
			fmt.Printf(" page")
		}
		fmt.Println()
		rows = 0
		s := bufio.NewScanner(f)
		for s.Scan() {
			line := s.Text()
			rows++
			fmt.Printf("%s", line)
		}
		if err := s.Err(); err != nil {
			fmt.Printf("%s\n", err)
			os.Exit(1)
		}
		for i := rows % PageRows; i <= PageRows; i++ {
			fmt.Println()
		}
		f.Close()
	}
}

func count_pages(f *os.File) int {
	var rows int
	s := bufio.NewScanner(f)
	for s.Scan() {
		rows++
	}
	if err := s.Err(); err != nil {
		fmt.Printf("%s\n", err)
		os.Exit(1)
	}
	return int(rows/PageRows + 1)
}
