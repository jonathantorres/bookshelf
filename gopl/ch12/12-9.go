package main

import (
	"bytes"
	"fmt"
	"io"
	"os"
	"strconv"
	"text/scanner"
)

func main() {
	sexp := []byte("(1 2 3 4 5)")
	dec := NewDecoder(bytes.NewReader(sexp))
	var buf bytes.Buffer
	for {
		tok, err := dec.Token()
		if err == io.EOF {
			break
		} else if err != nil {
			fmt.Fprintf(os.Stderr, "%s\n", err)
			os.Exit(1)
		}
		switch tok := tok.(type) {
		case Symbol, String:
			buf.WriteString(fmt.Sprintf("%s", tok))
		case Int:
			buf.WriteString(fmt.Sprintf("%d", tok))
		case StartList:
			buf.WriteRune(rune(tok))
		case EndList:
			buf.WriteRune(rune(tok))
		}
	}
	fmt.Println(buf.String())
}

type Decoder struct {
	s     scanner.Scanner
	err   error
	depth int
}

func (d *Decoder) Token() (Token, error) {
	t := d.s.Scan()
	if d.err != nil {
		return nil, d.err
	}
	if d.depth == 0 && t != '(' && t != scanner.EOF {
		return nil, fmt.Errorf("expecting '(', got %s", scanner.TokenString(t))
	}
	switch t {
	case scanner.EOF:
		return nil, io.EOF
	case scanner.Ident:
		return Symbol(d.s.TokenText()), nil
	case scanner.String:
		text := d.s.TokenText()
		return String(text[1 : len(text)-1]), nil
	case scanner.Int:
		n, err := strconv.ParseInt(d.s.TokenText(), 10, 64)
		if err != nil {
			return nil, err
		}
		return Int(n), nil
	case '(':
		d.depth++
		return StartList('('), nil
	case ')':
		d.depth--
		return EndList(')'), nil
	default:
		pos := d.s.Pos()
		return nil, fmt.Errorf("unexpected token %s at L%d:C%d", scanner.TokenString(t), pos.Line, pos.Column)
	}
}

func (d *Decoder) setError(s *scanner.Scanner, m string) {
	d.err = fmt.Errorf("scanning: %s", m)
}

type Token interface{}
type Symbol string
type String string
type Int int
type StartList rune // (
type EndList rune   // )

func (i Int) String() string {
	return fmt.Sprintf("Int(%d)", i)
}

func (s StartList) String() string {
	return "("
}

func (s EndList) String() string {
	return ")"
}

func NewDecoder(r io.Reader) *Decoder {
	var scan scanner.Scanner
	scan.Init(r)
	d := Decoder{s: scan}
	scan.Error = d.setError
	return &d
}
