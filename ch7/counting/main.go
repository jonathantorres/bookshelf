package main

// Exercise 7.2

import (
	"bufio"
	"fmt"
	"io"
	"os"
)

type CountWriter struct {
	w io.Writer
	b *int64
}

func main() {
	w, n := CountingWriter(os.Stdout)
	fmt.Println("start:", *n)
	_, err := w.Write([]byte("Hello!\n"))
	if err != nil {
		fmt.Fprintf(os.Stderr, "error writing!\n")
		os.Exit(1)
	}
	fmt.Println("end:", *n)
}

func (cw *CountWriter) Write(p []byte) (int, error) {
	*cw.b += int64(len(p))
	l, err := cw.w.Write(p)
	if err != nil {
		return 0, err
	}
	return l, nil
}

func CountingWriter(w io.Writer) (io.Writer, *int64) {
	cw := CountWriter{
		w: bufio.NewWriter(w),
		b: new(int64),
	}
	return &cw, cw.b
}
