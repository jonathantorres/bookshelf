package main

import (
	"bufio"
	"bytes"
	"fmt"
	"os"
	"strings"
)

func main() {
	r := bufio.NewReader(os.Stdin)
	scanner := bufio.NewScanner(r)
	defs := make(map[string]string)
	for scanner.Scan() {
		l := scanner.Bytes()
		if bytes.HasPrefix(l, []byte("#define")) {
			// save definition
			saveDef(l, defs)
			fmt.Printf("%s\n", string(l))
		} else {
			def := hasDef(l, defs)
			if def != "" {
				nl := replaceDef(l, def, defs)
				fmt.Printf("%s\n", nl)
			} else {
				fmt.Printf("%s\n", string(l))
			}
		}
	}
	if err := scanner.Err(); err != nil {
		fmt.Printf("%s\n", err)
		os.Exit(1)
	}
}

func saveDef(l []byte, defs map[string]string) {
	tokens := bytes.Split(l, []byte(" "))
	if len(tokens) < 3 {
		return
	}
	k := bytes.TrimSpace(tokens[1])
	var v bytes.Buffer
	for _, t := range tokens[2:] {
		v.Write(t)
	}
	defs[string(k)] = v.String()
}

func replaceDef(l []byte, def string, defs map[string]string) string {
	line := string(l)
	return strings.ReplaceAll(line, def, defs[def])
}

func hasDef(l []byte, defs map[string]string) string {
	for d := range defs {
		if strings.Contains(string(l), d) {
			return d
		}
	}
	return ""
}
