package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	fileLines := make(map[string][]string)
	counts := make(map[string]int)
	files := os.Args[1:]
	if len(files) == 0 {
		countLines(os.Stdin, counts, fileLines)
	} else {
		for _, arg := range files {
			f, err := os.Open(arg)
			if err != nil {
				fmt.Fprintf(os.Stderr, "dup2: %v\n", err)
				continue
			}
			countLines(f, counts, fileLines)
			f.Close()
		}
	}
	for line, n := range counts {
		if n > 1 {
			fmt.Printf("%d\t%s (%s)\n", n, line, strings.Join(fileLines[line], ","))
		}
	}
}

func countLines(f *os.File, counts map[string]int, fileLines map[string][]string) {
	input := bufio.NewScanner(f)
	for input.Scan() {
		curLine := input.Text()
		counts[curLine]++
		if fileLines[curLine] == nil {
			fileLines[curLine] = make([]string, 0, 10)
		}
		var exists bool
		for _, n := range fileLines[curLine] {
			if n == f.Name() {
				exists = true
			}
		}
		if !exists {
			fileLines[curLine] = append(fileLines[curLine], f.Name())
		}
	}
	err := input.Err()
	if err != nil {
		fmt.Fprintf(os.Stderr, "dup2: %v\n", err)
	}
}
