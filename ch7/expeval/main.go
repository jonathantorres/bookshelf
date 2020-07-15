package main

// Exercise 7.15

import (
	"fmt"
	"github.com/jonathantorres/gopl/ch7/eval"
	"os"
	"unicode"
)

func main() {
	for {
		var input string
		if _, err := fmt.Scanf("%s", &input); err != nil {
			fmt.Fprintf(os.Stderr, "error reading input: %s\n", err)
			continue
		}
		expr, err := eval.Parse(input)
		if err != nil {
			fmt.Fprintf(os.Stderr, "error parsing input: %s\n", err)
			continue
		}
		var env = eval.Env{}
		var vars = getVars(input)
		if len(vars) > 0 {
			askForVars(&env, vars)
		}
		val := expr.Eval(env)
		fmt.Printf("= %.2f\n", val)
	}
}

func askForVars(env *eval.Env, vars []rune) {
	for _, r := range vars {
		var envVal float64
		fmt.Printf("Please provide a value for %c: ", r)
		fmt.Scanf("%f", &envVal)
		(*env)[eval.Var(string(r))] = envVal
	}
}

func containsRune(runes []rune, ru rune) bool {
	for _, r := range runes {
		if r == ru {
			return true
		}
	}
	return false
}

func getVars(input string) []rune {
	vars := []rune{}
	for _, r := range input {
		if unicode.IsLetter(r) && !containsRune(vars, r) {
			vars = append(vars, r)
		}
	}
	return vars
}
