package main

import (
	"fmt"
	"reflect"
	"strconv"
)

type str struct {
	a int
	b int
}

func main() {
	a := [3]int{1, 2, 3}
	m := make(map[[3]int]bool)
	m[a] = true
	Display("map", m)
	fmt.Println()
	s := str{10, 20}
	m1 := make(map[str]bool)
	m1[s] = true
	Display("m1", m1)
}

func Display(name string, x interface{}) {
	fmt.Printf("Display %s (%T):\n", name, x)
	display(name, reflect.ValueOf(x))
}

// formatAtom formats a value without inspecting its internal structure.
// It is a copy of the the function in gopl.io/ch11/format.
func formatAtom(v reflect.Value) string {
	switch v.Kind() {
	case reflect.Invalid:
		return "invalid"
	case reflect.Int, reflect.Int8, reflect.Int16,
		reflect.Int32, reflect.Int64:
		return strconv.FormatInt(v.Int(), 10)
	case reflect.Uint, reflect.Uint8, reflect.Uint16,
		reflect.Uint32, reflect.Uint64, reflect.Uintptr:
		return strconv.FormatUint(v.Uint(), 10)
	case reflect.Bool:
		if v.Bool() {
			return "true"
		}
		return "false"
	case reflect.String:
		return strconv.Quote(v.String())
	case reflect.Chan, reflect.Func, reflect.Ptr,
		reflect.Slice, reflect.Map:
		return v.Type().String() + " 0x" +
			strconv.FormatUint(uint64(v.Pointer()), 16)
	default: // reflect.Array, reflect.Struct, reflect.Interface
		return v.Type().String() + " value"
	}
}

func display(path string, v reflect.Value) {
	switch v.Kind() {
	case reflect.Invalid:
		fmt.Printf("%s = invalid\n", path)
	case reflect.Slice, reflect.Array:
		for i := 0; i < v.Len(); i++ {
			display(fmt.Sprintf("%s[%d]", path, i), v.Index(i))
		}
	case reflect.Struct:
		for i := 0; i < v.NumField(); i++ {
			fieldPath := fmt.Sprintf("%s.%s", path, v.Type().Field(i).Name)
			display(fieldPath, v.Field(i))
		}
	case reflect.Map:
		for _, key := range v.MapKeys() {
			var kVal string
			if key.Kind() == reflect.Array || key.Kind() == reflect.Struct {
				kVal = formatAggr(key)
			} else {
				kVal = formatAtom(key)
			}
			display(fmt.Sprintf("%s[%s]", path, kVal), v.MapIndex(key))
		}
	case reflect.Ptr:
		if v.IsNil() {
			fmt.Printf("%s = nil\n", path)
		} else {
			display(fmt.Sprintf("(*%s)", path), v.Elem())
		}
	case reflect.Interface:
		if v.IsNil() {
			fmt.Printf("%s = nil\n", path)
		} else {
			fmt.Printf("%s.type = %s\n", path, v.Elem().Type())
			display(path+".value", v.Elem())
		}
	default: // basic types, channels, funcs
		fmt.Printf("%s = %s\n", path, formatAtom(v))
	}
}

func formatAggr(v reflect.Value) string {
	var format string
	if v.Kind() == reflect.Array {
		for i := 0; i < v.Len(); i++ {
			format += fmt.Sprintf("%v", v.Index(i)) + ","
		}
		return format
	}
	if v.Kind() == reflect.Struct {
		format += "{"
		for i := 0; i < v.NumField(); i++ {
			format += v.Type().Field(i).Name + ":" + fmt.Sprintf("%v", v.Field(i)) + ","
		}
		format += "}"
		return format
	}
	return "unknown"
}
