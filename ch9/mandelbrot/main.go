package main

// Exercise 9.6

import (
	"image"
	"image/color"
	"image/png"
	"math/cmplx"
	"os"
	"runtime"
	"sync"
)

const (
	xmin, ymin, xmax, ymax = -2, -2, +2, +2
	width, height          = 1024, 1024
)

func main() {
	workers := runtime.GOMAXPROCS(-1)
	img := image.NewRGBA(image.Rect(0, 0, width, height))
	wg := sync.WaitGroup{}
	rows := make(chan int, height)
	for row := 0; row < height; row++ {
		rows <- row
	}
	close(rows)
	for i := 0; i < workers; i++ {
		wg.Add(1)
		go func() {
			for py := range rows {
				y := float64(py)/height*(ymax-ymin) + ymin
				for px := 0; px < width; px++ {
					x := float64(px)/width*(xmax-xmin) + xmin
					z := complex(x, y)
					img.Set(px, py, mandelbrot(z))
				}
			}
			wg.Done()
		}()
	}
	wg.Wait()
	png.Encode(os.Stdout, img)
}

func mandelbrot(z complex128) color.Color {
	const iterations = 200
	const contrast = 15
	var v complex128
	for n := uint8(0); n < iterations; n++ {
		v = v*v + z
		if cmplx.Abs(v) > 2 {
			return color.Gray{255 - contrast*n}
		}
	}
	return color.Black
}
