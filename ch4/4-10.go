package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"strconv"
	"unicode"
)

const (
	MaxVal  = 100
	BufSize = 100
	MaxOp   = 100
	MaxLine = 1000
)

var sp, bufp int
var buf []byte
var val []float64
var x float64

func main() {
	var operator bool
	var v rune
	buf = make([]byte, BufSize)
	val = make([]float64, MaxVal)
	s := make([]byte, 0, MaxOp)
	vars := make([]float64, MaxVal)

	for i := 0; i < 26; i++ {
		vars[i] = 0.0
	}

	for {
		line, l := getLine(MaxLine)
		if l <= 0 {
			break
		}
	GetOp:
		for {
			typ, err := getop(&s, line)
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
			case 'm':
				operator = true
				mathfunc(s)
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
					break GetOp
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
			case '=':
				pop()
				if v >= 'A' && v <= 'Z' {
					vars[v-'A'] = pop()
				} else {
					fmt.Printf("error: no variable name\n")
					break GetOp
				}
				break
			case '\n':
				if operator {
					x = pop()
					fmt.Printf("\t%.8g\n", x)
				}
				break
			default:
				if typ >= 'A' && typ <= 'Z' {
					push(vars[typ-'A'])
				} else if typ == 'v' {
					push(x)
				} else {
					fmt.Printf("error: unknown command %s\n", string(s))
					break GetOp
				}
			}
			v = typ
		}
	}
}

var j int

func getop(s *[]byte, line []byte) (rune, error) {
	var i int
	var c byte
	if rune(line[j]) == '\n' {
		j++
		return '\n', nil
	}
	for {
		if j >= len(line)-1 {
			break
		}
		c = line[j]
		j++
		if rune(c) != ' ' && rune(c) != '\t' {
			*s = append(*s, c)
			break
		}
	}
	if unicode.IsLower(rune(c)) {
		for {
			c = line[j]
			j++
			i++
			*s = append(*s, c)
			if !unicode.IsLower(rune(c)) {
				break
			}
			if len(string(*s)) > 1 {
				return 'm', nil
			}
			return rune(c), nil
		}
	}
	if c == (*s)[len(*s)-1] {
		j = 0
		return rune(c), nil
	}
	if !unicode.IsDigit(rune(c)) && rune(c) != '.' {
		return rune(c), nil
	}
	if unicode.IsDigit(rune(c)) {
		for {
			c = line[j]
			j++
			i++
			*s = append(*s, c)
			if !unicode.IsDigit(rune(c)) {
				break
			}
		}
	}
	if rune(c) == '.' {
		for {
			c = line[j]
			j++
			i++
			*s = append(*s, c)
			if !unicode.IsDigit(rune(c)) {
				break
			}
		}
	}
	return 'n', nil
}

func mathfunc(s []byte) {
	var op2 float64
	if string(s) == "sin" {
		push(math.Sin(pop()))
	} else if string(s) == "cos" {
		push(math.Cos(pop()))
	} else if string(s) == "exp" {
		push(math.Exp(pop()))
	} else if string(s) == "pow" {
		op2 = pop()
		push(math.Pow(pop(), op2))
	} else {
		fmt.Printf("error: %s is not supported\n", string(s))
	}
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
