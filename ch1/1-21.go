package main

import (
	"bufio"
	"bytes"
	"fmt"
	"io"
	"os"
)

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
		line = entab(line)
		fmt.Printf("%s", string(line))
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
