package main

import (
	"flag"
	"fmt"
	"image"
	"image/gif"
	"image/jpeg"
	"image/png"
	"io"
	"os"
)

var output = flag.String("o", "jpeg", "output format")

func main() {
	flag.Parse()
	if err := convert(os.Stdin, os.Stdout); err != nil {
		fmt.Fprintf(os.Stderr, "jpeg: %v\n", err)
		os.Exit(1)
	}
}

func convert(in io.Reader, out io.Writer) error {
	img, _, err := image.Decode(in)
	if err != nil {
		return err
	}
	switch *output {
	case "png":
		return png.Encode(out, img)
	case "jpeg", "jpg":
		return jpeg.Encode(out, img, &jpeg.Options{Quality: 95})
	case "gif":
		return gif.Encode(out, img, &gif.Options{NumColors: 256})
	}
	return fmt.Errorf("%s format not supported", *output)
}
