package split

// Exercise 11.5

import (
	"strings"
	"testing"
)

func TestSplit(t *testing.T) {
	var tests = []struct {
		input string
		sep   string
		want  int
	}{
		{"a:b:c", ":", 3},
		{"one,two", ",", 2},
		{"one,", ",", 2},
		{"1|2|3|4|5", "|", 5},
	}
	for _, test := range tests {
		words := strings.Split(test.input, test.sep)
		if got, want := len(words), test.want; got != want {
			t.Errorf("Split(%q, %q) returned %d words, want %d", test.input, test.sep, got, want)
		}
	}
}
