package main

import (
	"bufio"
	"bytes"
	"fmt"
	"os"
	"strings"
)

type tnode struct {
	word  string
	lines []int
	left  *tnode
	right *tnode
}

func main() {
	var root *tnode
	r := bufio.NewReader(os.Stdin)
	scanner := bufio.NewScanner(r)
	var ln int
	for scanner.Scan() {
		l := scanner.Bytes()
		ln++
		root = addWords(root, l, ln)
	}
	if err := scanner.Err(); err != nil {
		fmt.Printf("%s\n", err)
		os.Exit(1)
	}
	printTree(root)
}

func addWords(root *tnode, l []byte, ln int) *tnode {
	words := getWords(l)
	if len(words) == 0 {
		return root
	}
	for _, w := range words {
		root = addTree(root, w, ln)
	}
	return root
}

func getWords(l []byte) []string {
	var words []string
	spl := bytes.Split(l, []byte(" "))
	for _, word := range spl {
		w := string(bytes.TrimSpace(word))
		if !isNoiseWord(w) && w != "" {
			words = append(words, w)
		}
	}
	return words
}

func isNoiseWord(word string) bool {
	var words = []string{
		"a",
		"an",
		"and",
		"be",
		"but",
		"by",
		"he",
		"I",
		"is",
		"it",
		"off",
		"on",
		"she",
		"so",
		"the",
		"they",
		"you",
	}
	for _, w := range words {
		if strings.ToLower(word) == w {
			return true
		}
	}
	return false
}

func addTree(node *tnode, word string, ln int) *tnode {
	if node == nil {
		return &tnode{
			word:  word,
			lines: []int{ln},
		}
	} else if cmp := strings.Compare(strings.ToLower(word), strings.ToLower(node.word)); cmp == 0 {
		node.lines = append(node.lines, ln)
	} else if cmp < 0 {
		node.left = addTree(node.left, word, ln)
	} else {
		node.right = addTree(node.right, word, ln)
	}
	return node
}

func printTree(node *tnode) {
	if node != nil {
		printTree(node.left)
		fmt.Printf("%s\t\t", node.word)
		for _, n := range node.lines {
			fmt.Printf("%d,", n)
		}
		fmt.Println()
		printTree(node.right)
	}
}
