package main

import (
	"fmt"
	"reflect"
	"unsafe"
)

type list struct {
	v int
	n *list
}

type msg string

func main() {
	a := msg("Hello, world")
	b := list{1, nil}
	c := list{2, &list{3, &list{4, &b}}}
	b.n = &c
	fmt.Println(Cyclic(a))
	fmt.Println(Cyclic(b))
}

func Cyclic(x interface{}) bool {
	seen := make(map[ptr]bool)
	return cyclic(reflect.ValueOf(x), seen)
}

type ptr struct {
	x unsafe.Pointer
	t reflect.Type
}

func cyclic(x reflect.Value, seen map[ptr]bool) bool {
	if x.CanAddr() {
		p := ptr{unsafe.Pointer(x.UnsafeAddr()), x.Type()}
		if seen[p] {
			return true // already seen
		}
		seen[p] = true
	}
	switch x.Kind() {
	case reflect.Ptr, reflect.Interface:
		return cyclic(x.Elem(), seen)
	case reflect.Array, reflect.Slice:
		for i := 0; i < x.Len(); i++ {
			if cyclic(x.Index(i), seen) {
				return true
			}
		}
		return false
	case reflect.Struct:
		for i, n := 0, x.NumField(); i < n; i++ {
			if cyclic(x.Field(i), seen) {
				return true
			}
		}
		return false
	case reflect.Map:
		for _, k := range x.MapKeys() {
			if cyclic(x.MapIndex(k), seen) || cyclic(k, seen) {
				return true
			}
		}
		return false
	default:
		return false
	}
	panic("unreachable")
}
