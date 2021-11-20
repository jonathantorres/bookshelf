package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

type tnode struct {
	word  string
	count int
	left  *tnode
	right *tnode
}

func main() {
	wordCounts := make(map[string]int)
	r := bufio.NewReader(os.Stdin)
	scanner := bufio.NewScanner(r)
	scanner.Split(bufio.ScanWords)
	for scanner.Scan() {
		w := strings.TrimSpace(scanner.Text())
		wordCounts[w]++
	}
	if err := scanner.Err(); err != nil {
		fmt.Printf("%s\n", err)
		os.Exit(1)
	}
	t := buildTree(wordCounts)
	printTree(t)
}

func buildTree(words map[string]int) *tnode {
	var t *tnode
	for w, n := range words {
		t = addTree(t, w, n)
	}
	return t
}

func addTree(node *tnode, word string, n int) *tnode {
	if node == nil {
		return &tnode{
			word:  word,
			count: n,
		}
	} else if node.count <= n {
		node.left = addTree(node.left, word, n)
	} else {
		node.right = addTree(node.right, word, n)
	}
	return node
}

func printTree(node *tnode) {
	if node != nil {
		printTree(node.left)
		fmt.Printf("%10d %s\n", node.count, node.word)
		printTree(node.right)
	}
}
