package main

import (
	"bytes"
	"fmt"
	"os"
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
	for i, c := len(s)-1, 0; i >= 0; i, c = i-1, c+1 {
		if c > 0 && c%3 == 0 {
			c = 0
			buf.WriteRune(',')
		}
		buf.WriteByte(s[i])
	}
	r := buf.Bytes()
	r = reverse(r)
	return string(r)
}

func reverse(r []byte) []byte {
	for i, j := 0, len(r)-1; i < j; i, j = i+1, j-1 {
		r[i], r[j] = r[j], r[i]
	}
	return r
}
