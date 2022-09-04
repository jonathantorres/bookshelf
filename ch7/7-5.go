package main

import (
	"fmt"
	"io"
	"os"
	"strings"
)

func main() {
	sr := strings.NewReader("Hi, this is a message")
	r := LimitReader(sr, 5)
	b := make([]byte, 10)
	n, err := r.Read(b)
	if err != nil && err != io.EOF {
		fmt.Fprintf(os.Stderr, "%s\n", err)
		os.Exit(1)
	}
	fmt.Printf("%s\n", string(b))
	fmt.Printf("bytes read: %d\n", n)
}

type LimitedReader struct {
	r io.Reader
	n int64
}

func (r *LimitedReader) Read(p []byte) (n int, err error) {
	if len(p) == 0 {
		return
	}
	if r.n <= 0 {
		err = io.EOF
	}
	end := int(r.n)
	if len(p) < end {
		end = len(p)
	}
	n, err = r.r.Read(p[:end])
	r.n -= int64(n)
	return
}

func LimitReader(r io.Reader, n int64) io.Reader {
	return &LimitedReader{
		r: r,
		n: n,
	}
}
