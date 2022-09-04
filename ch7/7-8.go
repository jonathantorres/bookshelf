package main

import (
	"bufio"
	"fmt"
	"os"
)

const pageRows = 25

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
		pages = countPages(f)
		fmt.Printf("File: %s, %d", n, pages)
		if pages > 1 {
			fmt.Printf(" pages")
		} else {
			fmt.Printf(" page")
		}
		fmt.Println()
		rows = 0
		_, err = f.Seek(0, 0)
		if err != nil {
			fmt.Printf("%s\n", err)
			os.Exit(1)
		}
		s := bufio.NewScanner(f)
		for s.Scan() {
			line := s.Text()
			rows++
			fmt.Printf("%s\n", line)
		}
		if err := s.Err(); err != nil {
			fmt.Printf("%s\n", err)
			os.Exit(1)
		}
		for i := rows % pageRows; i <= pageRows; i++ {
			fmt.Println()
		}
		f.Close()
	}
}

func countPages(f *os.File) int {
	var rows int
	s := bufio.NewScanner(f)
	for s.Scan() {
		rows++
	}
	if err := s.Err(); err != nil {
		fmt.Printf("%s\n", err)
		os.Exit(1)
	}
	return int(rows/pageRows + 1)
}
