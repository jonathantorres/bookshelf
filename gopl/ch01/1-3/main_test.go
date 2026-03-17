package main

import (
	"os"
	"testing"
)

var args []string = []string{
	"prog",
	"one",
	"two",
	"three",
}

func BenchmarkEcho1(b *testing.B) {
	out, err := os.Open(os.DevNull)
	if err != nil {
		b.Fatal(err)
	}
	defer out.Close()
	for i := 0; i < b.N; i++ {
		echo1(out, args)
	}
}

func BenchmarkEcho2(b *testing.B) {
	out, err := os.Open(os.DevNull)
	if err != nil {
		b.Fatal(err)
	}
	defer out.Close()
	for i := 0; i < b.N; i++ {
		echo2(out, args)
	}
}

func BenchmarkEcho3(b *testing.B) {
	out, err := os.Open(os.DevNull)
	if err != nil {
		b.Fatal(err)
	}
	defer out.Close()
	for i := 0; i < b.N; i++ {
		echo3(out, args)
	}
}
