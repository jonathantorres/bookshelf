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
		line = detab(line)
		fmt.Printf("%s", string(line))
	}
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
