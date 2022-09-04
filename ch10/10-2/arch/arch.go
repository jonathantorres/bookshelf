package arch

import (
	"archive/tar"
	"archive/zip"
	"errors"
	"fmt"
	"io"
	"os"
	"strings"
)

type Archiver struct {
	format  string
	zReader *zip.ReadCloser
	tReader *os.File
	Files   []string
}

func (a *Archiver) Close() error {
	if a.format == "zip" {
		return a.zReader.Close()
	} else if a.format == "tar" {
		return a.tReader.Close()
	}
	return fmt.Errorf("format %s not suppored", a.format)
}

var archives map[string]bool

func init() {
	archives = make(map[string]bool)
}

func Open(file string) (*Archiver, error) {
	archType := ""
	if strings.HasSuffix(file, "tar") {
		archType = "tar"
	} else if strings.HasSuffix(file, "zip") {
		archType = "zip"
	}

	found := false
	for k := range archives {
		if k == archType {
			found = true
		}
	}
	if !found {
		return nil, errors.New("archive type not supported")
	}
	a := Archiver{format: archType}
	files := make([]string, 0, 10)
	if archType == "zip" {
		r, err := zip.OpenReader(file)
		if err != nil {
			return nil, err
		}
		for _, f := range r.File {
			files = append(files, f.Name)
		}
	} else if archType == "tar" {
		r, err := os.Open(file)
		if err != nil {
			return nil, err
		}
		tr := tar.NewReader(r)
		for {
			hdr, err := tr.Next()
			if err == io.EOF {
				break
			}
			if err != nil {
				return nil, err
			}
			files = append(files, hdr.Name)
		}
	}
	a.Files = files
	return &a, nil
}

func Register(archType string) {
	archives[archType] = true
}
