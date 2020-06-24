package main

// Exercise 3.4

import (
	"fmt"
	"log"
	"math"
	"net/http"
	"strconv"
)

var (
	width           = 600
	height          = 320
	stroke          = "grey"
	fill            = "white"
	xyscale float64 = float64(width / 2 / xyrange)
	zscale  float64 = float64(height) * 0.4
)

const (
	cells   = 100
	xyrange = 30.0
	angle   = math.Pi / 6
)

var sin30, cos30 = math.Sin(angle), math.Cos(angle)

func main() {
	http.HandleFunc("/", render)
	log.Fatal(http.ListenAndServe(":9090", nil))
}

func render(w http.ResponseWriter, r *http.Request) {
	r.ParseForm()
	if r.Form.Get("width") != "" {
		val, err := strconv.Atoi(r.Form.Get("width"))
		if err == nil {
			width = val
		}
	}
	if r.Form.Get("height") != "" {
		val, err := strconv.Atoi(r.Form.Get("height"))
		if err == nil {
			height = val
		}
	}
	if r.Form.Get("stroke") != "" {
		stroke = r.Form.Get("stroke")
	}
	if r.Form.Get("fill") != "" {
		fill = r.Form.Get("fill")
	}
	w.Header().Set("Content-Type", "image/svg+xml")
	fmt.Fprintf(w, "<svg xmlns='http://www.w3.org/2000/svg' "+"style='stroke:%s;fill:%s;stroke-width:0.7' "+"width='%d' height='%d'>", stroke, fill, width, height)
	for i := 0; i < cells; i++ {
		for j := 0; j < cells; j++ {
			ax, ay := corner(i+1, j)
			bx, by := corner(i, j)
			cx, cy := corner(i, j+1)
			dx, dy := corner(i+1, j+1)
			if math.IsNaN(ax) || math.IsNaN(ay) || math.IsNaN(bx) || math.IsNaN(by) || math.IsNaN(cx) || math.IsNaN(cy) || math.IsNaN(dx) || math.IsNaN(dy) {
				continue
			}
			fmt.Fprintf(w, "<polygon points='%g,%g,%g,%g,%g,%g,%g,%g'/>\n", ax, ay, bx, by, cx, cy, dx, dy)
		}
	}
	fmt.Fprintf(w, "</svg>")
}

func corner(i, j int) (float64, float64) {
	x := xyrange * (float64(i)/cells - 0.5)
	y := xyrange * (float64(j)/cells - 0.5)
	z := f(x, y)
	sx := float64(width)/2 + (x-y)*cos30*xyscale
	sy := float64(height)/2 + (x+y)*sin30*xyscale - z*zscale
	return sx, sy
}

func f(x, y float64) float64 {
	r := math.Hypot(x, y)
	return math.Sin(r)
}
