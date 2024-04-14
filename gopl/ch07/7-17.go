package main

import (
	"bytes"
	"encoding/xml"
	"fmt"
	"io"
	"os"
	"strings"
)

func main() {
	dec := xml.NewDecoder(os.Stdin)
	var stack []xml.StartElement // stack of elements
	for {
		tok, err := dec.Token()
		if err == io.EOF {
			return
		}
		if err != nil {
			fmt.Fprintf(os.Stderr, "xmlselect: %v\n", err)
			os.Exit(1)
		}
		switch tok := tok.(type) {
		case xml.StartElement:
			stack = append(stack, tok) // push
		case xml.EndElement:
			stack = stack[:len(stack)-1] // pop
		case xml.CharData:
			char := string(bytes.TrimSpace(tok))
			if char != "" && containsAll(stack, os.Args[1:]) {
				curElem := getStackElems(stack)
				fmt.Printf("%s: %s\n", curElem, char)
			}
		}
	}
}

func getStackElems(stack []xml.StartElement) string {
	var curElem string
	for _, s := range stack {
		curElem += s.Name.Local
		for _, a := range s.Attr {
			if a.Name.Local == "id" {
				curElem += "#" + a.Value
			}
			if a.Name.Local == "class" {
				curElem += "." + a.Value
			}
		}
		curElem += " "
	}
	return curElem
}

func getClassAndId(y string) (string, string) {
	id, class := "", ""
	if i := strings.Index(y, "#"); i != -1 {
		var r rune
		for {
			if len(y)-1 <= i {
				break
			}
			i++ // skip the #
			r = rune(y[i])
			if r == '.' || r == ' ' {
				break
			}
			id += string(r)
		}
	}
	if i := strings.Index(y, "."); i != -1 {
		var r rune
		for {
			if len(y)-1 <= i {
				break
			}
			i++ // skip the #
			r = rune(y[i])
			if r == '#' || r == ' ' {
				break
			}
			class += string(r)
		}
	}
	return id, class
}

func getName(y string) string {
	n := ""
	for _, r := range y {
		if r == ' ' || r == '.' || r == '#' {
			break
		}
		n += string(r)
	}
	return n
}

// containsAll reports whether x contains the elements of y, in order.
func containsAll(x []xml.StartElement, y []string) bool {
	for len(y) <= len(x) {
		if len(y) == 0 {
			return true
		}
		id, class := getClassAndId(y[0])
		name := getName(y[0])
		eName := x[0].Name.Local
		var eId string
		var eClass string
		for _, a := range x[0].Attr {
			if a.Name.Local == "id" {
				eId = a.Value
			}
			if a.Name.Local == "class" {
				eClass = a.Value
			}
		}
		if name == eName && ((id == "" || id == eId) && (class == "" || class == eClass)) {
			y = y[1:]
		}
		x = x[1:]
	}
	return false
}
