package main

import (
	"reflect"
	"strings"
	"testing"
	"unicode/utf8"
)

func TestCharcount(t *testing.T) {
	tests := []struct {
		input string
		want  *Counts
	}{
		{
			input: "Jonathan Torres\n",
			want: &Counts{
				un: map[rune]int{
					'\n': 1,
					'J':  1,
					'o':  2,
					'n':  2,
					'a':  2,
					't':  1,
					'h':  1,
					' ':  1,
					'T':  1,
					'r':  2,
					'e':  1,
					's':  1,
				},
				utf: [utf8.UTFMax + 1]int{0, 16, 0, 0, 0},
				inv: 0,
			},
		},
		{
			input: "hello",
			want: &Counts{
				un: map[rune]int{
					'h': 1,
					'e': 1,
					'l': 2,
					'o': 1,
				},
				utf: [utf8.UTFMax + 1]int{0, 5, 0, 0, 0},
				inv: 0,
			},
		},
		{
			input: "Zerdrücken",
			want: &Counts{
				un: map[rune]int{
					'Z': 1,
					'e': 2,
					'r': 2,
					'd': 1,
					'ü': 1,
					'c': 1,
					'k': 1,
					'n': 1,
				},
				utf: [utf8.UTFMax + 1]int{0, 9, 1, 0, 0},
				inv: 0,
			},
		},
	}
	for _, test := range tests {
		res, err := charcount(strings.NewReader(test.input))
		if err != nil {
			t.Fatalf("%s", err)
		}
		if !reflect.DeepEqual(res, test.want) {
			t.Errorf("expected %v, got %v", test.want, res)
		}
	}
}
