package main

import (
	"bufio"
	"bytes"
	"flag"
	"fmt"
	"os"
	"strings"
	"unicode"
)

type tnode struct {
	word  string
	count int
	left  *tnode
	right *tnode
}

var nFlag = flag.Int("n", 6, "default length of words")

func main() {
	flag.Parse()
	var root *tnode
	r := bufio.NewReader(os.Stdin)
	scanner := bufio.NewScanner(r)
	for scanner.Scan() {
		l := scanner.Bytes()
		root = addWords(root, l)
	}
	if err := scanner.Err(); err != nil {
		fmt.Printf("%s\n", err)
		os.Exit(1)
	}
	printTree(root)
}

func addWords(root *tnode, l []byte) *tnode {
	words := getWords(l)
	if len(words) == 0 {
		return root
	}
	for _, w := range words {
		if len(w) >= *nFlag {
			root = addTree(root, w)
		}
	}
	return root
}

func addTree(node *tnode, word string) *tnode {
	if node == nil {
		return &tnode{
			word:  word,
			count: 1,
		}
	} else if cmp := compareWords(word, node.word); cmp == 0 {
		node.count++
	} else if cmp < 0 {
		node.left = addTree(node.left, word)
	} else {
		node.right = addTree(node.right, word)
	}
	return node
}

func compareWords(w1, w2 string) int {
	n := (*nFlag)
	return strings.Compare(w1[:n], w2[:n])
}

func getWords(l []byte) []string {
	var words []string
	spl := bytes.Split(l, []byte(" "))
	for _, word := range spl {
		var cleanW strings.Builder
		w := bytes.TrimSpace(word)
		for _, c := range w {
			if unicode.IsDigit(rune(c)) || unicode.IsLetter(rune(c)) || rune(c) == '_' {
				cleanW.WriteByte(c)
			} else {
				if cleanW.Len() > 0 && !isKeyword(cleanW.String()) {
					words = append(words, cleanW.String())
					cleanW.Reset()
					continue
				}
			}
		}
		if cleanW.Len() > 0 && !isKeyword(cleanW.String()) {
			words = append(words, cleanW.String())
		}
	}
	return words
}

func isKeyword(word string) bool {
	var keywords = []string{
		"char",
		"double",
		"float",
		"int",
		"long",
		"struct",
		"unsigned",
		"else",
		"if",
		"break",
		"continue",
		"return",
		"void",
		"include",
		"define",
		"while",
	}
	for _, k := range keywords {
		if word == k {
			return true
		}
	}
	return false
}

func printTree(node *tnode) {
	if node != nil {
		printTree(node.left)
		if node.count > 1 && len(node.word) > 1 {
			fmt.Printf("%d %s\n", node.count, node.word)
		}
		printTree(node.right)
	}
}
