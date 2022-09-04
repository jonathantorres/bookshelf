package main

import (
	"errors"
	"fmt"
	"math"
	"os"
	"strconv"
	"unicode"
)

const maxVal = 100

var sp int
var val []float64

func main() {
	if len(os.Args) == 1 {
		fmt.Printf("not enough arguments: expr \"numbers operators\"\n")
		os.Exit(1)
	}
	val = make([]float64, maxVal)
	var line []byte
	for i := 1; i < len(os.Args); i++ {
		p := os.Args[i]
		for _, r := range p {
			b := byte(r)
			line = append(line, b)
		}
		line = append(line, byte(' '))
	}
	line = append(line, byte('\n'))
	res, err := calc(line)
	if err != nil {
		fmt.Printf("%s\n", err)
		return
	}
	fmt.Printf("%.8g\n", res)
}

func calc(line []byte) (float64, error) {
	var num []byte
	for i, b := range line {
		c := rune(b)
		var isNegative bool
		if unicode.IsSpace(c) {
			if c != '\n' && len(num) > 0 {
				n, err := strconv.ParseFloat(string(num), 64)
				if err != nil {
					return 0.0, err
				}
				push(n)
				num = nil
			}
			continue
		}
		if c == '-' && i+1 < len(line) && unicode.IsDigit(rune(line[i+1])) {
			isNegative = true
		}
		if unicode.IsDigit(c) || c == '.' || isNegative {
			num = append(num, b)
			continue
		}
		switch c {
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
				return 0.0, errors.New("error: zero divisor")
			}
			break
		case '%':
			op2 := pop()
			if op2 != 0.0 {
				push(math.Mod(pop(), op2))
			}
			break
		default:
			return 0.0, fmt.Errorf("error: unknown command %c", c)
		}
	}
	return pop(), nil
}

func push(f float64) {
	if sp < maxVal {
		val[sp] = f
		sp++
	} else {
		fmt.Printf("error: stack full, can't push %f\n", f)
	}
}

func pop() float64 {
	if sp > 0 {
		sp--
		v := val[sp]
		return v
	}
	fmt.Printf("error: stack empty\n")
	return 0.0
}
