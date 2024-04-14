package main

import (
	"fmt"
	"log"
	"math"
	"net/http"
	"strconv"
)

var (
	width   int     = 600                          // canvas width in pixels
	height          = 320                          // canvas height in pixels
	cells           = 100                          // number of grid cells
	xyrange float64 = 30.0                         // axis ranges (-xyrange..+xyrange)
	xyscale         = float64(width) / 2 / xyrange // pixels per x or y unit
	zscale          = float64(height) * 0.4        // pixels per z unit
	angle           = math.Pi / 6                  // angle of x, y axes (=30°)
	color           = "white"
	stroke          = "grey"
)

var sin30, cos30 = math.Sin(angle), math.Cos(angle) // sin(30°), cos(30°)

func main() {
	http.HandleFunc("/", handler)
	log.Fatal(http.ListenAndServe(":8000", nil))
}

func handler(w http.ResponseWriter, r *http.Request) {
	if err := r.ParseForm(); err != nil {
		fmt.Fprintf(w, "%v", err)
		return
	}
	if c := r.Form.Get("color"); c != "" {
		color = c
	}
	if s := r.Form.Get("stroke"); s != "" {
		stroke = s
	}
	if wi := r.Form.Get("width"); wi != "" {
		i, err := strconv.Atoi(wi)
		if err == nil {
			width = i
		}
	}
	if he := r.Form.Get("height"); he != "" {
		i, err := strconv.Atoi(he)
		if err == nil {
			height = i
		}
	}
	w.Header().Set("Content-Type", "image/svg+xml")
	fmt.Fprintf(w, "<svg xmlns='http://www.w3.org/2000/svg' "+
		"style='stroke: %s; fill: %s; stroke-width: 0.7' "+
		"width='%d' height='%d'>", stroke, color, width, height)
	for i := 0; i < cells; i++ {
		for j := 0; j < cells; j++ {
			ax, ay := corner(i+1, j)
			bx, by := corner(i, j)
			cx, cy := corner(i, j+1)
			dx, dy := corner(i+1, j+1)
			fmt.Fprintf(w, "<polygon points='%g,%g %g,%g %g,%g %g,%g'/>\n",
				ax, ay, bx, by, cx, cy, dx, dy)
		}
	}
	fmt.Fprintf(w, "</svg>")
}

func corner(i, j int) (float64, float64) {
	// Find point (x,y) at corner of cell (i,j).
	x := xyrange * (float64(i)/float64(cells) - 0.5)
	y := xyrange * (float64(j)/float64(cells) - 0.5)

	// Compute surface height z.
	z := f(x, y)

	// Project (x,y,z) isometrically onto 2-D SVG canvas (sx,sy).
	sx := float64(width)/2 + (x-y)*cos30*xyscale
	sy := float64(height)/2 + (x+y)*sin30*xyscale - z*zscale
	return sx, sy
}

func f(x, y float64) float64 {
	r := math.Hypot(x, y) // distance from (0,0)
	return math.Sin(r) / r
}
