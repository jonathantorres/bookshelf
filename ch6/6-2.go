package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
	"unicode"
)

type var_group struct {
	word string
}

var var_arr = []var_group{
	{"char"},
	{"double"},
	{"float"},
	{"int"},
	{"long"},
	{"struct"},
	{"unsigned"},
}

type tnode struct {
	word  string
	count int
	left  *tnode
	right *tnode
}

const (
	Default = 6
	MaxWord = 100
	MaxVar  = 500
	BufSize = 100
)

var VarSize = len(var_arr)
var sp, bufp, vg_index int
var buf []byte
var vgroup [][]byte

func main() {
	buf = make([]byte, BufSize)
	vgroup = make([][]byte, MaxVar)
	n := Default
	var err error
	var root *tnode
	if len(os.Args) == 1 {
		fmt.Printf("Usage: ./program -n, a default value has been set\n")
	} else {
		for i, s := range os.Args {
			if s == "-n" {
				n, err = strconv.Atoi(os.Args[i+1])
				if err != nil {
					fmt.Printf("%s\n", err)
					os.Exit(1)
				}
			}
		}
	}
	word := make([]byte, MaxWord)
	for {
		_, err := getword(word, MaxWord)
		if err != nil {
			break
		}
		if unicode.IsLetter(rune(word[0])) || unicode.IsDigit(rune(word[0])) {
			i := binsearch(string(word), var_arr, VarSize)
			if i >= 0 && vg_index < MaxVar {
				getvar(n)
			}
		}
	}
	vgroup[vg_index] = nil
	for i := 0; i < vg_index-1; i++ {
		root = addtree(root, string(vgroup[i]))
	}
	treeprint(root)
}

func getword(word []byte, lim int) (byte, error) {
	var c byte
	var err error
	for {
		c, err = getch()
		if err != nil {
			return byte(0), err
		}
		if !unicode.IsSpace(rune(c)) {
			break
		}
	}
	if !unicode.IsLetter(rune(c)) || !unicode.IsNumber(rune(c)) {
		return c, nil
	}
	for i := 0; lim > 0; lim, i = lim-1, i-1 {
		c, err = getch()
		if err != nil {
			return byte(0), err
		}
		if !unicode.IsLetter(rune(c)) || !unicode.IsNumber(rune(c)) {
			ungetch(c)
			break
		}
		word[i] = c
	}
	return word[0], nil
}

func getvar(n int) {
	var c byte
	var i int
	var err error
	word := make([]byte, MaxWord)
	for {
		c, err = getch()
		if err != nil {
			return
		}
		if !unicode.IsSpace(rune(c)) {
			break
		}
	}
	ungetch(c)
	for {
		if unicode.IsLetter(rune(c)) || unicode.IsNumber(rune(c)) || rune(c) == '_' {
			word[i] = c
			i++
		} else {
			b := binsearch(string(word), var_arr, VarSize)
			if i >= n && b < 0 {
				vgroup[vg_index] = make([]byte, i)
				copy(vgroup[vg_index], word)
				vg_index++
			}
			i = 0
			for {
				c, err = getch()
				if err != nil {
					return
				}
				if !unicode.IsSpace(rune(c)) {
					break
				}
			}
			if rune(c) != ',' {
				ungetch(c)
				break
			}
		}
	}
}

func addtree(p *tnode, w string) *tnode {
	var cond int
	if p == nil {
		p = new(tnode)
		p.word = w
		p.count = 1
		p.left = nil
		p.right = nil
	} else {
		cond = strings.Compare(w, p.word)
		if cond == 0 {
			p.count++
		} else if cond < 0 {
			p.left = addtree(p.left, w)
		} else {
			p.right = addtree(p.right, w)
		}
	}
	return p
}

func treeprint(p *tnode) {
	if p != nil {
		treeprint(p.left)
		fmt.Printf("%d %s\n", p.count, p.word)
		treeprint(p.right)
	}
}

func binsearch(word string, var_arr []var_group, n int) int {
	var low, high, mid int
	var cond int
	high = n - 1
	for {
		if low > high {
			break
		}
		mid = (low + high) / 2
		cond = strings.Compare(word, var_arr[mid].word)
		if cond < 0 {
			high = mid - 1
		} else if cond > 0 {
			low = mid + 1
		} else {
			return mid
		}
	}
	return -1
}

func getch() (byte, error) {
	if bufp > 0 {
		v := buf[bufp]
		bufp--
		return v, nil
	}
	r := bufio.NewReader(os.Stdin)
	return r.ReadByte()
}

func ungetch(c byte) {
	if bufp >= BufSize {
		fmt.Printf("ungetch: too many characters\n")
	} else {
		buf[bufp] = c
		bufp++
	}
}
