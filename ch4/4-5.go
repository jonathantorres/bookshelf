package main

import (
	"bufio"
	"errors"
	"fmt"
	"io"
	"math"
	"os"
	"strconv"
	"strings"
	"unicode"
)

const maxVal = 100

var sp int
var val []float64

func main() {
	val = make([]float64, maxVal)
	r := bufio.NewReader(os.Stdin)
	for {
		line, err := r.ReadBytes('\n')
		if err != nil {
			if err == io.EOF {
				break
			}
			fmt.Printf("%s\n", err)
			continue
		}
		if out := mathFunc(line); out != "" {
			fmt.Printf("%s\n", out)
			continue
		}
		res, err := calc(line)
		if err != nil {
			fmt.Printf("%s\n", err)
			continue
		}
		fmt.Printf("\t%.8g\n", res)
	}
}

func mathFunc(line []byte) string {
	cmd := strings.TrimSpace(string(line))
	switch cmd {
	case "sin":
		return fmt.Sprintf("\t%.8g", math.Sin(pop()))
	case "cos":
		return fmt.Sprintf("\t%.8g", math.Cos(pop()))
	case "exp":
		return fmt.Sprintf("\t%.8g", math.Exp(pop()))
	case "pow":
		op2 := pop()
		return fmt.Sprintf("\t%.8g", math.Pow(pop(), op2))
	}
	return ""
}

func calc(line []byte) (float64, error) {
	var num []byte
	for i, b := range line {
		c := rune(b)
		var isNegative bool
		if unicode.IsSpace(c) {
			if len(num) > 0 {
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
