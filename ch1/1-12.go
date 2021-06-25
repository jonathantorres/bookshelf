package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	r := bufio.NewReader(os.Stdin)
	for {
		b, err := r.ReadByte()
		if err != nil {
			break
		}
		if rune(b) == ' ' {
			fmt.Printf("\n")
		} else {
			fmt.Printf("%c", rune(b))
		}
	}
}
