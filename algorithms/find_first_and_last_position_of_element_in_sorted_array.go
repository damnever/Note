// https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/

package main

import "fmt"

func searchRange(nums []int, target int) []int {
	res := []int{-1, -1}
	n := len(nums)
	if n == 0 {
		return res
	}

	left, right := 0, n-1
	for left <= right {
		mid := (left + right) / 2
		if v := nums[mid]; v > target {
			right = mid - 1
		} else if v < target {
			left = mid + 1
		} else {
			start := mid - 1
			for start >= 0 && nums[start] == v {
				start--
			}
			res[0] = start + 1
			end := mid + 1
			for end < n && nums[end] == v {
				end++
			}
			res[1] = end - 1
			return res
		}
	}
	return res
}

func main() {
	fmt.Println(searchRange([]int{5, 7, 7, 8, 8, 10}, 8))
	fmt.Println(searchRange([]int{5, 7, 7, 8, 8, 10}, 6))
}
