package main

import (
	"fmt"
	"log"
	"net/http"
	"text/template"
)

type dollars float32

func (d dollars) String() string { return fmt.Sprintf("$%.2f", d) }

const html = `<html>
<head>
	<title>{{.PageTitle}}</title>
</head>
<body>
<style type="text/css">
table {
	border-collapse: collapse;
}
table, th, td {
	border: 1px solid black;
}
th, td {
	padding: 5px;
}
</style>
<p>{{.PageTitle}}</p>
<table>
	<thead>
		<tr>
			<th>Item Name</th>
			<th>Price</th>
		</tr>
	</thead>
	<tbody>
		{{range $item, $price := .Items}}
			<tr>
				<td>{{$item}}</td>
				<td>{{$price}}</td>
			</tr>
		{{end}}
	</tbody>
</table>
</body>
</html>
`

func main() {
	db := database{"shoes": 50, "socks": 5}
	http.HandleFunc("/list", db.list)
	http.HandleFunc("/price", db.price)
	log.Fatal(http.ListenAndServe("localhost:8000", nil))
}

type database map[string]dollars

func (db database) list(w http.ResponseWriter, req *http.Request) {
	tmpl, err := template.New("store").Parse(html)
	if err != nil {
		fmt.Fprintf(w, "error parsing template %s\n", err)
		return
	}
	data := struct {
		PageTitle string
		Items     database
	}{
		"Items on Stock",
		db,
	}

	err = tmpl.Execute(w, data)
	if err != nil {
		fmt.Fprintf(w, "error executing template %s\n", err)
		return
	}
}

func (db database) price(w http.ResponseWriter, req *http.Request) {
	item := req.URL.Query().Get("item")
	price, ok := db[item]
	if !ok {
		w.WriteHeader(http.StatusNotFound) // 404
		fmt.Fprintf(w, "no such item: %q\n", item)
		return
	}
	fmt.Fprintf(w, "%s\n", price)
}
