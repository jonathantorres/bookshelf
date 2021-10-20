package main

import (
	"bufio"
	"bytes"
	"fmt"
	"io"
	"os"
)

const maxLine = 1000

func main() {
	r := bufio.NewReader(os.Stdin)

	for {
		line, err := r.ReadBytes(byte('\n'))
		if err != nil {
			if err != io.EOF {
				fmt.Printf("error: %s\n", err)
			}
			break
		}
		l := len(line)
		if l == 0 {
			break
		}
		line2 := escape(line)
		line3 := rEscape(line2)
		fmt.Printf("%s\n", string(line2))
		fmt.Printf("%s\n", string(line3))
	}
}

func escape(line []byte) []byte {
	var buf bytes.Buffer
	for _, b := range line {
		switch rune(b) {
		case '\n':
			buf.WriteByte(byte('\\'))
			buf.WriteByte(byte('n'))
			break
		case '\t':
			buf.WriteByte(byte('\\'))
			buf.WriteByte(byte('t'))
			break
		default:
			buf.WriteByte(b)
			break
		}
	}
	return buf.Bytes()
}

func rEscape(line []byte) []byte {
	var buf bytes.Buffer
	var esc bool
	for i, b := range line {
		switch rune(b) {
		case '\\':
			if line[i+1] == 't' {
				buf.WriteByte(byte('\t'))
				esc = true
			} else if line[i+1] == 'n' {
				buf.WriteByte(byte('\n'))
				esc = true
			}
			break
		default:
			if !esc {
				buf.WriteByte(b)
			}
			esc = false
			break
		}
	}
	return buf.Bytes()
}
