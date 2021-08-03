package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"strings"
)

type word_t struct {
	word  string
	count int
	left  *word_t
	right *word_t
}

const NonAlpha = "1234567890 \v\f\n\t\r+=-*/\\,.;:'#~?<>|{}[]`!\"�$%^&()"

func main() {
	var words *word_t
	var tree_count int
	err := read_input_to_tree(words, tree_count, os.Stdin)
	if err != nil {
		fmt.Printf("%s\n", err)
		os.Exit(1)
	}
	walk_tree(words)
	output_words(os.Stdout, tree_count, words)
}

func add_to_tree(dest_tree *word_t, tree_count int, word string) {
	if dest_tree == nil {
		dest_tree = new(word_t)
		dest_tree.left = nil
		dest_tree.right = nil
		dest_tree.count = 1
		dest_tree.word = word
		tree_count++
	} else {
		r := strings.Compare(word, dest_tree.word)
		if r < 0 {
			add_to_tree(dest_tree.left, tree_count, word)
		} else if r > 0 {
			add_to_tree(dest_tree.right, tree_count, word)
		} else {
			dest_tree.count++
		}
	}
}

func read_input_to_tree(dest_tree *word_t, tree_count int, input io.Reader) error {
	s := bufio.NewScanner(input)
	s.Split(bufio.ScanWords)

	for s.Scan() {
		w := s.Text()
		add_to_tree(dest_tree, tree_count, w)
	}
	if err := s.Err(); err != nil {
		return err
	}
	return nil
}

func walk_tree(dest_tree *word_t) {
	if dest_tree != nil {
		if dest_tree.left != nil {
			walk_tree(dest_tree.left)
		} else if dest_tree.right != nil {
			walk_tree(dest_tree.right)
		}
	}
}

func output_words(dest io.Writer, count int, dest_tree *word_t) {
	fmt.Fprintf(dest, "Total words: %d\n", count)
	output_word(dest, dest_tree)
}

func output_word(dest io.Writer, dest_tree *word_t) {
	if dest_tree != nil {
		if dest_tree.left != nil {
			output_word(dest, dest_tree.left)
		}
		fmt.Fprintf(dest, "%d %s\n", dest_tree.count, dest_tree.word)
		if dest_tree.right != nil {
			output_word(dest, dest_tree.right)
		}
	}
}
