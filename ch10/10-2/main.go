package main

import (
	"fmt"
	"os"

	"github.com/jonathantorres/gopl/ch10/10-2/arch/tar"
)

func main() {
	f, err := tar.Open("file.tar")
	if err != nil {
		fmt.Fprintf(os.Stderr, "%s\n", err)
		os.Exit(1)
	}
}
