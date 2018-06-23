// https://leetcode.com/problems/combinations/description/

package main

import "fmt"

func combine(n int, k int) [][]int {
	combinations := [][]int{}
	if k > n {
		return combinations
	}

	indexs := make([]int, k, k)
	comb := make([]int, k, k)
	for i := 0; i < k; i++ {
		indexs[i] = i
		comb[i] = i + 1
	}
	combinations = append(combinations, comb)

	reset := false
	for j, x := k-1, n-k; j >= 0; {
		if indexs[j]-j >= x {
			j--
			reset = true
			continue
		}

		indexs[j]++
		if reset { // Reset indexs..
			for y := j + 1; y < k; y++ {
				indexs[y] = indexs[y-1] + 1
			}
			j = k - 1
			reset = false
		}
		comb = make([]int, k, k)
		for x, i := range indexs {
			comb[x] = i + 1
		}
		combinations = append(combinations, comb)
	}

	return combinations
}

func main() {
	fmt.Println(combine(4, 2))
	fmt.Println(combine(4, 3))
}
