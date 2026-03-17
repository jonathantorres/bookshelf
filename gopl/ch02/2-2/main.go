package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"

	"github.com/jonathantorres/gopl/ch2/2-1/tempconv"
	"github.com/jonathantorres/gopl/ch2/2-2/distconv"
	"github.com/jonathantorres/gopl/ch2/2-2/weightconv"
)

func main() {
	for _, arg := range os.Args[1:] {
		f, err := strconv.ParseFloat(arg, 64)
		if err != nil {
			fmt.Printf("%s could not be parsed\n", arg)
			continue
		}
		displayConversions(f)
	}
	if len(os.Args) == 1 {
		s := bufio.NewScanner(os.Stdin)
		for s.Scan() {
			l := s.Text()
			args := strings.Split(l, " ")
			for _, arg := range args {
				f, err := strconv.ParseFloat(arg, 64)
				if err != nil {
					fmt.Printf("%s could not be parsed\n", arg)
					continue
				}
				displayConversions(f)
				fmt.Println()
			}
		}
		if err := s.Err(); err != nil {
			fmt.Printf("error scanning: %s\n", err)
		}
	}
}

func displayConversions(v float64) {
	c := tempconv.Celsius(v)
	f := tempconv.Fahrenheit(v)
	k := tempconv.Kelvin(v)
	ft := distconv.Feet(v)
	mt := distconv.Meter(v)
	pd := weightconv.Pound(v)
	kl := weightconv.Kilogram(v)

	fmt.Printf("%s = %s\n", c, tempconv.CToF(c))
	fmt.Printf("%s = %s\n", c, tempconv.CToK(c))
	fmt.Printf("%s = %s\n", f, tempconv.FToC(f))
	fmt.Printf("%s = %s\n", f, tempconv.FToK(f))
	fmt.Printf("%s = %s\n", k, tempconv.KToC(k))
	fmt.Printf("%s = %s\n", k, tempconv.KToF(k))
	fmt.Printf("%s = %s\n", ft, distconv.FToMeters(ft))
	fmt.Printf("%s = %s\n", mt, distconv.MToFeet(mt))
	fmt.Printf("%s = %s\n", pd, weightconv.PToKilo(pd))
	fmt.Printf("%s = %s\n", kl, weightconv.KToPound(kl))
}
