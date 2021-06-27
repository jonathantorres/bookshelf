package main

import (
	"bufio"
	"fmt"
	"os"
)

const maxLine = 1000

func main() {
	for {
		line, len := getLine(maxLine)
		if len == 0 {
			break
		}
		var lTrails int
		for i := 0; i < len; i++ {
			if rune(line[i]) != ' ' && rune(line[i]) != '\t' {
				break
			}
			lTrails++
		}
		// remove left trailing blanks and tabs
		if lTrails > 0 {
			for i := 0; i < len; i++ {
				line[i] = line[(i + lTrails)]
			}
			len -= lTrails
		}

		var rTrails int
		for i := len - 1; i >= 0; i-- {
			if rune(line[i]) == '\n' {
				continue
			}
			if rune(line[i]) == ' ' || rune(line[i]) == '\t' {
				rTrails++
			} else {
				break
			}
		}

		// remove right trailing blanks and tabs
		if rTrails > 0 {
			len -= rTrails
			line[len-1] = byte('\n')
		}

		allBlanks := true
		for i := 0; i < len; i++ {
			if rune(line[i]) != ' ' && rune(line[i]) != '\t' && rune(line[i]) != '\n' {
				allBlanks = false
			}
		}
		if allBlanks {
			continue
		}
		fmt.Printf("%s\n", string(line))
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
