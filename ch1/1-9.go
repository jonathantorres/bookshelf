package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	r := bufio.NewReader(os.Stdin)
	var prev rune
	for {
		b, err := r.ReadByte()
		if err != nil {
			break
		}
		if !(rune(b) == ' ' && prev == ' ') {
			fmt.Printf("%c", rune(b))
		}
		prev = rune(b)
	}
}
