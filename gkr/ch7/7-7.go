package main

import (
	"bufio"
	"flag"
	"fmt"
	"os"
	"strings"
)

type match struct {
	lineNum int
	line    string
}

var nFlag = flag.Bool("n", false, "print line numbers")
var xFlag = flag.Bool("x", false, "print lines that do not match instead")

func main() {
	flag.Parse()
	var pattern string
	matches := make([]*match, 0, 5)
	for i, arg := range flag.Args() {
		if i == 0 {
			pattern = arg
			continue
		}
		f, err := os.Open(arg)
		if err != nil {
			fmt.Printf("find: %s\n", err)
			os.Exit(1)
		}
		scanner := bufio.NewScanner(f)
		var ln int
		for scanner.Scan() {
			l := scanner.Text()
			ln++
			found := strings.Contains(l, pattern)
			if *xFlag == false && found {
				m := &match{
					lineNum: ln,
					line:    l,
				}
				matches = append(matches, m)
			} else if *xFlag && !found {
				m := &match{
					lineNum: ln,
					line:    l,
				}
				matches = append(matches, m)
			}
		}
		if err := scanner.Err(); err != nil {
			fmt.Printf("find: %s\n", err)
			os.Exit(1)
		}
	}
	for _, m := range matches {
		if *nFlag {
			fmt.Printf("%d: ", m.lineNum)
		}
		fmt.Printf("%s\n", m.line)
	}
}
