package main

// Exercise 7.5

import (
	"fmt"
	"io"
	"os"
	"strings"
)

type LimReader struct {
	r io.Reader
	n int
}

func (lr *LimReader) Read(p []byte) (int, error) {
	read, err := lr.r.Read(p[:lr.n])
	if err != nil {
		return 0, err
	}
	if read >= lr.n {
		return lr.n, io.EOF
	}
	return lr.n, nil
}

func main() {
	r := strings.NewReader("Jonathan")
	lr := limitReader(r, 5)
	if _, err := io.Copy(os.Stdout, lr); err != nil {
		fmt.Fprintf(os.Stderr, "ERROR! %v\n", err)
		os.Exit(1)
	}
	fmt.Println()
}

func limitReader(r io.Reader, n int64) io.Reader {
	return &LimReader{
		r: r,
		n: int(n),
	}
}
