// https://leetcode.com/problems/permutations/description/
//
// The easiest way is recursive algorithm.
// https://en.wikipedia.org/wiki/Steinhaus%E2%80%93Johnson%E2%80%93Trotter_algorithm

package main

import (
	"fmt"
)

func permute(nums []int) [][]int {
	permutations := [][]int{}
	if n := len(nums); n == 0 {
		return permutations
	} else if n == 1 {
		return [][]int{{nums[0]}}
	}

	subps := permute(nums[1:])
	for _, subp := range subps {
		n := len(subp)
		x := nums[0]
		for i := 0; i < n; i++ {
			p := make([]int, n+1)
			copy(p, subp[:i])
			p[i] = x
			copy(p[i+1:], subp[i:])
			permutations = append(permutations, p)
		}
		permutations = append(permutations, append(subp, x))
	}
	return permutations
}

func main() {
	fmt.Println(permute([]int{1, 2, 3}))
}
