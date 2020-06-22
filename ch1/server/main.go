package main

// Exercise 1.12

import (
	"image"
	"image/color"
	"image/gif"
	"io"
	"log"
	"math"
	"math/rand"
	"net/http"
	"strconv"
)

var pallete = []color.Color{color.RGBA{0, 0, 0, 255}, color.RGBA{53, 168, 30, 255}}

const (
	whiteIndex = 0
	blackIndex = 1
)

var (
	cycles  = 5
	res     = 0.001
	size    = 100
	nframes = 64
	delay   = 8
)

func main() {
	http.HandleFunc("/", handler)
	log.Fatal(http.ListenAndServe("localhost:9090", nil))
}

func handler(w http.ResponseWriter, r *http.Request) {
	r.ParseForm()
	if r.Form.Get("cycles") != "" {
		val, err := strconv.Atoi(r.Form.Get("cycles"))
		if err == nil {
			cycles = val
		}
	}
	if r.Form.Get("size") != "" {
		val, err := strconv.Atoi(r.Form.Get("size"))
		if err == nil {
			size = val
		}
	}
	if r.Form.Get("delay") != "" {
		val, err := strconv.Atoi(r.Form.Get("delay"))
		if err == nil {
			delay = val
		}
	}
	if r.Form.Get("nframes") != "" {
		val, err := strconv.Atoi(r.Form.Get("nframes"))
		if err == nil {
			nframes = val
		}
	}
	lissajous(w)
}

func lissajous(out io.Writer) {
	freq := rand.Float64() * 3.0
	anim := gif.GIF{LoopCount: nframes}
	phase := 0.0
	for i := 0; i < nframes; i++ {
		rect := image.Rect(0, 0, 2*size+1, 2*size+1)
		img := image.NewPaletted(rect, pallete)
		for t := 0.0; t < float64(cycles)*2*math.Pi; t += res {
			x := math.Sin(t)
			y := math.Sin(t*freq + phase)
			img.SetColorIndex(size+int(x*float64(size)+0.5), size+int(y*float64(size)+0.5), blackIndex)
		}
		phase += 0.1
		anim.Delay = append(anim.Delay, delay)
		anim.Image = append(anim.Image, img)
	}
	gif.EncodeAll(out, &anim)
}
