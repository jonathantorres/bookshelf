package main

// Exercise 10.1

import (
	"fmt"
	"flag"
	"image"
	"image/jpeg"
	"image/png"
	"image/gif"
	"io"
	"os"
)

var outF = flag.String("format", "jpeg", "Output format")
type ConvFunc func(in io.Reader, out io.Writer) error

func main() {
	flag.Parse()
	var convFunc ConvFunc
	switch *outF {
	case "jpeg", "jpg":
		convFunc = toJPEG
	case "png":
		convFunc = toPNG
	case "gif":
		convFunc = toGIF
	default:
		fmt.Fprintf(os.Stderr, "Output format %s not supported\n", *outF)
		os.Exit(1)
	}
	if err := convFunc(os.Stdin, os.Stdout); err != nil {
		fmt.Fprintf(os.Stderr, "jpeg: %v\n", err)
		os.Exit(1)
	}
}

func toGIF(in io.Reader, out io.Writer) error {
	img, kind, err := image.Decode(in)
	if err != nil {
		return err
	}
	fmt.Fprintln(os.Stderr, "Input format =", kind)
	return gif.Encode(out, img, &gif.Options{NumColors: 255})
}

func toPNG(in io.Reader, out io.Writer) error {
	img, kind, err := image.Decode(in)
	if err != nil {
		return err
	}
	fmt.Fprintln(os.Stderr, "Input format =", kind)
	return png.Encode(out, img)
}

func toJPEG(in io.Reader, out io.Writer) error {
	img, kind, err := image.Decode(in)
	if err != nil {
		return err
	}
	fmt.Fprintln(os.Stderr, "Input format =", kind)
	return jpeg.Encode(out, img, &jpeg.Options{Quality: 95})
}
