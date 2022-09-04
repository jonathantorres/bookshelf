package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	r := bufio.NewReader(os.Stdin)
	var idx int
	var curLen int
	wordLens := make([]int, 50)
	for {
		b, err := r.ReadByte()
		if err != nil {
			break
		}
		c := rune(b)
		if c == ' ' {
			wordLens[idx] = curLen
			curLen = 0
			idx++
		} else {
			curLen++
		}

		if c == '\n' {
			wordLens[idx] = curLen - 1
			curLen = 0
			idx++
			for i := 0; i < idx; i++ {
				for j := 0; j < wordLens[i]; j++ {
					fmt.Printf("-")
				}
				fmt.Printf("\n")
			}
			idx = 0
		}
	}
}
