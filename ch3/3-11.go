package main

import (
	"bytes"
	"fmt"
	"os"
	"strings"
)

func main() {
	for i := 1; i < len(os.Args); i++ {
		fmt.Printf("%s\n", comma(os.Args[i]))
	}
}

func comma(s string) string {
	n := len(s)
	if n <= 3 {
		return s
	}
	var buf bytes.Buffer
	var decs string
	var sign rune
	if strings.HasPrefix(s, "+") {
		sign = '+'
	} else if strings.HasPrefix(s, "-") {
		sign = '-'
	}
	if sign == '-' || sign == '+' {
		s = s[1:]
	}
	if li := strings.LastIndex(s, "."); li != -1 {
		decs, s = s[li:], s[:li]
	}
	for i, c := len(s)-1, 0; i >= 0; i, c = i-1, c+1 {
		if c > 0 && c%3 == 0 {
			c = 0
			buf.WriteRune(',')
		}
		buf.WriteByte(s[i])
	}
	r := buf.String()
	r = reverse(r)

	if sign == '-' || sign == '+' {
		r = string(sign) + r
	}
	if decs != "" {
		r = r + decs
	}
	return r
}

func reverse(s string) string {
	r := []byte(s)
	for i, j := 0, len(r)-1; i < j; i, j = i+1, j-1 {
		r[i], r[j] = r[j], r[i]
	}
	return string(r)
}
