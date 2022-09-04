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
var pos1 int
var pos2 int
var usePos bool

func main() {
	flag.Parse()
	var err error
	if len(flag.Args()) == 2 {
		usePos = true
		pos1, err = strconv.Atoi(flag.Args()[0])
		if err != nil {
			fmt.Fprintf(os.Stderr, "%s\n", err)
			os.Exit(1)
		}
		pos2, err = strconv.Atoi(flag.Args()[1])
		if err != nil {
			fmt.Fprintf(os.Stderr, "%s\n", err)
			os.Exit(1)
		}
		if pos1 < 0 || pos2 < 0 {
			fmt.Fprintf(os.Stderr, "The start and end positions must be greater than or equal to 0")
			os.Exit(1)
		}
	}
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
		sort.Slice(lines, func(i, j int) bool {
			var si string
			var sj string
			if usePos {
				si = lines[i][pos1:pos2]
				sj = lines[j][pos1:pos2]
			} else {
				si = lines[i]
				sj = lines[j]
			}
			return si < sj
		})
	} else if !*numeric && !*dir && *fold {
		sort.Slice(lines, func(i, j int) bool {
			var si string
			var sj string
			if usePos {
				si = lines[i][pos1:pos2]
				sj = lines[j][pos1:pos2]
			} else {
				si = lines[i]
				sj = lines[j]
			}
			si = strings.ToLower(si)
			sj = strings.ToLower(sj)
			return si < sj
		})
	} else if !*numeric && !*fold && *dir {
		sort.Slice(lines, func(i, j int) bool {
			var sib strings.Builder
			var sjb strings.Builder
			var si string
			var sj string
			if usePos {
				si = lines[i][pos1:pos2]
				sj = lines[j][pos1:pos2]
			} else {
				si = lines[i]
				sj = lines[j]
			}
			for _, r := range si {
				if unicode.IsLetter(r) || unicode.IsSpace(r) || unicode.IsDigit(r) {
					sib.WriteRune(r)
				}
			}
			for _, r := range sj {
				if unicode.IsLetter(r) || unicode.IsSpace(r) || unicode.IsDigit(r) {
					sjb.WriteRune(r)
				}
			}
			return sib.String() < sjb.String()
		})
	} else if !*numeric && *fold && *dir {
		sort.Slice(lines, func(i, j int) bool {
			var sib strings.Builder
			var sjb strings.Builder
			var si string
			var sj string
			if usePos {
				si = lines[i][pos1:pos2]
				sj = lines[j][pos1:pos2]
			} else {
				si = lines[i]
				sj = lines[j]
			}

			for _, r := range si {
				if unicode.IsLetter(r) || unicode.IsSpace(r) || unicode.IsDigit(r) {
					sib.WriteRune(r)
				}
			}
			for _, r := range sj {
				if unicode.IsLetter(r) || unicode.IsSpace(r) || unicode.IsDigit(r) {
					sjb.WriteRune(r)
				}
			}
			return strings.ToLower(sib.String()) < strings.ToLower(sjb.String())
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
