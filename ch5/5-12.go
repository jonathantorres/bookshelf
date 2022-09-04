package main

import (
	"bufio"
	"bytes"
	"fmt"
	"io"
	"os"
)

const tabLen = 4

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
		entabbed := entab(line)
		detabbed := detab(line)
		fmt.Printf("%s", entabbed)
		fmt.Printf("%s", detabbed)
		fmt.Println()
	}
}

func entab(s []byte) []byte {
	var tab bool
	var res bytes.Buffer
	for i, b := range s {
		if rune(s[i]) == ' ' && rune(s[i+1]) == ' ' && rune(s[i+2]) == ' ' && rune(s[i+3]) == ' ' {
			res.WriteByte(byte('\t'))
			tab = true
		} else if rune(b) == ' ' {
			if !tab {
				res.WriteByte(byte(' '))
			}
		} else {
			tab = false
			res.WriteByte(b)
		}
	}
	return res.Bytes()
}

func detab(s []byte) []byte {
	var res bytes.Buffer
	for _, b := range s {
		if rune(b) == '\t' {
			for k := 0; k < tabLen; k++ {
				res.WriteByte(byte(' '))
			}
		} else {
			res.WriteByte(b)
		}
	}
	return res.Bytes()
}
