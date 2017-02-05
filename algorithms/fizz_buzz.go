// https://leetcode.com/problems/fizz-buzz/
package main

import (
	"fmt"
	"strconv"
)

func fizzBuzz(n int) []string {
	res := make([]string, n)

	for i := 1; i <= n; i++ {
		s := ""
		if i%3 == 0 {
			s += "Fizz"
		}
		if i%5 == 0 {
			s += "Buzz"
		}
		if s == "" {
			res[i-1] = strconv.Itoa(i)
		} else {
			res[i-1] = s
		}
	}

	return res
}

func main() {
	fmt.Println(fizzBuzz(15))
}
