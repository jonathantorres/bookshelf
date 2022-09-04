package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
)

const (
	maxLine   = 1000
	lineLimit = 10
)

func main() {
	for {
		line, l := getLine(maxLine)
		if l > lineLimit {
			split := int(math.Ceil(float64(l / lineLimit)))
			charS := 0
			charE := lineLimit - 1
			for i := 1; i <= split; i++ {
				for j := charS; j <= charE; j++ {
					fmt.Printf("%c", rune(line[j]))
				}
				if i == split-1 {
					charE += (l - charE) - 1
				} else {
					charE += lineLimit
				}
				charS += lineLimit
				fmt.Printf("\n")
			}
		} else {
			fmt.Printf("%s", line)
		}
	}
}

func getLine(lim int) ([]byte, int) {
	var c byte
	var i int
	s := make([]byte, lim)
	r := bufio.NewReader(os.Stdin)
	for i = 0; i < lim-1; i++ {
		c, err := r.ReadByte()
		if rune(c) == '\n' || err != nil {
			break
		}
		s[i] = c
	}
	if rune(c) == '\n' {
		s[i] = c
		i++
	}
	return s, i
}
