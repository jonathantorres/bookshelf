package main

// Exercise 7.11
// Exercise 7.12

import (
	"fmt"
	"html/template"
	"log"
	"net/http"
	"strconv"
)

type dollars float64

func (d dollars) String() string {
	return fmt.Sprintf("$%.2f", d)
}

type database map[string]dollars

type Store struct {
	Title string
	Items database
}

var listTmpl = `
<html>
	<head>
		<title>{{.Title}}</title>
		<style>
		table {
			font-family: arial, sans-serif;
			border-collapse: collapse;
			width: 800px;
		}
		td, th {
			border: 1px solid #dddddd;
			text-align: left;
			padding: 8px;
		}
		</style>
	</head>
	<body>
		<h1>{{.Title}}</h1>
		<table>
			<thead>
				<tr>
					<th>Item</th>
					<th>Price</th>
				</tr>
			</thead>
			<tbody>
				{{ range $item, $price := .Items}}
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

func (db database) list(w http.ResponseWriter, req *http.Request) {
	w.Header().Set("Content-Type", "text/html")
	tmpl, err := template.New("prices").Parse(listTmpl)
	if err != nil {
		fmt.Fprintf(w, "error rendering template %s", err)
		return
	}
	store := Store{
		Title: "Store Items",
		Items: db,
	}
	err = tmpl.Execute(w, store)
	if err != nil {
		fmt.Fprintf(w, "error executing template %s", err)
	}
}

func (db database) price(w http.ResponseWriter, req *http.Request) {
	w.Header().Set("Content-Type", "text/html")
	item := req.URL.Query().Get("item")
	price, ok := db[item]
	if !ok {
		w.WriteHeader(http.StatusNotFound)
		fmt.Fprintf(w, "no such item: %q", item)
		return
	}
	fmt.Fprintf(w, "%s", price)
}

func (db database) create(w http.ResponseWriter, req *http.Request) {
	w.Header().Set("Content-Type", "text/html")
	item := req.URL.Query().Get("item")
	price := req.URL.Query().Get("price")
	if item == "" || price == "" {
		w.WriteHeader(http.StatusNotFound)
		fmt.Fprintf(w, "item not created an item name and a price must be provided")
		return
	}
	pri, err := strconv.ParseFloat(price, 64)
	if err != nil {
		fmt.Fprintf(w, "item not created: %s", err)
		return
	}
	db[item] = dollars(pri)
	fmt.Fprintf(w, "Added %s for %s", item, dollars(pri))
}

func (db database) update(w http.ResponseWriter, req *http.Request) {
	w.Header().Set("Content-Type", "text/html")
	item := req.URL.Query().Get("item")
	price := req.URL.Query().Get("price")
	if item == "" || price == "" {
		w.WriteHeader(http.StatusNotFound)
		fmt.Fprintf(w, "item not updated, an item name and a price must be provided")
		return
	}
	_, ok := db[item]
	if !ok {
		w.WriteHeader(http.StatusNotFound)
		fmt.Fprintf(w, "item not updated, the item %s could not be found", item)
		return
	}
	pri, err := strconv.ParseFloat(price, 64)
	if err != nil {
		fmt.Fprintf(w, "item %s was not updated: %s", item, err)
		return
	}
	db[item] = dollars(pri)
	fmt.Fprintf(w, "item %s has been updated!", item)
}

func (db database) delete(w http.ResponseWriter, req *http.Request) {
	w.Header().Set("Content-Type", "text/html")
	item := req.URL.Query().Get("item")
	if item == "" {
		w.WriteHeader(http.StatusNotFound)
		fmt.Fprintf(w, "item not deleted, an item name must be provided")
		return
	}
	_, ok := db[item]
	if !ok {
		w.WriteHeader(http.StatusNotFound)
		fmt.Fprintf(w, "item not deleted, the item %s could not be found", item)
		return
	}
	delete(db, item)
	fmt.Fprintf(w, "item %s is now deleted!", item)
}

func main() {
	db := database{
		"shoes": 50,
		"socks": 5,
	}
	mux := http.NewServeMux()
	mux.Handle("/list", http.HandlerFunc(db.list))
	mux.Handle("/price", http.HandlerFunc(db.price))
	mux.Handle("/create", http.HandlerFunc(db.create))
	mux.Handle("/update", http.HandlerFunc(db.update))
	mux.Handle("/delete", http.HandlerFunc(db.delete))
	log.Fatal(http.ListenAndServe("localhost:9999", mux))
}
