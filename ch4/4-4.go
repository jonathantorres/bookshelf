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
var x float64

func main() {
	var operator bool
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
			operator = true
			push(n)
			break
		case 'x':
			operator = true
			push(x)
			break
		case '+':
			operator = true
			push(pop() + pop())
			break
		case '*':
			operator = true
			push(pop() * pop())
			break
		case '-':
			operator = true
			op2 := pop()
			push(pop() - op2)
			break
		case '/':
			operator = true
			op2 := pop()
			if op2 != 0.0 {
				push(pop() / op2)
			} else {
				fmt.Printf("error: zero divisor\n")
			}
			break
		case '%':
			operator = true
			op2 := pop()
			if op2 != 0.0 {
				push(math.Mod(pop(), op2))
			}
			break
		case 'p':
			operator = false
			peek()
			break
		case 'd':
			operator = false
			dup()
			break
		case 's':
			operator = false
			swap()
			break
		case 'c':
			operator = false
			clear()
			break
		case '\n':
			if operator {
				x = pop()
				fmt.Printf("\t%.8g\n", x)
			}
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

func peek() {
	x := val[sp-1]
	fmt.Printf("%g\n", x)
}

func dup() {
	push(val[sp])
}

func swap() {
	tmp := val[sp-2]
	val[sp-2] = val[sp-1]
	val[sp-1] = tmp
}

func clear() {
	sp = 0
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
