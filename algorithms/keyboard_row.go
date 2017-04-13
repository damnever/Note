// https://leetcode.com/problems/keyboard-row/
// Trading space for time, golang is faster, (＾－＾)V

package main

import (
	"fmt"
	"strings"
)

var Nil = struct{}{}

func newSet(ss []string) map[string]struct{} {
	set := make(map[string]struct{})

	for _, s := range ss {
		set[s] = Nil
		set[strings.ToUpper(s)] = Nil
	}

	return set
}

var keySets = []map[string]struct{}{
	newSet([]string{"q", "w", "e", "r", "t", "y", "u", "i", "o", "p"}),
	newSet([]string{"a", "s", "d", "f", "g", "h", "j", "k", "l"}),
	newSet([]string{"z", "x", "c", "v", "b", "n", "n", "m"}),
}

func findWords(words []string) []string {
	var set map[string]struct{}
	ws := []string{}

	for _, word := range words {
		contains := true

		setInit := false
		for _, c := range word {
			cs := string(c)
			if !setInit {
				for _, s := range keySets {
					if _, exists := s[cs]; exists {
						set = s
						break
					}
				}
				setInit = true
			} else if _, exists := set[cs]; !exists {
				contains = false
				break
			}
		}

		if contains {
			ws = append(ws, word)
		}
	}

	return ws
}

func main() {
	fmt.Printf("%v\n", findWords([]string{"Hello", "Alaska", "Dad", "Peace"}))
}
