package main

import (
	"io"
	"net/http"
)

func main() {
	http.HandleFunc("/hello", hello)
	http.ListenAndServe(":9090", nil)
}

func hello(res http.ResponseWriter, req *http.Request) {
	res.Header().Set("Content-Type", "text/html")
	io.WriteString(res, `
<DOCTYPE html>
<head><title>Hello, World</title></head>
<body>
Hello,World!
</body>
</html>`)
}
