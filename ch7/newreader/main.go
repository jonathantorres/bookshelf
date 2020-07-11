package main

// Exercise 7.4

import (
	"fmt"
	"io"
	"os"
)

type MyReader struct {
	s string
	b int
}

func (r *MyReader) Read(p []byte) (int, error) {
	read := copy(p, r.s)
	r.b = read
	r.s = r.s[read:]
	return r.b, nil
}

func main() {
	myReader := newReader("hola")
	data := make([]byte, 100)
	l, err := myReader.Read(data);
	if err != nil {
		fmt.Fprintf(os.Stderr, "error reading data\n")
		os.Exit(1)
	}
	fmt.Printf("read %d bytes: %s\n", l, string(data))
}

func newReader(s string) io.Reader {
	return &MyReader{
		s: s,
		b: 0,
	}
}
