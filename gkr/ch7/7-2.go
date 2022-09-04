package main

import (
	"bufio"
	"fmt"
	"os"
)

const (
	linelen = 10
	octLen  = 3
)

func main() {
	r := bufio.NewReader(os.Stdin)
	for {
		b, err := r.ReadByte()
		if err != nil {
			break
		}
		var cnum int
		if int(b) < 32 {
			cnum = printoct(int(b), cnum)
		} else {
			cnum = printnor(int(b), cnum)
		}
		if cnum >= linelen {
			cnum = cnum - linelen
		}
	}
}

func printoct(c, n int) int {
	var l int
	l = n + octLen
	if l <= linelen {
		fmt.Printf("%o", c)
	} else {
		fmt.Printf("\n%o", c)
	}
	return l
}

func printnor(c, n int) int {
	var l int
	l = n + 1
	if l <= linelen {
		fmt.Printf("%c", c)
	} else {
		fmt.Printf("\n%c", c)
	}
	return l
}
