package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
)

const maxLine = 1000

func main() {
	r := bufio.NewReader(os.Stdin)
	for {
		line, err := r.ReadBytes(byte('\n'))
		if err != nil {
			if err != io.EOF {
				fmt.Printf("error: %s\n", err)
			}
			break
		}
		var ignore bool
		l := len(line)
		for i := 0; i < l; i++ {
			if rune(line[i]) == '/' && i+1 < l && rune(line[i+1]) == '/' {
				ignore = true
			}
			if !ignore {
				fmt.Printf("%c", rune(line[i]))
			}
		}
		if ignore {
			fmt.Printf("\n")
		}
	}
}
