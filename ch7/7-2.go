package main

import (
	"fmt"
	"io"
	"os"
)

type CW struct {
	n int64
	w io.Writer
}

func (c *CW) Write(p []byte) (int, error) {
	n, err := c.w.Write(p)
	if err != nil {
		return 0, err
	}
	c.n += int64(n)
	return n, err
}

func main() {
	w, n := CountingWriter(os.Stdout)
	w.Write([]byte("Hola\n"))
	fmt.Println(*n)
	w.Write([]byte("Hello\n"))
	fmt.Println(*n)
}

func CountingWriter(w io.Writer) (io.Writer, *int64) {
	cw := CW{
		n: 0,
		w: w,
	}
	return &cw, &cw.n
}
