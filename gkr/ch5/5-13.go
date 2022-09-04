package main

import (
	"bufio"
	"flag"
	"fmt"
	"io"
	"os"
)

func main() {
	var n = flag.Int("n", 10, "number of lines to print")
	flag.Parse()
	var inputLines [][]byte
	r := bufio.NewReader(os.Stdin)
	for {
		line, err := r.ReadBytes(byte('\n'))
		if err != nil {
			if err != io.EOF {
				fmt.Printf("error: %s\n", err)
			}
			break
		}
		inputLines = append(inputLines, line)
	}
	printLines(inputLines, *n)
}

func printLines(lines [][]byte, n int) {
	var linesToPrint [][]byte
	if len(lines) <= n {
		// print everything
		linesToPrint = lines
	} else {
		linesToPrint = lines[len(lines)-n:]
	}
	for _, l := range linesToPrint {
		fmt.Printf("%s", string(l))
	}
}
