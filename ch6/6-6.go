package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
	"unicode"
)

const (
	HashSize = 101
	MaxWord  = 1000
	BufSize  = 100
)

type nlist struct {
	next *nlist
	name string
	defn string
}

var sp, bufp int
var buf []byte
var hashtab []*nlist

func main() {
	var c byte
	var err error
	var done bool
	var status int
	hashtab = make([]*nlist, HashSize)

	for {
		if done {
			break
		}
		for {
			c, err = getch()
			if err != nil {
				break
			}
			if !unicode.IsSpace(rune(c)) {
				break
			}
			fmt.Printf("%c", rune(c))
			if rune(c) == '\n' {
				status = 1
			}
		}
		if err != nil {
			return
		}
		if rune(c) == '#' && status == 1 {
			status = preproc()
		} else if rune(c) == '\\' {
			status = backslash()
		} else if rune(c) == '/' {
			status = comment()
		} else if rune(c) == '"' {
			status = literal()
		} else if !unicode.IsLetter(rune(c)) && !unicode.IsNumber(rune(c)) && rune(c) != '_' {
			fmt.Printf("%c", rune(c))
			status = 0
		} else {
			ungetch(c)
			status = readword()
		}
		if status == 2 {
			os.Exit(1)
		}
	}
}

func preproc() int {
	var c byte
	var err error
	name := make([]byte, 0, MaxWord)
	defn := make([]byte, 0, MaxWord)
	for {
		c, err = getch()
		if err != nil {
			break
		}
		if !unicode.IsLetter(rune(c)) || !unicode.IsNumber(rune(c)) {
			break
		}
		name = append(name, c)
	}
	if strings.Compare(string(name), "define") == 0 {
		for {
			if !unicode.IsSpace(rune(c)) {
				break
			}
			if rune(c) == '\n' {
				fmt.Printf("%c", rune(c))
				return 1
			}
			c, err = getch()
			if err != nil {
				break
			}
		}
		for {
			c, err = getch()
			if err != nil {
				break
			}
			if !unicode.IsLetter(rune(c)) || !unicode.IsNumber(rune(c)) || rune(c) != '_' {
				break
			}
			name = append(name, c)
		}
		for {
			c, err = getch()
			if err != nil {
				break
			}
			if !unicode.IsLetter(rune(c)) || !unicode.IsNumber(rune(c)) || rune(c) != '_' {
				break
			}
			defn = append(defn, c)
		}
		if install(string(name), string(defn)) == nil {
			return 2
		}
	} else {
		fmt.Printf("%c", '#')
		fmt.Printf("%s", string(name))
	}
	for {
		if rune(c) == '\n' {
			break
		}
		fmt.Printf("%c", rune(c))
		c, err = getch()
		if err != nil {
			return -1
		}
	}
	fmt.Printf("%c", rune(c))
	return 1
}

func backslash() int {
	var c byte
	var err error
	var slash bool
	slash = true
	fmt.Printf("%c", '\\')
	for {
		c, err = getch()
		if err != nil {
			return 1
		}
		if rune(c) != '\\' {
			return 1
		}
		slash = !slash
		fmt.Printf("%c", rune(c))
	}
	if slash {
		fmt.Printf("%c", rune(c))
	} else {
		ungetch(c)
	}
	return 0
}

func comment() int {
	var c byte
	var err error
	var after_star bool
	fmt.Printf("%c", '/')

	c, err = getch()
	if err != nil {
		return 1
	}
	if rune(c) == '*' {
		fmt.Printf("%c", rune(c))
		c, err = getch()
		if err != nil {
			return 1
		}
		for {
			if rune(c) == '\\' {
				backslash()
				after_star = false
			} else if rune(c) == '*' {
				after_star = true
				fmt.Printf("%c", rune(c))
			} else if rune(c) == '/' && after_star {
				fmt.Printf("%c", rune(c))
				return 0
			} else {
				after_star = false
				fmt.Printf("%c", rune(c))
			}
			c, err = getch()
			if err != nil {
				return 1
			}
		}
		fmt.Printf("%c", rune(c))
		return 0
	} else {
		ungetch(c)
		return 0
	}
}

func literal() int {
	var c byte
	var err error
	fmt.Printf("%c", '"')
	c, err = getch()
	if err != nil {
		return 1
	}
	for {
		if rune(c) == '"' {
			break
		}
		if rune(c) == '\\' {
			backslash()
		} else {
			fmt.Printf("%c", rune(c))
		}
		c, err = getch()
		if err != nil {
			return 1
		}
	}
	fmt.Printf("%c", rune(c))
	return 0
}

func readword() int {
	var c byte
	var err error
	word := make([]byte, 0, MaxWord)
	var node *nlist
	c, err = getch()
	if err != nil {
		return 1
	}
	for {
		word = append(word, c)
		c, err = getch()
		if err != nil || rune(c) == '\n' {
			break
		}
	}
	node = lookup(string(word))
	if node == nil {
		fmt.Printf("%s", string(word))
	} else {
		fmt.Printf("%s", node.defn)
	}
	ungetch(c)
	return 0
}

func lookup(s string) *nlist {
	var np *nlist
	for np = hashtab[hash(s)]; np != nil; np = np.next {
		if strings.Compare(s, np.name) == 0 {
			return np
		}
	}
	return nil
}

func install(name string, defn string) *nlist {
	var np *nlist
	var hashval uint
	np = lookup(name)
	if np == nil {
		np = &nlist{
			name: name,
		}
		hashval = hash(name)
		np.next = hashtab[hashval]
		hashtab[hashval] = np
	} else {
		np.defn = ""
	}
	np.defn = defn
	return np
}

func hash(s string) uint {
	var hashval uint
	for _, c := range s {
		hashval = uint(int(c) + 31*int(hashval))
	}
	return hashval % HashSize
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
