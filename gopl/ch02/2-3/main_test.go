package main

import (
	"testing"

	"github.com/jonathantorres/gopl/ch2/2-3/pcloop"
	"github.com/jonathantorres/gopl/ch2/2-3/popcount"
)

func BenchmarkPopCount(b *testing.B) {
	for i := 0; i < b.N; i++ {
		popcount.PopCount(uint64(i))
	}
}

func BenchmarkPopCountLoop(b *testing.B) {
	for i := 0; i < b.N; i++ {
		pcloop.PopCount(uint64(i))
	}
}
