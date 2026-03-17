package main

import (
	"io"
	"io/ioutil"
	"log"
	"os"
	"os/exec"
)

func main() {
	w := NewWriter(os.Stdout)
	if _, err := io.Copy(w, os.Stdin); err != nil {
		log.Fatalf("bzip: %v\n", err)
	}
	if err := w.Close(); err != nil {
		log.Fatalf("bzip: close: %v\n", err)
	}
}

type writer struct {
	w io.Writer // underlying output stream
}

func NewWriter(out io.Writer) io.WriteCloser {
	return &writer{w: out}
}

func (w *writer) Write(data []byte) (int, error) {
	var total int
	tmp, err := ioutil.TempFile("", "bzip")
	if err != nil {
		return 0, err
	}
	if total, err = tmp.Write(data); err != nil {
		return 0, err
	}
	tmp.Close()
	cmd := exec.Command("bzip2", tmp.Name())
	if err = cmd.Run(); err != nil {
		return 0, err
	}
	f, err := ioutil.ReadFile(tmp.Name() + ".bz2")
	if err != nil {
		return 0, err
	}
	_, err = w.w.Write(f)
	if err != nil {
		return 0, nil
	}

	return total, nil
}

func (w *writer) Close() error {
	return nil
}
