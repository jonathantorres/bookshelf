package main

// Exercise 11.1

import (
	"bufio"
	"strings"
	"testing"
	"unicode/utf8"
)

type testExp struct {
	input   *bufio.Reader
	wantMap map[string]int
	wantUtf [utf8.UTFMax + 1]int
	wantInv int
	err     error
}

func TestCharcount(t *testing.T) {
	wantMap := map[string]int{
		"space":   1,
		"letters": 4,
	}
	var wantUtf [utf8.UTFMax + 1]int = [utf8.UTFMax + 1]int{0, 5, 0, 0, 0}
	var tests = []testExp{
		{
			bufio.NewReader(strings.NewReader("hello")),
			wantMap,
			wantUtf,
			0,
			nil,
		},
	}
	for _, test := range tests {
		gotCounts, gotUtf, gotInv, gotErr := charcount(test.input)
		if gotErr != nil {
			t.Errorf("charcount(%v) = %v, %v, %v", test.input, gotCounts, gotUtf, gotInv)
			continue
		}
		if gotInv != test.wantInv {
			t.Errorf("charcount(%v) = %v, %v, %v", test.input, gotCounts, gotUtf, gotInv)
		}
		for i, n := range test.wantUtf {
			if gotUtf[i] != n {
				t.Errorf("value %d from index %d is not equal to %d in utf array", n, i, gotUtf[i])
			}
		}
		// if gotCounts != test.wantMap {
		// 	t.Errorf("charcount(%s) = %v, %v, %v", test.input, gotCounts, gotUtf, gotInv)
		// }
	}
}
