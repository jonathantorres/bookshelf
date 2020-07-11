package main

// Exercise 7.3

import (
	"fmt"
	"strings"
)

type tree struct {
	value       int
	left, right *tree
}

func main() {
	var t *tree = nil
	t = add(t, 10)
	t = add(t, 4)
	t = add(t, 19)
	fmt.Println(t)
}

func (t *tree) String() string {
	var s strings.Builder
	fmt.Fprintf(&s, "{")
	addval(t, &s)
	fmt.Fprintf(&s, "}")
	return s.String()
}

func addval(t *tree, s *strings.Builder) {
	if t == nil {
		return
	}
	if t.left != nil {
		addval(t.left, s)
	}
	fmt.Fprintf(s, "%d,", t.value)
	if t.right != nil {
		addval(t.right, s)
	}
}

func Sort(values []int) {
	var root *tree
	for _, v := range values {
		root = add(root, v)
	}
	appendValues(values[:0], root)
}

func appendValues(values []int, t *tree) []int {
	if t != nil {
		values = appendValues(values, t.left)
		values = append(values, t.value)
		values = appendValues(values, t.right)
	}
	return values
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
