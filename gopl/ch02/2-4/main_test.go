package main

import (
	"testing"

	"github.com/jonathantorres/gopl/ch2/2-4/pcshift"
	"github.com/jonathantorres/gopl/ch2/2-4/popcount"
)

func BenchmarkPopCount(b *testing.B) {
	for i := 0; i < b.N; i++ {
		popcount.PopCount(uint64(i))
	}
}

func BenchmarkPopCountShift(b *testing.B) {
	for i := 0; i < b.N; i++ {
		pcshift.PopCount(uint64(i))
	}
}
