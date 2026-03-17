package main

import (
	"fmt"
	"log"
	"net/http"

	"github.com/jonathantorres/gopl/ch7/eval"
)

func main() {
	http.HandleFunc("/", index)
	log.Fatal(http.ListenAndServe("localhost:8888", nil))
}

func index(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "text/html")
	e := r.FormValue("e")
	if e == "" {
		fmt.Fprintf(w, "an expression must be provided")
		return
	}
	exp, err := eval.Parse(e)
	if err != nil {
		fmt.Fprintf(w, "parse error %s\n", err)
		return
	}
	err = exp.Check(nil)
	if err != nil {
		fmt.Fprintf(w, "check error %s\n", err)
		return
	}
	fmt.Fprintf(w, "%s = %v\n", eval.Format(exp), exp.Eval(nil))
}
