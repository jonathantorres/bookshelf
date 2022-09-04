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
	f, err := strconv.ParseFloat(strings.TrimSpace(string(buf)), 64)
	if err != nil {
		fmt.Printf("%s\n", err)
		return
	}
	fmt.Printf("%f\n", f)
}
