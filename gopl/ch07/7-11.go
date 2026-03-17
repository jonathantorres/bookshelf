package main

import (
	"fmt"
	"log"
	"net/http"
	"strconv"
)

type dollars float32

func (d dollars) String() string { return fmt.Sprintf("$%.2f", d) }

func main() {
	db := database{"shoes": 50, "socks": 5}
	http.HandleFunc("/list", db.list)
	http.HandleFunc("/create", db.create)
	http.HandleFunc("/read", db.read)
	http.HandleFunc("/update", db.update)
	http.HandleFunc("/delete", db.delete)
	log.Fatal(http.ListenAndServe("localhost:8000", nil))
}

type database map[string]dollars

func (db database) list(w http.ResponseWriter, req *http.Request) {
	for item, price := range db {
		fmt.Fprintf(w, "%s: %s\n", item, price)
	}
}

func (db database) update(w http.ResponseWriter, req *http.Request) {
	item := req.URL.Query().Get("item")
	price := req.URL.Query().Get("price")
	if _, ok := db[item]; !ok {
		fmt.Fprintf(w, "item: %q, does not exist\n", item)
		return
	}
	if price == "" {
		fmt.Fprintf(w, "a price for the item must be provided\n")
		return
	}
	f, err := strconv.ParseFloat(price, 64)
	if err != nil {
		fmt.Fprintf(w, "error retrieving the price %s\n", err)
		return
	}
	db[item] = dollars(f)
	fmt.Fprintf(w, "Item %s has been updated with a price of %v\n", item, dollars(f))
}

func (db database) create(w http.ResponseWriter, req *http.Request) {
	item := req.URL.Query().Get("item")
	price := req.URL.Query().Get("price")
	if _, ok := db[item]; ok {
		fmt.Fprintf(w, "item: %q, already exists\n", item)
		return
	}
	if item == "" {
		fmt.Fprintf(w, "an item must be specified\n")
		return
	}
	if price == "" {
		fmt.Fprintf(w, "a price for the item must be provided\n")
		return
	}
	f, err := strconv.ParseFloat(price, 64)
	if err != nil {
		fmt.Fprintf(w, "error retrieving the price %s\n", err)
		return
	}
	db[item] = dollars(f)
	fmt.Fprintf(w, "Item %s has been added with a price of %v\n", item, dollars(f))
}

func (db database) delete(w http.ResponseWriter, req *http.Request) {
	item := req.URL.Query().Get("item")
	_, ok := db[item]
	if !ok {
		w.WriteHeader(http.StatusNotFound) // 404
		fmt.Fprintf(w, "no such item: %q\n", item)
		return
	}
	delete(db, item)
	fmt.Fprintf(w, "item %s has been deleted\n", item)
}

func (db database) read(w http.ResponseWriter, req *http.Request) {
	item := req.URL.Query().Get("item")
	price, ok := db[item]
	if !ok {
		w.WriteHeader(http.StatusNotFound) // 404
		fmt.Fprintf(w, "no such item: %q\n", item)
		return
	}
	fmt.Fprintf(w, "%s\n", price)
}
