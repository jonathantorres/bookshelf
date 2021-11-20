package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

type key struct {
	word  string
	count int
}

var keytab = []key{
	{"auto", 0},
	{"break", 0},
	{"case", 0},
	{"char", 0},
	{"const", 0},
	{"continue", 0},
	{"default", 0},
	{"unsigned", 0},
	{"void", 0},
	{"volatile", 0},
	{"while", 0},
}

func main() {
	r := bufio.NewReader(os.Stdin)
	scanner := bufio.NewScanner(r)
	for scanner.Scan() {
		w := scanner.Bytes()
		countKeywords(w)
	}
	for _, key := range keytab {
		if key.count > 0 {
			fmt.Printf("%d %s\n", key.count, key.word)
		}
	}
}

func countKeywords(line []byte) {
	for i, key := range keytab {
		if strings.Contains(string(line), key.word+" ") {
			keytab[i].count++
		}
		if strings.Contains(string(line), key.word+";") {
			keytab[i].count++
		}
		if strings.Contains(string(line), key.word+")") {
			keytab[i].count++
		}
	}
}
