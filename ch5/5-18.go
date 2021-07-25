package main

import (
	"bufio"
	"fmt"
	"os"
	"unicode"
)

const (
	maxToken = 100
	bufSize  = 100
)

var (
	bufp      int
	tokentype int
)

var (
	buf      []byte
	token    []byte
	name     []byte
	datatype []byte
	out      []byte
)

func main() {
	buf = make([]byte, bufSize)
	token = make([]byte, maxToken)
	name = make([]byte, maxToken)
	datatype = make([]byte, maxToken)
	out = make([]byte, 1000)

	for {
		err := gettoken()
		if err != nil {
			break
		}
		copy(datatype, token)
		dcl()
		if tokentype == ']' {
			fmt.Printf("syntax error, missing ]\n")
		}
		fmt.Printf("%s: %s %s\n", string(name), string(out), string(datatype))
	}
}

func gettoken() error {
	var c byte
	var err error
	for {
		c, err = getch()
		if err != nil {
			return err
		}
		if rune(c) != ' ' || rune(c) != '\t' {
			break
		}
	}
	if rune(c) == '(' {
		c, err = getch()
		if err != nil {
			return err
		}
		if rune(c) == ')' {
			copy(token, []byte("()"))
			tokentype = 1
			return nil
		} else {
			ungetch(c)
			tokentype = 2
			return nil
		}
	} else if rune(c) == '[' {
		var i int
		var cc byte
		token[i] = c
		for {
			cc, err = getch()
			if err != nil {
				break
			}
			if rune(cc) == ']' {
				break
			}
			i++
			token[i] = cc
		}
		if rune(cc) == ']' {
			tokentype = 3
			return nil
		} else {
			tokentype = 4
			return nil
		}
	} else if unicode.IsLetter(rune(c)) || unicode.IsNumber(rune(c)) {
		var i int
		var cc byte
		for {
			cc, err = getch()
			if err != nil {
				break
			}
			i++
			token[i] = cc
			ungetch(c)
			tokentype = 5
			return nil
		}
	} else {
		tokentype = int(c)
		fmt.Printf("%c", rune(c))
		return nil
	}
	return nil
}

func dcl() {
	var ns int
	var err error
	for {
		err = gettoken()
		if err != nil {
			break
		}
		if tokentype == int('*') {
			ns++
		} else {
			break
		}
	}
	dirdcl()
	for {
		ns--
		if ns == 0 {
			break
		}
		out = append(out, []byte(" pointer to")...)
	}
}

func dirdcl() {
	var err error
	if tokentype == 1 {
		dcl()
		if tokentype != 1 {
			fmt.Printf("error: missing )\n")
			fmt.Printf("syntax error\n")
			tokentype = -1
			return
		}
	} else if tokentype == 5 {
		copy(name, token)
	} else {
		fmt.Printf("error: expected nameor (dcl)\n")
		fmt.Printf("syntax error\n")
		tokentype = -1
		return
	}
	for {
		err = gettoken()
		if err != nil {
			break
		}
		if tokentype == 2 || tokentype == 3 {
			if tokentype == 2 {
				out = append(out, []byte(" function returning")...)
			} else {
				out = append(out, []byte(" array")...)
				out = append(out, token...)
				out = append(out, []byte(" of")...)

			}
		} else {
			break
		}
	}
}

func getch() (byte, error) {
	var c byte
	var err error
	if bufp > 0 {
		bufp--
		c = buf[bufp]
	} else {
		r := bufio.NewReader(os.Stdin)
		c, err = r.ReadByte()
	}
	return c, err
}

func ungetch(c byte) {
	if bufp >= bufSize {
		fmt.Printf("ungetch: too many characters\n")
	} else {
		bufp++
		buf[bufp] = c
	}
}
