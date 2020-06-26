package main

// Exercise 3.10
// Exercise 3.11

import (
	"bytes"
	"fmt"
	"strings"
)

func main() {
	fmt.Println(comma("123"))
	fmt.Println(comma("123456"))
	fmt.Println(comma("1234567"))
	fmt.Println()
	fmt.Println(commabuf("123"))
	fmt.Println(commabuf("123456"))
	fmt.Println(commabuf("1234567"))
	fmt.Println()
	fmt.Println(commaflo("123.00"))
	fmt.Println(commaflo("123456.00"))
	fmt.Println(commaflo("1234567.00"))
	fmt.Println(commaflo("-123456789.57"))
}

func commabuf(s string) string {
	n := len(s)
	if n <= 3 {
		return s
	}
	var buf bytes.Buffer
	for i, j := len(s)-1, 0; i >= 0; i-- {
		buf.WriteByte(byte(s[i]))
		j++
		if j%3 == 0 && i != 0 {
			buf.WriteByte(byte(','))
		}
	}
	var sli = buf.Bytes()
	for i, j := 0, len(sli)-1; i < j; i, j = i+1, j-1 {
		sli[i], sli[j] = sli[j], sli[i]
	}
	return string(sli)
}

func commaflo(s string) string {
	n := len(s)
	if n <= 3 {
		return s
	}
	var sign string
	if strings.HasPrefix(s, "-") || strings.HasPrefix(s, "+") {
		sign = string(s[0])
		s = s[1:]
	}
	var dotStr string
	if doti := strings.LastIndex(s, "."); doti != -1 {
		dotStr = s[doti:]
		s = comma(s[:doti]) + dotStr
		return sign + s
	}
	return sign + comma(s)
}

func comma(s string) string {
	n := len(s)
	if n <= 3 {
		return s
	}
	return comma(s[:n-3]) + "," + s[n-3:]
}
