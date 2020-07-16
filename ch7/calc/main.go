package main

// Exercise 7.16

import (
	"fmt"
	"github.com/jonathantorres/gopl/ch7/eval"
	"log"
	"net/http"
)

type Handler struct{}

func (*Handler) ServeHTTP(resp http.ResponseWriter, req *http.Request) {
	resp.Header().Set("Content-Type", "text/html")
	exprStr := req.URL.Query().Get("expr")
	if exprStr == "" {
		fmt.Fprintf(resp, "An expression was not provided")
		return
	}
	expr, err := eval.Parse(exprStr)
	if err != nil {
		fmt.Fprintf(resp, "error parsing expr: %s", err)
		return
	}
	val := expr.Eval(eval.Env{})
	fmt.Fprintf(resp, "Result is %.2f", val)
}

func main() {
	var handler = Handler{}
	log.Fatal(http.ListenAndServe("localhost:9999", &handler))
}
