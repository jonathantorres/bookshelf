package main

import "fmt"

func main() {
	miniprintf("This is the letter %c\n", 's')
}

func miniprintf(fm string, ap ...interface{}) {
	var j int
	for i, p := range fm {
		if i > 0 && fm[i-1] == '%' {
			continue
		}
		if p != '%' {
			fmt.Printf("%c", p)
			continue
		}
		v := ap[j]
		switch fm[i+1] {
		case 'i', 'd':
			fmt.Printf("%d", v.(int))
			j++
			break
		case 'o':
			fmt.Printf("%o", v.(int))
			j++
			break
		case 'X', 'x':
			fmt.Printf("%x", v.(int))
			j++
			break
		case 'u':
			fmt.Printf("%u", v.(int))
			j++
			break
		case 'c':
			fmt.Printf("%c", v.(rune))
			j++
			break
		case 'G', 'g', 'E', 'e', 'f':
			fmt.Printf("%f", v.(float64))
			j++
			break
		case 's':
			fmt.Printf("%s", v.(string))
			j++
			break
		default:
			fmt.Printf("%v", v)
			j++
			break

		}
	}
}
