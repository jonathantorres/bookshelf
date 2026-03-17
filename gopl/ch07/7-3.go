package main

import (
	"bytes"
	"fmt"
	"strconv"
)

type tree struct {
	value       int
	left, right *tree
}

func main() {
	t := add(nil, 1)
	add(t, 2)
	add(t, 3)
	add(t, 4)
	fmt.Println(t)
}

func add(t *tree, value int) *tree {
	if t == nil {
		// Equivalent to return &tree{value: value}.
		t = new(tree)
		t.value = value
		return t
	}
	if value < t.value {
		t.left = add(t.left, value)
	} else {
		t.right = add(t.right, value)
	}
	return t
}

func (t *tree) String() string {
	if t == nil {
		return "<nil>"
	}
	b := &bytes.Buffer{}
	b.WriteString("{")
	writeVal(b, t)
	b.WriteString("}")
	return b.String()
}

func writeVal(b *bytes.Buffer, t *tree) {
	if t == nil {
		return
	}
	writeVal(b, t.left)
	b.WriteString(strconv.Itoa(t.value) + ",")
	writeVal(b, t.right)
}

// Sort sorts values in place.
func Sort(values []int) {
	var root *tree
	for _, v := range values {
		root = add(root, v)
	}
	appendValues(values[:0], root)
}

// appendValues appends the elements of t to values in order
// and returns the resulting slice.
func appendValues(values []int, t *tree) []int {
	if t != nil {
		values = appendValues(values, t.left)
		values = append(values, t.value)
		values = appendValues(values, t.right)
	}
	return values
}
