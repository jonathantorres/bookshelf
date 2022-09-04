package main

import (
	"io"
	"log"
	"os"

	"github.com/jonathantorres/gopl/ch13/13-3/bzip"
)

func main() {
	w := bzip.NewWriter(os.Stdout)
	if _, err := io.Copy(w, os.Stdin); err != nil {
		log.Fatalf("bzip: %v\n", err)
	}
	if err := w.Close(); err != nil {
		log.Fatalf("bzip: close: %v\n", err)
	}
}
