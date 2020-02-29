package main

import (
	"fmt"
)

func main() {
	makeOdd := makeOddGenerator()

	fmt.Println(makeOdd())
	fmt.Println(makeOdd())
	fmt.Println(makeOdd())
}

func makeOddGenerator() func() uint {
	i := uint(1)
	return func() (ret uint) {
		ret = i
		i += 2
		return
	}
}
