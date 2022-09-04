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
var fold = flag.Bool("f", false, "fold upper and lowercase together")

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
	if !*numeric && !*fold {
		sort.Strings(lines)
	} else if !*numeric && *fold {
		sort.Slice(lines, func(i, j int) bool {
			si := strings.ToLower(lines[i])
			sj := strings.ToLower(lines[j])
			return si < sj
		})
	} else if *numeric {
		sort.Slice(lines, func(i, j int) bool {
			fi, _ := strconv.ParseFloat(lines[i], 64)
			fj, _ := strconv.ParseFloat(lines[j], 64)
			return fi < fj
		})
	} else {
		panic("sorting configuration not recognized")
	}
}
