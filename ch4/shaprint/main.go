package main

import (
	"bufio"
	"crypto/sha256"
	"crypto/sha512"
	"flag"
	"fmt"
	"os"
)

// Exercise 4.2

func main() {
	use384 := flag.Bool("a", false, "use sha 384")
	use512 := flag.Bool("b", false, "use sha 512")
	flag.Parse()

	scanner := bufio.NewScanner(os.Stdin)
	for scanner.Scan() {
		txt := scanner.Text()
		if *use512 {
			fmt.Printf("SHA512: %x\n", sha512.Sum512([]byte(txt)))
		} else if *use384 {
			fmt.Printf("SHA384: %x\n", sha512.Sum384([]byte(txt)))
		} else {
			fmt.Printf("SHA256: %x\n", sha256.Sum256([]byte(txt)))
		}
	}
	if err := scanner.Err(); err != nil {
		fmt.Fprintln(os.Stderr, "reading standard input:", err)
	}
}
