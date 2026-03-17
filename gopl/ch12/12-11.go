package main

import (
	"fmt"
	"log"
	"net/http"
	"reflect"
	"strings"
)

func main() {
	http.HandleFunc("/search", search)
	log.Fatal(http.ListenAndServe(":9090", nil))
}

// search implements the /search URL endpoint.
func search(resp http.ResponseWriter, req *http.Request) {
	var data struct {
		Labels     []string `http:"l"`
		MaxResults int      `http:"max"`
		Exact      bool     `http:"x"`
	}
	data.MaxResults = 10 // set default
	data.Exact = true
	data.Labels = []string{"one", "two", "three"}
	url, err := Pack(req, &data)
	if err != nil {
		http.Error(resp, err.Error(), http.StatusBadRequest) // 400
		return
	}
	fmt.Fprintf(resp, "Search: %s\n", url)
}

// Write the corresponding Pack function. Given a struct value, Pack should
// return a URL incorporating the parameter values from the struct.
func Pack(req *http.Request, ptr interface{}) (string, error) {
	var url strings.Builder
	url.WriteString(req.URL.Scheme)
	url.WriteString(req.URL.Host)
	url.WriteString(req.URL.Path)

	// Build map of fields keyed by query string key
	fields := make(map[string][]string)
	v := reflect.ValueOf(ptr).Elem() // the struct variable
	for i := 0; i < v.NumField(); i++ {
		var val []string
		field := v.Field(i)
		fieldInfo := v.Type().Field(i) // a reflect.StructField
		tag := fieldInfo.Tag           // a reflect.StructTag
		name := tag.Get("http")

		switch field.Kind() {
		case reflect.Invalid:
			name = ""
		case reflect.Int, reflect.Int8, reflect.Int16,
			reflect.Int32, reflect.Int64:
			val = append(val, fmt.Sprintf("%d", field.Int()))
		case reflect.Bool:
			val = append(val, fmt.Sprintf("%v", field.Bool()))
		case reflect.Slice:
			for i := 0; i < field.Len(); i++ {
				sv := field.Index(i)
				switch sv.Kind() { // only strings supported
				case reflect.String:
					val = append(val, sv.String())
				}
			}
		}
		if name == "" {
			continue
		}
		fields[name] = val
	}

	// build query string
	if len(fields) > 0 {
		url.WriteByte('?')
		for key, value := range fields {
			if len(value) == 1 {
				url.WriteString(key)
				url.WriteByte('=')
				url.WriteString(value[0])
				url.WriteByte('&')
			} else {
				for _, sv := range value {
					url.WriteString(key)
					url.WriteByte('=')
					url.WriteString(sv)
					url.WriteByte('&')
				}
			}
		}
	}

	return url.String(), nil
}
