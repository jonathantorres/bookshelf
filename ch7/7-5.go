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

var bufp int
var buf []byte
var val []float64
var sp int

func main() {
	var typ rune
	var err error
	var op2 float64
	s := make([]byte, 1, MaxOp)
	for {
		typ, err = getop(&s)
		if err != nil {
			return
		}
		switch typ {
		case '1':
			f, err := strconv.ParseFloat(string(s), 64)
			if err != nil {
				fmt.Printf("%s\n", err)
				return
			}
			push(f)
			break
		case '+':
			push(pop() + pop())
			break
		case '*':
			push(pop() * pop())
			break
		case '-':
			op2 = pop()
			push(pop() - op2)
			break
		case '/':
			op2 = pop()
			if op2 != 0.0 {
				push(pop() / op2)
			} else {
				fmt.Printf("error: zero divisor\n")
			}
			break
		case '%':
			op2 = pop()
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
	var c rune
	var err error
	var f float64
	for {
		_, err = fmt.Scanf("%c", &c)
		if err != nil {
			return 0, err
		}
		(*s)[0] = byte(c)
		if rune((*s)[0]) == ' ' || rune((*s)[0]) == '\t' {
			break
		}
	}
	if err != nil && err == io.EOF {
		return 0, err
	} else if !unicode.IsDigit(c) && c != '.' {
		return c, nil
	}
	_, err = fmt.Scanf("%f", &f)
	if err != nil {
		return 0, err
	}
	str := fmt.Sprintf("%f", f)
	for _, ss := range str {
		*s = append(*s, byte(ss))
	}
	return '1', nil
}

func push(f float64) {
	if sp < MaxVal {
		sp++
		val[sp] = f
	} else {
		fmt.Printf("error: stack full, can't push %g\n", f)
	}
}

func pop() float64 {
	if sp > 0 {
		sp--
		return val[sp]
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
