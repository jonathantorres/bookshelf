package main

import (
	"bufio"
	"flag"
	"fmt"
	"io"
	"os"
	"sort"
	"strconv"
	"strings"
)

var numeric = flag.Bool("n", false, "sort numerically")
var reverse = flag.Bool("r", false, "sort on reverse")

func main() {
	flag.Parse()
	var inputLines []string
	r := bufio.NewReader(os.Stdin)
	for {
		line, err := r.ReadBytes(byte('\n'))
		if err != nil {
			if err != io.EOF {
				fmt.Printf("error: %s\n", err)
			}
			break
		}
		inputLines = append(inputLines, strings.TrimSpace(string(line)))
	}
	sortLines(inputLines)
	fmt.Println()
	for _, l := range inputLines {
		fmt.Printf("%s\n", l)
	}
}

func sortLines(lines []string) {
	if !*numeric && !*reverse {
		sort.Strings(lines)
	} else if !*numeric && *reverse {
		sort.Slice(lines, func(i, j int) bool {
			return lines[i] > lines[j]
		})
	} else if *numeric && !*reverse {
		sort.Slice(lines, func(i, j int) bool {
			fi, _ := strconv.ParseFloat(lines[i], 64)
			fj, _ := strconv.ParseFloat(lines[j], 64)
			return fi < fj
		})
	} else if *numeric && *reverse {
		sort.Slice(lines, func(i, j int) bool {
			fi, _ := strconv.ParseFloat(lines[i], 64)
			fj, _ := strconv.ParseFloat(lines[j], 64)
			return fi > fj
		})
	} else {
		panic("sorting configuration not recognized")
	}
}
