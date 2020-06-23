package main

// Exercise 2.2

import (
	"bufio"
	"fmt"
	"github.com/jonathantorres/gopl/ch2/distconv"
	"github.com/jonathantorres/gopl/ch2/tempconv"
	"github.com/jonathantorres/gopl/ch2/weightconv"
	"os"
	"strconv"
	"strings"
)

func main() {
	if len(os.Args) > 1 {
		for _, arg := range os.Args[1:] {
			num, err := strconv.ParseFloat(arg, 64)
			if err != nil {
				continue
			}
			displayConversions(num)
		}
		return
	}
	// read from stdin
	reader := bufio.NewReader(os.Stdin)
	str, err := reader.ReadString('\n')
	if err != nil {
		fmt.Println("Error reading input")
		return
	}
	var parts []string = strings.Split(str, " ")
	for _, num := range parts {
		num, err := strconv.ParseFloat(num, 64)
		if err != nil {
			continue
		}
		displayConversions(num)
	}
}

func displayConversions(num float64) {
	fmt.Printf("%v = %v\n", tempconv.Celsius(num), tempconv.CToF(tempconv.Celsius(num)))
	fmt.Printf("%v = %v\n", tempconv.Fahrenheit(num), tempconv.FToC(tempconv.Fahrenheit(num)))
	fmt.Printf("%v = %v\n", distconv.Feet(num), distconv.FToMeters(distconv.Feet(num)))
	fmt.Printf("%v = %v\n", distconv.Meter(num), distconv.MToFeet(distconv.Meter(num)))
	fmt.Printf("%v = %v\n", weightconv.Pound(num), weightconv.PToKilo(weightconv.Pound(num)))
	fmt.Printf("%v = %v\n", weightconv.Kilogram(num), weightconv.KToPound(weightconv.Kilogram(num)))
	fmt.Println()
}
