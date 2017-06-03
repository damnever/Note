// https://leetcode.com/problems/detect-capital/

package main

import (
	"fmt"
	"time"
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
		last = i
	}
	if (ncap > 1 && ncap < last+1) || (ncap == 1 && icap != 0) {
		return false
	}
	return true
}

func detectCapitalUse2(word string) bool {
	ncap := 0
	for i, c := range word {
		n := i + 1
		if c >= 'A' && c <= 'Z' {
			ncap++
			if (ncap != n) && i != 0 {
				return false
			}
		} else if ncap > 1 && ncap < n {
			return false
		}
	}
	return true
}

func main() {
	fmt.Printf("USA = %v\n", detectCapitalUse("USA"))
	fmt.Printf("leetcode = %v\n", detectCapitalUse("leetcode"))
	fmt.Printf("Google = %v\n", detectCapitalUse("Google"))
	fmt.Printf("FlaG = %v\n", detectCapitalUse("FlaG"))
	fmt.Printf("flaG = %v\n", detectCapitalUse("flaG"))
	fmt.Printf("FLag = %v\n", detectCapitalUse("FLag"))

	start := time.Now()
	for i := 0; i < 1e7; i++ {
		detectCapitalUse("USA")
		detectCapitalUse("leetcode")
		detectCapitalUse("Google")
		detectCapitalUse("FlaG")
		detectCapitalUse("flaG")
		detectCapitalUse("FLag")
	}
	fmt.Println(time.Since(start).Nanoseconds() / 1e7)

	start = time.Now()
	for i := 0; i < 1e7; i++ {
		detectCapitalUse2("USA")
		detectCapitalUse2("leetcode")
		detectCapitalUse2("Google")
		detectCapitalUse2("FlaG")
		detectCapitalUse2("flaG")
		detectCapitalUse2("FLag")
	}
	fmt.Println(time.Since(start).Nanoseconds() / 1e7)

}
