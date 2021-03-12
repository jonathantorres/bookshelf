package main

import (
	"fmt"
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

var palette = []color.Color{color.White, color.Black}

const (
	whiteIndex = 0 // first color in palette
	blackIndex = 1 // next color in palette
)

var (
	nframes int     = 64    // number of animation frames
	delay   int     = 8     // delay between frames in 10ms units
	size    int     = 100   // image canvas covers [-size..+size]
	cycles  float64 = 5.0   // number of complete x oscillator revolutions
	res     float64 = 0.001 // angular resolution
)

func main() {
	http.HandleFunc("/", handler)
	log.Fatal(http.ListenAndServe("localhost:8000", nil))
}

func handler(w http.ResponseWriter, r *http.Request) {
	if err := r.ParseForm(); err != nil {
		fmt.Fprintf(w, "%v", err)
		return
	}
	if c := r.Form.Get("cycles"); c != "" {
		f, err := strconv.ParseFloat(c, 64)
		if err == nil {
			cycles = f
		}
	}
	if rs := r.Form.Get("res"); rs != "" {
		f, err := strconv.ParseFloat(rs, 64)
		if err == nil {
			res = f
		}
	}
	if d := r.Form.Get("delay"); d != "" {
		i, err := strconv.Atoi(d)
		if err == nil {
			delay = i
		}
	}
	lissajous(w)
}

func lissajous(out io.Writer) {
	freq := rand.Float64() * 3.0 // relative frequency of y oscillator
	anim := gif.GIF{LoopCount: nframes}
	phase := 0.0 // phase difference
	for i := 0; i < nframes; i++ {
		rect := image.Rect(0, 0, 2*size+1, 2*size+1)
		img := image.NewPaletted(rect, palette)
		for t := 0.0; t < cycles*2*math.Pi; t += res {
			x := math.Sin(t)
			y := math.Sin(t*freq + phase)
			img.SetColorIndex(
				int(float64(size)+x*float64(size)+0.5),
				int(float64(size)+y*float64(size)+0.5),
				blackIndex,
			)
		}
		phase += 0.1
		anim.Delay = append(anim.Delay, delay)
		anim.Image = append(anim.Image, img)
	}
	gif.EncodeAll(out, &anim) // NOTE: ignoring encoding errors
}
