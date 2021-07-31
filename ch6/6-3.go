package main

import (
	"bufio"
	"bytes"
	"fmt"
	"os"
)

const MaxLine = 8192

type linelist struct {
	next *linelist
	line int
}

type wordtree struct {
	word      string
	firstline *linelist
	left      *wordtree
	right     *wordtree
}

func main() {
	var buffer []byte
	var s []byte
	var word []byte
	var line, n int
	var giveup bool
	var tree *wordtree
	delims := " \t\n\r\a\f\v!\"%^&*()_=+{}[]\\|/,.<>:;#~?"

	for {
		buffer, n = getLine(MaxLine)
		if giveup || n == 0 {
			break
		}
		line++
		s = buffer
		for {
			word = tokenise(s, delims)
			if giveup || word == nil {
				break
			}
			if !noiseword(word) {
				w := addword(tree, word, line)
				if w == nil {
					fmt.Printf("Error adding data into memory. Giving up.\n")
					giveup = true
				}
			}
		}
	}
	if !giveup {
		fmt.Printf("%s Line Numbers\n", "Word")
		printtree(tree)
	}
	deleteword(tree)
}

func deleteword(node *wordtree) {
	var tmp *wordtree
	if node != nil {
		if node.right != nil {
			tmp = node
			deleteword(tmp.right)
		}
		if node.left != nil {
			tmp = node
			deleteword(tmp.left)
		}
		if node.firstline != nil {
			deletelist(node.firstline)
		}
	}
}

func addword(node *wordtree, word []byte, line int) *wordtree {
	var wordloc *wordtree
	if node == nil {
		wordloc = new(wordtree)
		wordloc.left = nil
		wordloc.right = nil
		wordloc.word = string(word)
		wordloc.firstline = addlink(line)
	} else {
		newline := addlink(line)
		comp := bytes.Compare(word, []byte(node.word))
		if comp == 0 {
			wordloc = node
			newline.next = node.firstline
			node.firstline = newline
		} else if comp < 0 {
			tmp := node
			wordloc = addword(tmp.left, word, line)
		} else {
			tmp := node
			wordloc = addword(tmp.right, word, line)
		}
	}
	if wordloc == nil {
		deleteword(wordloc)
	}
	return wordloc
}

func tokenise(s []byte, delims string) []byte {
	var r []byte
	var b byte
	for _, ss := range s {
		if !bytes.ContainsRune([]byte(delims), rune(ss)) {
			b = ss
			r = append(r, b+1)
		}
	}
	return r
}

func noiseword(s []byte) bool {
	list := []string{
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
	var found bool
	for {
		if found {
			break
		}
		for _, l := range list {
			if bytes.ContainsAny(s, l) {
				found = true
			}
		}
	}
	return found
}

func deletelist(listnode *linelist) {
	if listnode != nil {
		deletelist(listnode.next)
	}
}

func addlink(line int) *linelist {
	ll := new(linelist)
	ll.line = line
	ll.next = nil
	return ll
}

func printtree(node *wordtree) {
	if node != nil {
		printtree(node.left)
		fmt.Printf("%s ", node.word)
		printlist(node.firstline)
		fmt.Println()
		printtree(node.right)
	}
}

func printlist(list *linelist) {
	if list != nil {
		printlist(list.next)
		fmt.Printf("%d ", list.line)
	}
}

func getLine(lim int) ([]byte, int) {
	var c byte
	var i int
	s := make([]byte, lim)
	r := bufio.NewReader(os.Stdin)
	for i = 0; i < lim-1; i++ {
		c, err := r.ReadByte()
		if rune(c) == '\n' || err != nil {
			break
		}
		s[i] = c
	}
	if rune(c) == '\n' {
		s[i] = c
		i++
	}
	return s, i
}
