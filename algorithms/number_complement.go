// https://leetcode.com/problems/number-complement/
package main

import "fmt"

func findComplement(num int) int {
	c, started := 0, false

	for n := 31; n >= 0; n-- {
		cur := 1 << uint(n)
		if (cur & num) > 0 {
			started = true
		} else if started {
			c |= cur
		}
	}

	return c
}

func main() {
	fmt.Printf("%v\n", findComplement(5))
}
