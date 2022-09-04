package main

import (
	"bufio"
	"bytes"
	"errors"
	"fmt"
	"io"
	"os"
	"strings"
	"unicode"
)

const (
	name rune = iota
	parens
	brackets
	syntaxErr
)

const (
	no rune = iota
	yes
)

var buf *bytes.Buffer
var token bytes.Buffer
var out bytes.Buffer
var tokentype rune
var pretoken rune

func main() {
	r := bufio.NewReader(os.Stdin)
	pretoken = no
	for {
		l, err := r.ReadBytes('\n')
		if err != nil {
			break
		}
		decl, err := parse(l)
		if err != nil {
			fmt.Printf("%s\n", err)
			continue
		}
		fmt.Printf("%s\n", decl)
	}
}

func parse(exp []byte) (string, error) {
	buf = bytes.NewBuffer(exp)
	var temp strings.Builder
	for {
		_, err := getToken()
		if err != nil {
			if err == io.EOF {
				break
			}
			return "", err
		}
		out.WriteString(token.String())
		token.Reset()
		for {
			typ, err := getToken()
			if err != nil {
				if err == io.EOF {
					break
				}
				return "", err
			}
			if typ == '\n' {
				break
			}
			if typ == parens || typ == brackets {
				out.WriteString(token.String())
				token.Reset()
			} else if typ == '*' {
				typ = postToken()
				if typ == parens || typ == brackets {
					temp.WriteString(fmt.Sprintf("(*%s)", out.String()))
					out.Reset()
				} else {
					temp.WriteString(fmt.Sprintf("*%s", out.String()))
					out.Reset()
				}
				out.WriteString(temp.String())
				temp.Reset()
			} else if typ == name {
				temp.WriteString(fmt.Sprintf("%s %s", token.String(), out.String()))
				out.Reset()
				token.Reset()
				out.WriteString(temp.String())
				temp.Reset()
			} else {
				tokenString := token.String()
				token.Reset()
				temp.Reset()
				out.Reset()
				return "", fmt.Errorf("invalid input at %s", tokenString)
			}
		}
	}
	outStr := out.String()
	out.Reset()
	return outStr, nil
}

func getToken() (rune, error) {
	var c rune
	var err error
	if pretoken == yes {
		pretoken = no
		return tokentype, nil
	}
	for {
		c, _, err = buf.ReadRune()
		if err != nil {
			return 0, err
		}
		if unicode.IsSpace(c) {
			continue
		}
		if c == '(' {
			c, _, err := buf.ReadRune()
			if err != nil {
				if err == io.EOF {
					return 0, nil
				}
				return 0, err
			}
			if c == ')' {
				tokentype = parens
				return tokentype, nil
			}
			buf.UnreadRune()
			tokentype = '('
			return tokentype, nil
		} else if c == '[' {
			last := writeTokenChars(c)
			if last == ']' {
				tokentype = brackets
				return tokentype, nil
			}
			tokentype = ']'
			return tokentype, nil
		} else if unicode.IsLetter(c) {
			writeTokenName(c)
			tokentype = name
			return tokentype, nil
		} else {
			tokentype = c
			return tokentype, nil
		}
	}
	return 0, errors.New("unreachable")
}

func writeTokenChars(f rune) rune {
	var last rune
	token.WriteRune(f) // write first rune
	for {
		c, _, err := buf.ReadRune()
		if err != nil {
			break
		}
		// continue writing until we find the closing ]
		if c == ']' || c == '\n' {
			if c == ']' {
				token.WriteRune(c)
				last = c
			}
			break
		}
		token.WriteRune(c)
		last = c
	}
	return last
}

func writeTokenName(f rune) {
	token.WriteRune(f) // write first rune in name
	for {
		c, _, err := buf.ReadRune()
		if err != nil {
			break
		}
		// write the rest of the name
		if unicode.IsLetter(c) || unicode.IsNumber(c) {
			token.WriteRune(c)
			continue
		}
		// stop here, since we found another character
		// push it back into the buffer
		buf.UnreadRune()
		break
	}
}

func postToken() rune {
	var nexttype rune
	nexttype, _ = getToken()
	pretoken = yes
	return nexttype
}
