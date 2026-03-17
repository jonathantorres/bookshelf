package main

import (
	"testing"

	"github.com/jonathantorres/gopl/ch2/2-5/pcright"
	"github.com/jonathantorres/gopl/ch2/2-5/popcount"
)

func BenchmarkPopCount(b *testing.B) {
	for i := 0; i < b.N; i++ {
		popcount.PopCount(uint64(i))
	}
}

func BenchmarkPopCountRight(b *testing.B) {
	for i := 0; i < b.N; i++ {
		pcright.PopCount(uint64(i))
	}
}
