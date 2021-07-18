package main

import (
	"bufio"
	"fmt"
	"io"
	"math"
	"os"
	"unicode"
)

const (
	MaxLen   = 1000
	BuffSize = 100
)

var buf []byte
var bufp int

func main() {
	buf = make([]byte, BuffSize)
	var f float64
	var r int
	r = getfloat(&f)
	if r > 0 {
		fmt.Printf("%f\n", f)
	} else if r == 0 {
		fmt.Printf("not a number\n")
	} else if r == -1 {
		fmt.Printf("end of file\n")
	} else {
		fmt.Printf("unknown error\n")
	}
}

func getfloat(n *float64) int {
	var power float64
	var c byte
	var sign, exp, esign, bige int
	var err error
	for {
		c, err = getch()
		if err != nil {
			return -1
		}
		if !unicode.IsSpace(rune(c)) {
			break
		}
	}
	if !unicode.IsDigit(rune(c)) && rune(c) != '+' && rune(c) != '-' && err != io.EOF {
		ungetch(c)
		return 0
	}
	if rune(c) == '-' {
		sign = -1
	} else {
		sign = 1
	}
	if rune(c) == '+' || rune(c) == '-' {
		c, err = getch()
		if err != nil {
			return 0
		}
		if !unicode.IsDigit(rune(c)) {
			ungetch(c)
			if sign == 1 {
				ungetch(byte('+'))
			} else {
				ungetch(byte('-'))
			}
			return 0
		}
	}
	for *n = 0; unicode.IsDigit(rune(c)); c, err = getch() {
		*n = 10*(*n) + float64(rune(c)-'0')
	}
	if rune(c) == '.' {
		r := bufio.NewReader(os.Stdin)
		c, err = r.ReadByte()
		if err != nil {
			return 0
		}
	}
	for power = 1.0; unicode.IsDigit(rune(c)); c, err = getch() {
		*n = 10.0*(*n) + float64(rune(c)-'0')
		power *= 10.0
	}
	if rune(c) == 'E' {
		bige = 1
	}
	if rune(c) == 'e' || rune(c) == 'E' {
		c, err = getch()
		if err != nil {
			return 0
		}
		if rune(c) == '-' {
			esign = -1
		} else {
			esign = 1
		}
		if rune(c) == '+' || rune(c) == '-' {
			c, err = getch()
			if err != nil {
				return 0
			}
			if !unicode.IsDigit(rune(c)) {
				ungetch(c)
				if sign == 1 {
					ungetch(byte('+'))
				} else {
					ungetch(byte('-'))
				}
			}
		} else if !unicode.IsDigit(rune(c)) {
			ungetch(c)
			if bige == 0 {
				ungetch(byte('e'))
			} else {
				ungetch(byte('E'))
			}
		}
		for exp = 0; unicode.IsDigit(rune(c)); c, err = getch() {
			exp = 10*exp + int(rune(c)-'0')
		}
		*n *= (float64(sign) / power) * math.Pow(float64(10), float64(esign*exp))
	} else {
		*n *= (float64(sign) / power)
	}
	if err != io.EOF {
		ungetch(c)
	}
	return int(c)
}

func getch() (byte, error) {
	if bufp > 0 {
		bufp--
		v := buf[bufp]
		return v, nil
	}
	r := bufio.NewReader(os.Stdin)
	return r.ReadByte()
}

func ungetch(c byte) {
	if bufp >= BuffSize {
		fmt.Printf("ungetch: too many characters\n")
	} else {
		buf[bufp] = c
		bufp++
	}
}
