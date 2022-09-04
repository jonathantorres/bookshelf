package main

import (
	"fmt"
	"unicode"
)

func main() {
	msg := "50e-2"
	fmt.Printf("%f\n", atof(msg))
}

func atof(s string) float64 {
	var val, power float64
	var i, sign, e int

	for i = 0; unicode.IsSpace(rune(s[i])); i++ {
		// skip whitespace
	}
	if s[i] == '-' {
		sign = -1
	} else {
		sign = 1
	}
	for val = 0.0; unicode.IsDigit(rune(s[i])); i++ {
		val = 10.0*val + float64(int(s[i]-'0'))
	}
	if s[i] == '.' {
		i++
	}
	for power = 1.0; unicode.IsDigit(rune(s[i])); i++ {
		val = 10.0*val + float64(int(s[i]-'0'))
		power *= 10.0
	}
	if s[i] == 'e' || s[i] == 'E' {
		i++
		if s[i] == '-' {
			sign = -1
		} else {
			sign = 1
		}
		if s[i] == '+' || s[i] == '-' {
			i++
		}
		for e = 0; i < len(s) && unicode.IsDigit(rune(s[i])); i++ {
			e = e*10 + int(s[i]-'0')
		}
		if sign == 1 {
			for i = 0; i <= e; i++ {
				power *= 10
			}
		} else {
			for i = 0; i <= e; i++ {
				power /= 10
			}
		}
	}
	return float64(float64(sign) * val / power)
}
