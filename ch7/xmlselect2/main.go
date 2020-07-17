package main

// Exercise 7.17

import (
	"encoding/xml"
	"fmt"
	"io"
	"os"
	"strings"
)

func main() {
	dec := xml.NewDecoder(os.Stdin)
	var stack []xml.StartElement
	for {
		tok, err := dec.Token()
		if err == io.EOF {
			break
		} else if err != nil {
			fmt.Fprintf(os.Stderr, "xmlselect: %v\n", err)
			os.Exit(1)
		}
		switch tok := tok.(type) {
		case xml.StartElement:
			stack = append(stack, tok) // push
		case xml.EndElement:
			stack = stack[:len(stack)-1] // pop
		case xml.CharData:
			if ok, matches := selectorMatches(stack, os.Args[1:]); ok {
				fmt.Printf("%s: %s\n", matches, tok)
			}
		}
	}
}

func getElemName(selector string) string {
	if strings.Contains(selector, ".") {
		return strings.Split(selector, ".")[0]
	}
	if strings.Contains(selector, "#") {
		return strings.Split(selector, "#")[0]
	}
	return selector
}

func hasSelector(elem xml.StartElement, selec string) bool {
	if !strings.Contains(selec, ".") && !strings.Contains(selec, "#") {
		return true
	}
	var idSelec string
	var classSelec string
	if strings.Contains(selec, ".") {
		classSelec = strings.Split(selec, ".")[1]
	}
	if strings.Contains(selec, "#") {
		idSelec = strings.Split(selec, "#")[1]
	}
	for _, attr := range elem.Attr {
		if idSelec != "" && attr.Name.Local == "id" && idSelec == attr.Value {
			return true
		}
		if classSelec != "" && attr.Name.Local == "class" && strings.Contains(attr.Value, classSelec) {
			return true
		}
	}
	return false
}

// containsAll reports whether x contains the elements of y, in order.
func selectorMatches(x []xml.StartElement, y []string) (bool, string) {
	var matches string
	for len(y) <= len(x) {
		if len(y) == 0 {
			return true, matches
		}
		if x[0].Name.Local == getElemName(y[0]) && hasSelector(x[0], y[0]) {
			matches += y[0] + " "
			y = y[1:]
		}
		x = x[1:]
	}
	return false, matches
}
