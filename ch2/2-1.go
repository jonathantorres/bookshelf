package main

import (
	"fmt"
	"math"
	"unsafe"
)

func main() {
	fmt.Println("Max ranges:")
	fmt.Printf("rune:\t\t %d\n", math.MaxInt32)
	fmt.Printf("int8:\t\t %d\n", math.MaxInt8)
	fmt.Printf("int32:\t\t %d\n", math.MaxInt32)
	fmt.Printf("uint32:\t\t %d\n", math.MaxUint32)
	fmt.Printf("int64:\t\t %d\n", math.MaxInt64)
	fmt.Printf("float32:\t\t %f\n", math.MaxFloat32)
	fmt.Printf("float64:\t\t %f\n", math.MaxFloat64)

	fmt.Println("")
	fmt.Println("Sizes:")
	fmt.Printf("rune:\t\t %d\n", unsafe.Sizeof(rune(0)))
	fmt.Printf("int8:\t\t %d\n", unsafe.Sizeof(int8(0)))
	fmt.Printf("int32:\t\t %d\n", unsafe.Sizeof(int32(0)))
	fmt.Printf("uint32:\t\t %d\n", unsafe.Sizeof(uint32(0)))
	fmt.Printf("int64:\t\t %d\n", unsafe.Sizeof(int64(0)))
	fmt.Printf("float32:\t\t %d\n", unsafe.Sizeof(float32(0)))
	fmt.Printf("float64:\t\t %d\n", unsafe.Sizeof(float64(0)))
}
