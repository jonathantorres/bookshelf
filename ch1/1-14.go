package main

import (
	"bufio"
	"fmt"
	"os"
)

const max = 50

func main() {
	var leng int
	chars := make([]rune, max)
	freqs := make([]int, max)
	r := bufio.NewReader(os.Stdin)
	for {
		b, err := r.ReadByte()
		if err != nil {
			break
		}
		c := rune(b)
		if c == ' ' {
			continue
		}
		if c == '\n' {
			break
		}

		var inChars bool
		for i := 0; i < leng; i++ {
			if chars[i] == c {
				inChars = true
				freqs[i]++
				break
			}
		}

		if !inChars {
			chars[leng] = c
			freqs[leng] = 1
			leng++
		}
	}

	for i := 0; i < leng; i++ {
		fmt.Printf("%c", chars[i])
		for j := 0; j < freqs[i]; j++ {
			fmt.Printf("-")
		}
		fmt.Printf("\n")
	}
}
