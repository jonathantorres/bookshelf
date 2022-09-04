package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	r := bufio.NewReader(os.Stdin)
	buf, err := r.ReadBytes('\n')
	if err != nil {
		fmt.Printf("%s\n", err)
		return
	}
	n, err := strconv.Atoi(strings.TrimSpace(string(buf)))
	if err != nil {
		fmt.Printf("%s\n", err)
		return
	}
	fmt.Printf("%d\n", n)
}
