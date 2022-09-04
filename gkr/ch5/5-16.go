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
	"unicode"
)

var numeric = flag.Bool("n", false, "sort numerically")
var fold = flag.Bool("f", false, "fold upper and lowercase together")
var dir = flag.Bool("d", false, "directory order")

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
	if !*numeric && !*fold && !*dir {
		sort.Strings(lines)
	} else if !*numeric && !*dir && *fold {
		sort.Slice(lines, func(i, j int) bool {
			si := strings.ToLower(lines[i])
			sj := strings.ToLower(lines[j])
			return si < sj
		})
	} else if !*numeric && !*fold && *dir {
		sort.Slice(lines, func(i, j int) bool {
			var si strings.Builder
			var sj strings.Builder

			for _, r := range lines[i] {
				if unicode.IsLetter(r) || unicode.IsSpace(r) || unicode.IsDigit(r) {
					si.WriteRune(r)
				}
			}
			for _, r := range lines[j] {
				if unicode.IsLetter(r) || unicode.IsSpace(r) || unicode.IsDigit(r) {
					sj.WriteRune(r)
				}
			}
			return si.String() < sj.String()
		})
	} else if !*numeric && *fold && *dir {
		sort.Slice(lines, func(i, j int) bool {
			var si strings.Builder
			var sj strings.Builder

			for _, r := range lines[i] {
				if unicode.IsLetter(r) || unicode.IsSpace(r) || unicode.IsDigit(r) {
					si.WriteRune(r)
				}
			}
			for _, r := range lines[j] {
				if unicode.IsLetter(r) || unicode.IsSpace(r) || unicode.IsDigit(r) {
					sj.WriteRune(r)
				}
			}
			return strings.ToLower(si.String()) < strings.ToLower(sj.String())
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
