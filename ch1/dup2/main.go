package main

// Excercise 1.4

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

type LineInfo struct {
	count int
	files []string
}

func main() {
	counts := make(map[string]LineInfo)
	files := os.Args[1:]
	if len(files) == 0 {
		countLines(os.Stdin, counts, "stdin")
	} else {
		for _, arg := range files {
			f, err := os.Open(arg)
			if err != nil {
				fmt.Fprintf(os.Stderr, "dup2: %v\n", err)
				continue
			}
			countLines(f, counts, arg)
			f.Close()
		}
	}
	for line, fInfo := range counts {
		if fInfo.count > 1 {
			fmt.Printf("%s -> %s (%d times)\n", strings.Join(fInfo.files, ","), line, fInfo.count)
		}
	}
}

func countLines(f *os.File, counts map[string]LineInfo, filename string) {
	input := bufio.NewScanner(f)
	for input.Scan() {
		lineKey := input.Text()
		if info, ok := counts[lineKey]; ok {
			info.count++
			info.files = append(info.files, filename)
			counts[lineKey] = info
		} else {
			counts[lineKey] = LineInfo{
				count: 1,
				files: []string{filename},
			}
		}
	}
}
