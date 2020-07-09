package main

// Exercise 6.5

import (
	"bytes"
	"fmt"
)

const size = 32 << (^uint(0) >> 63)

type IntSet struct {
	words []uint
}

func (s *IntSet) Has(x int) bool {
	word, bit := x/size, uint(x%size)
	return int(word) < len(s.words) && s.words[word]&(1<<bit) != 0
}

func (s *IntSet) Add(x int) {
	word, bit := x/size, uint(x%size)
	for int(word) >= len(s.words) {
		s.words = append(s.words, 0)
	}
	s.words[word] |= 1 << bit
}

func (s *IntSet) UnionWith(t *IntSet) {
	for i, tword := range s.words {
		if i < len(s.words) {
			s.words[i] |= tword
		} else {
			s.words = append(s.words, tword)
		}
	}
}

func (s *IntSet) String() string {
	var buf bytes.Buffer
	buf.WriteByte('{')
	for i, word := range s.words {
		if word == 0 {
			continue
		}
		for j := 0; j < int(size); j++ {
			if word&(1<<uint(j)) != 0 {
				if buf.Len() > len("{") {
					buf.WriteByte(' ')
				}
				fmt.Fprintf(&buf, "%d", size*i+j)
			}
		}
	}
	buf.WriteByte('}')
	return buf.String()
}
