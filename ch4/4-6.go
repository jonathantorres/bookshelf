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

var vars map[rune]float64
var latest float64
var sp int
var val []float64

func main() {
	val = make([]float64, maxVal)
	vars = make(map[rune]float64)
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
		if saveVars(line) {
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

func saveVars(line []byte) bool {
	var found bool
	s := strings.TrimSpace(string(line))
	if !strings.Contains(s, "=") {
		return found
	}
	// a=1, a=1 b=2
	splits := strings.Split(s, " ")
	if len(splits) == 0 {
		return found
	}
	found = true
	for _, v := range splits {
		va := strings.Split(v, "=")
		if len(va) < 2 {
			continue
		}
		let := va[0][0]
		num := va[1]
		if !unicode.IsLetter(rune(let)) {
			continue
		}
		val, err := strconv.ParseFloat(num, 64)
		if err != nil {
			continue
		}
		vars[rune(let)] = val
	}
	return found
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
		case 'x':
			push(latest)
			break
		default:
			if unicode.IsLetter(c) && isVar(c) {
				push(vars[c])
			} else {
				return 0.0, fmt.Errorf("error: unknown command %c", c)
			}
		}
	}
	latest = pop()
	return latest, nil
}

func isVar(c rune) bool {
	if _, ok := vars[c]; !ok {
		return false
	}
	return true
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
