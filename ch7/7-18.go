package main

import (
	"bytes"
	"encoding/xml"
	"fmt"
	"io"
	"os"
)

type Node interface{} // CharData or *Element

type CharData string

type Element struct {
	Type     xml.Name
	Attr     []xml.Attr
	Children []Node
}

type stack []*Element

func (s stack) push(e *Element) stack {
	s = append(s, e)
	return s
}

func (s stack) peek() *Element {
	if len(s) == 0 {
		return nil
	}
	return s[len(s)-1]
}

func (s stack) pop() (stack, *Element) {
	if len(s) == 0 {
		return s, nil
	}
	el := s[len(s)-1]
	s = s[:len(s)-1]
	return s, el
}

func main() {
	dec := xml.NewDecoder(os.Stdin)
	var tree Node
	s := make(stack, 0, 10)
	for {
		tok, err := dec.Token()
		if err == io.EOF {
			break
		}
		if err != nil {
			fmt.Fprintf(os.Stderr, "error: %v\n", err)
			os.Exit(1)
		}
		switch tok := tok.(type) {
		case xml.StartElement:
			el := createElement(tok)
			if tree == nil {
				tree = el
				s = s.push(el)
			} else {
				p := s.peek()
				p.Children = append(p.Children, el)
				s = s.push(el)
			}
		case xml.EndElement:
			s, _ = s.pop()
		case xml.CharData:
			char := string(bytes.TrimSpace(tok))
			if char != "" {
				cd := CharData(char)
				p := s.peek()
				p.Children = append(p.Children, cd)
			}
		}
	}
	printXml(os.Stdout, tree, 0)
}

func createElement(e xml.StartElement) *Element {
	var attr []xml.Attr
	if len(e.Attr) > 0 {
		attr = make([]xml.Attr, len(e.Attr))
		copy(attr, e.Attr)
	}
	el := &Element{
		Type:     xml.Name{Space: e.Name.Space, Local: e.Name.Local},
		Attr:     attr,
		Children: make([]Node, 0, 5),
	}
	return el
}

func printXml(w io.Writer, t Node, depth int) {
	switch el := t.(type) {
	case *Element:
		fmt.Fprintf(w, "%*s<%s>", depth*2, "", el.Type.Local)
		if len(el.Children) > 1 {
			fmt.Fprintf(w, "\n")
		}
		for _, c := range el.Children {
			printXml(w, c, depth+1)
		}
		if len(el.Children) > 1 {
			fmt.Fprintf(w, "%*s</%s>\n", depth*2, "", el.Type.Local)
		} else {
			fmt.Fprintf(w, "</%s>\n", el.Type.Local)
		}
	case CharData:
		fmt.Fprintf(w, "%s", el)
	}
}
