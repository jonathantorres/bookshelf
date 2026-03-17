package main

import (
	"fmt"
	"log"
	"net/http"
	"reflect"
	"regexp"
	"strconv"
	"strings"
)

func main() {
	http.HandleFunc("/search", search)
	log.Fatal(http.ListenAndServe(":9090", nil))
}

var emailRegex = regexp.MustCompile("^[a-zA-Z0-9.!#$%&'*+\\/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$")
var ccRegex = regexp.MustCompile(`^(?:4[0-9]{12}(?:[0-9]{3})?|[25][1-7][0-9]{14}|6(?:011|5[0-9][0-9])[0-9]{12}|3[47][0-9]{13}|3(?:0[0-5]|[68][0-9])[0-9]{11}|(?:2131|1800|35\d{3})\d{11})$`)

type urlParam struct {
	v reflect.Value
	r string
}

func (u *urlParam) validate(value string) error {
	if u.r == "" {
		return nil // no validation needed
	}
	if u.r == "email" {
		return u.validateEmail(value)
	}
	if u.r == "cc" {
		return u.validateCC(value)
	}
	return nil
}

func (u *urlParam) validateEmail(email string) error {
	if u.v.Kind() != reflect.String {
		return fmt.Errorf("%s is not a supported type", u.v.Type().Name())
	}
	if ok := emailRegex.MatchString(email); !ok {
		return fmt.Errorf("%s is not a valid email", email)
	}
	return nil
}

func (u *urlParam) validateCC(cc string) error {
	if u.v.Kind() != reflect.String {
		return fmt.Errorf("%s is not a supported type", u.v.Type().Name())
	}
	if ok := ccRegex.MatchString(cc); !ok {
		return fmt.Errorf("%s is not a valid credit card number", cc)
	}
	return nil
}

// search implements the /search URL endpoint.
func search(resp http.ResponseWriter, req *http.Request) {
	var data struct {
		Labels     []string `http:"l"`
		Email      string   `http:"e" rule:"email"`
		MaxResults int      `http:"max"`
		Exact      bool     `http:"x"`
		Card       string   `http:"c" rule:"cc"`
	}
	data.MaxResults = 10 // set default
	if err := Unpack(req, &data); err != nil {
		http.Error(resp, err.Error(), http.StatusBadRequest) // 400
		return
	}
	fmt.Fprintf(resp, "Search: %+v\n", data)
}

// Unpack populates the fields of the struct pointed to by ptr
// from the HTTP request parameters in req.
func Unpack(req *http.Request, ptr interface{}) error {
	if err := req.ParseForm(); err != nil {
		return err
	}

	// Build map of fields keyed by effective name.
	fields := make(map[string]urlParam)
	v := reflect.ValueOf(ptr).Elem() // the struct variable
	for i := 0; i < v.NumField(); i++ {
		fieldInfo := v.Type().Field(i) // a reflect.StructField
		tag := fieldInfo.Tag           // a reflect.StructTag
		name := tag.Get("http")
		if name == "" {
			name = strings.ToLower(fieldInfo.Name)
		}
		fields[name] = urlParam{
			v: v.Field(i),
			r: tag.Get("rule"),
		}
	}

	// Update struct field for each parameter in the request.
	for name, values := range req.Form {
		p := fields[name]
		if !p.v.IsValid() {
			continue // ignore unrecognized HTTP parameters
		}
		for _, value := range values {
			if p.v.Kind() == reflect.Slice {
				if err := p.validate(value); err != nil {
					return fmt.Errorf("%s: %v", name, err)
				}
				elem := reflect.New(p.v.Type().Elem()).Elem()
				if err := populate(elem, value); err != nil {
					return fmt.Errorf("%s: %v", name, err)
				}
				p.v.Set(reflect.Append(p.v, elem))
			} else {
				if err := p.validate(value); err != nil {
					return fmt.Errorf("%s: %v", name, err)
				}
				if err := populate(p.v, value); err != nil {
					return fmt.Errorf("%s: %v", name, err)
				}
			}
		}
	}
	return nil
}

func populate(v reflect.Value, value string) error {
	switch v.Kind() {
	case reflect.String:
		v.SetString(value)
	case reflect.Int:
		i, err := strconv.ParseInt(value, 10, 64)
		if err != nil {
			return err
		}
		v.SetInt(i)
	case reflect.Bool:
		b, err := strconv.ParseBool(value)
		if err != nil {
			return err
		}
		v.SetBool(b)
	default:
		return fmt.Errorf("unsupported kind %s", v.Type())
	}
	return nil
}
