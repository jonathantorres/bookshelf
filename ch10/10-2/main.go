package main

import (
	"fmt"
	"os"

	"github.com/jonathantorres/gopl/ch10/10-2/arch"
	_ "github.com/jonathantorres/gopl/ch10/10-2/arch/tar"
	_ "github.com/jonathantorres/gopl/ch10/10-2/arch/zip"
)

func main() {
	z, err := arch.Open("Consolas.zip")
	if err != nil {
		fmt.Fprintf(os.Stderr, "%s\n", err)
		os.Exit(1)
	}
	for _, f := range z.Files {
		fmt.Println(f)
	}
	fmt.Println()

	z2, err := arch.Open("go1.13.5.src.tar")
	if err != nil {
		fmt.Fprintf(os.Stderr, "%s\n", err)
		os.Exit(1)
	}
	for _, f := range z2.Files {
		fmt.Println(f)
	}
}
