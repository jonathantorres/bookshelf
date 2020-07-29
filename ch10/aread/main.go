package main

// Exercise 10.2
// Exercise 10.3 - The code is hosted on GitHub - https://github.com/adonovan/gopl.io

import (
	"archive/tar"
	"archive/zip"
	"fmt"
	"io"
	"log"
	"os"
	"strings"
)

func main() {
	if len(os.Args) == 1 {
		fmt.Println("usage: aread [zip/tar file]")
		os.Exit(1)
	}
	filename := os.Args[1]
	if strings.HasSuffix(filename, ".zip") {
		r, err := zip.OpenReader(filename)
		if err != nil {
			log.Fatalln(err)
		}
		defer r.Close()
		for _, f := range r.File {
			fmt.Println(f.Name)
		}
		os.Exit(0)
	}
	if strings.HasSuffix(filename, ".tar") {
		r, err := os.Open(filename)
		if err != nil {
			log.Fatal(err)
		}
		defer r.Close()
		tr := tar.NewReader(r)
		for {
			hdr, err := tr.Next()
			if err == io.EOF {
				break
			}
			if err != nil {
				log.Fatalln(err)
			}
			fmt.Println(hdr.Name)
		}
		os.Exit(0)
	}
	log.Fatalf("%s is not supported\n", filename)
}
