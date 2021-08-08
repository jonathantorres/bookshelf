package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	var a int
	mscanf("%d\n", &a)
	fmt.Printf("%d\n", a)
}

func mscanf(fm string, ap ...interface{}) int {
	var c byte
	var err error
	var j int
	var count int
	r := bufio.NewReader(os.Stdin)
	for i, p := range fm {
		if i > 0 && fm[i-1] == '%' {
			continue
		}
		if p != '%' {
			c, err = r.ReadByte()
			if err != nil {
				keep_reading()
				return 0
			}
			if rune(c) != p {
				keep_reading()
				return 0
			} else {
				continue
			}
		}
		v := ap[j]
		switch fm[i+1] {
		case 'd':
			co, err := fmt.Scanf("%d", v.(*int))
			if err != nil {
				return 0
			}
			count += co
			j++
			break
		case 'f':
			co, err := fmt.Scanf("%lf", v.(*float64))
			if err != nil {
				return 0
			}
			count += co
			j++
			break
		case 's':
			co, err := fmt.Scanf("%s", v.(*string))
			if err != nil {
				return 0
			}
			count += co
			j++
			break
		default:
			fmt.Printf("wrong format!")
			return 0
		}
	}
	return count
}

func keep_reading() {
	var c byte
	var err error
	r := bufio.NewReader(os.Stdin)
	for {
		c, err = r.ReadByte()
		if err != nil {
			break
		}
		if rune(c) == '\n' {
			break
		}
	}
}
