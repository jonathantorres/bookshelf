package main

import (
	"bufio"
	"fmt"
	"io"
	"math"
	"os"
	"strconv"
	"unicode"
)

const (
	MaxVal  = 100
	BufSize = 100
	MaxOp   = 100
)

var sp, bufp int
var buf []byte
var val []float64

func main() {
	buf = make([]byte, BufSize)
	val = make([]float64, MaxVal)
	s := make([]byte, 0, MaxOp)
	for {
		typ, err := getop(&s)
		if err != nil {
			break
		}
		switch typ {
		case 'n':
			n, err := strconv.ParseFloat(string(s), 64)
			if err != nil {
				fmt.Printf("%s\n", err)
				return
			}
			push(n)
			break
		case '+':
			push(pop() + pop())
			break
		case '*':
			push(pop() * pop())
			break
		case '-':
			op2 := pop()
			push(pop() - op2)
			break
		case '/':
			op2 := pop()
			if op2 != 0.0 {
				push(pop() / op2)
			} else {
				fmt.Printf("error: zero divisor\n")
			}
			break
		case '%':
			op2 := pop()
			if op2 != 0.0 {
				push(math.Mod(pop(), op2))
			}
			break
		case '\n':
			fmt.Printf("\t%.8g\n", pop())
			break
		default:
			fmt.Printf("error: unknown command %s\n", string(s))
		}
	}
}

func getop(s *[]byte) (rune, error) {
	var i int
	var c byte
	var err error
	for {
		c, err = getch()
		if err != nil {
			return 0, err
		}
		if rune(c) != ' ' && rune(c) != '\t' {
			*s = append(*s, c)
			break
		}
	}
	if !unicode.IsDigit(rune(c)) && rune(c) != '.' {
		return rune(c), nil
	}
	if unicode.IsDigit(rune(c)) {
		for {
			c, err = getch()
			if err != nil {
				return 0, err
			}
			if !unicode.IsDigit(rune(c)) {
				break
			}
			i++
			*s = append(*s, c)
		}
	}
	if rune(c) == '.' {
		for {
			c, err = getch()
			if err != nil {
				return 0, err
			}
			if !unicode.IsDigit(rune(c)) {
				break
			}
			i++
			*s = append(*s, c)
		}
	}
	if err != io.EOF {
		ungetch(c)
	}
	return 'n', nil
}

func push(f float64) {
	if sp < MaxVal {
		val[sp] = f
		sp++
	} else {
		fmt.Printf("error: stack full, can't push %f\n", f)
	}
}

func pop() float64 {
	if sp > 0 {
		v := val[sp]
		sp--
		return v
	} else {
		fmt.Printf("error: stack empty\n")
		return 0.0
	}
}

func getch() (byte, error) {
	if bufp > 0 {
		v := buf[bufp]
		bufp--
		return v, nil
	}
	r := bufio.NewReader(os.Stdin)
	return r.ReadByte()
}

func ungetch(c byte) {
	if bufp >= BufSize {
		fmt.Printf("ungetch: too many characters\n")
	} else {
		buf[bufp] = c
		bufp++
	}
}
