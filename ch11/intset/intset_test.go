package intset

// Exercise 11.2

import (
	"testing"
)

func TestHas(t *testing.T) {
	var tests = []struct {
		input int
		want  bool
	}{
		{1, true},
		{2, false},
		{3, false},
		{4, true},
		{5, true},
	}
	var x IntSet
	x.Add(1)
	x.Add(4)
	x.Add(5)
	for _, test := range tests {
		if got := x.Has(test.input); got != test.want {
			t.Errorf("x.Has(%d) = %t", test.input, got)
		}
	}
}

func TestAdd(t *testing.T) {
	var x IntSet
	x.Add(1)
	x.Add(4)
	x.Add(5)
	var y IntSet
	y.Add(6)
	y.Add(2)
	var z IntSet
	z.Add(9)
	var tests = []struct {
		input IntSet
		want  []int
	}{
		{input: x, want: []int{1, 4, 5}},
		{input: y, want: []int{2,6}},
		{input: z, want: []int{9}},
	}
	for _, test := range tests {
		for i, v := range test.input.Elems() {
			if v != test.want[i] {
				t.Errorf("input[%d] = %d, set[%d] = %d", i, test.want[i], i, v)
			}
		}
	}
}
