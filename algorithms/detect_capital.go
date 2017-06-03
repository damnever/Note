// https://leetcode.com/problems/detect-capital/

package main

import (
	"fmt"
)

func detectCapitalUse(word string) bool {
	icap := -1
	ncap := 0
	last := 0
	for i, c := range word {
		if c >= 'A' && c <= 'Z' {
			icap = i
			ncap++
		}
		last = i // faster than len
	}
	if (ncap > 1 && ncap < last+1) || (ncap == 1 && icap != 0) {
		return false
	}
	return true
}

func main() {
	fmt.Printf("USA = %v\n", detectCapitalUse("USA"))
	fmt.Printf("leetcode = %v\n", detectCapitalUse("leetcode"))
	fmt.Printf("Google = %v\n", detectCapitalUse("Google"))
	fmt.Printf("FlaG = %v\n", detectCapitalUse("FlaG"))
	fmt.Printf("flaG = %v\n", detectCapitalUse("flaG"))
}
