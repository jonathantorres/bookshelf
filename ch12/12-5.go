package main

import (
	"bytes"
	"fmt"
	"os"
	"reflect"
)

type Movie struct {
	Title, Subtitle string
	Year            int
	Actor           map[string]string
	Oscars          []string
	Sequel          *string
}

func main() {
	strangelove := Movie{
		Title:    "Dr. Strangelove",
		Subtitle: "How I Learned to Stop Worrying and Love the Bomb",
		Year:     1964,
		Actor: map[string]string{
			"Dr. Strangelove":            "Peter Sellers",
			"Grp. Capt. Lionel Mandrake": "Peter Sellers",
			"Pres. Merkin Muffley":       "Peter Sellers",
			"Gen. Buck Turgidson":        "George C. Scott",
			"Brig. Gen. Jack D. Ripper":  "Sterling Hayden",
			`Maj. T.J. "King" Kong`:      "Slim Pickens",
		},
		Oscars: []string{
			"Best Actor (Nomin.)",
			"Best Adapted Screenplay (Nomin.)",
			"Best Director (Nomin.)",
			"Best Picture (Nomin.)",
		},
	}
	b, err := Marshal(strangelove)
	if err != nil {
		fmt.Fprintf(os.Stderr, "%s\n", err)
		os.Exit(1)
	}
	fmt.Println(string(b))
}

// Marshal encodes a Go value in JSON.
func Marshal(v interface{}) ([]byte, error) {
	var buf bytes.Buffer
	if err := encode(&buf, reflect.ValueOf(v)); err != nil {
		return nil, err
	}
	return buf.Bytes(), nil
}

// encode writes to buf a JSON representation of v.
func encode(buf *bytes.Buffer, v reflect.Value) error {
	switch v.Kind() {
	case reflect.Invalid:
		buf.WriteString("null")
	case reflect.Int, reflect.Int8, reflect.Int16,
		reflect.Int32, reflect.Int64:
		fmt.Fprintf(buf, "%d", v.Int())
	case reflect.Uint, reflect.Uint8, reflect.Uint16,
		reflect.Uint32, reflect.Uint64, reflect.Uintptr:
		fmt.Fprintf(buf, "%d", v.Uint())
	case reflect.Float32, reflect.Float64:
		fmt.Fprintf(buf, "%f", v.Float())
	case reflect.Complex64, reflect.Complex128:
		fmt.Fprintf(buf, "%f", v.Complex())
	case reflect.String:
		fmt.Fprintf(buf, "%q", v.String())
	case reflect.Bool:
		if v.Bool() {
			buf.WriteString("true")
		} else {
			buf.WriteString("false")
		}
	case reflect.Interface:
		fmt.Fprintf(buf, "{%q:", reflect.Indirect(v).Type())
		err := encode(buf, reflect.Indirect(v).Elem())
		if err != nil {
			return err
		}
		buf.WriteByte('}')
	case reflect.Ptr:
		return encode(buf, v.Elem())
	case reflect.Array, reflect.Slice: // (value ...)
		buf.WriteByte('[')
		for i := 0; i < v.Len(); i++ {
			if i > 0 {
				buf.WriteString(", ")
			}
			if err := encode(buf, v.Index(i)); err != nil {
				return err
			}
		}
		buf.WriteByte(']')
	case reflect.Struct: // ((name value) ...)
		buf.WriteByte('{')
		for i := 0; i < v.NumField(); i++ {
			fmt.Fprintf(buf, "%q:", v.Type().Field(i).Name)
			if err := encode(buf, v.Field(i)); err != nil {
				return err
			}
			if i < v.NumField()-1 {
				buf.WriteByte(',')
			}
		}
		buf.WriteByte('}')
	case reflect.Map: // ((key value) ...)
		buf.WriteByte('{')
		for i, key := range v.MapKeys() {
			if err := encode(buf, key); err != nil {
				return err
			}
			buf.WriteByte(':')
			if err := encode(buf, v.MapIndex(key)); err != nil {
				return err
			}
			if i < len(v.MapKeys())-1 {
				buf.WriteByte(',')
			}
		}
		buf.WriteByte('}')
	default: // chan, func
		return fmt.Errorf("unsupported type: %s", v.Type())
	}
	return nil
}
