/*
 * Prolem:
 *   https://leetcode.com/problems/plus-one/
 *
 * UNCOMFORTABLE...
 * https://github.com/golang/go/wiki/SliceTricks
 */

package main

import "fmt"

func plusOne(digits []int) []int {
	length := len(digits)
	// plused := make([]int, length)
	// copy(plused, digits)
	plused := append([]int(nil), digits...)
	carry := 1

	for i := length - 1; i >= 0; i-- {
		carry += plused[i]
		plused[i] = carry % 10
		carry /= 10
	}
	if carry > 0 {
		plused = append(plused[:0], append([]int{carry}, plused...)...)
	}
	return plused
}

func main() {
	digits := []int{3, 8, 8, 9}
	fmt.Println(digits)
	fmt.Println(plusOne(digits))
	digits2 := []int{9, 9, 9}
	fmt.Println(digits2)
	fmt.Println(plusOne(digits2))
}
