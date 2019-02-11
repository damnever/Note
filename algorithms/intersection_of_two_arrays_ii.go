// https://leetcode.com/problems/intersection-of-two-arrays-ii/

package main

import "fmt"

func intersect(nums1 []int, nums2 []int) []int {
	set1 := map[int]int{}
	nset := 0
	for _, n := range nums1 {
		set1[n]++
		nset++
	}

	res := []int{}
	for _, n := range nums2 {
		if nset == 0 {
			break
		}
		if set1[n] > 0 {
			set1[n]--
			nset--
			res = append(res, n)
		}
	}
	return res
}

func main() {
	fmt.Println(intersect([]int{1, 2, 2, 1}, []int{2, 2}))
	fmt.Println(intersect([]int{4, 9, 5}, []int{9, 4, 9, 8, 4}))
}
