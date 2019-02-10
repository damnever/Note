// https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/

package main

import "fmt"

func twoSum(numbers []int, target int) []int {
	maxidx := len(numbers) - 1
	if maxidx == 1 {
		return []int{1, 2}
	}

	if numbers[maxidx] > target && numbers[0] > 0 {
		maxidx, _ = bsearch(numbers, maxidx+1, target)
	}

	for i, v := range numbers[:maxidx+1] {
		idx, ok := bsearch(numbers[i+1:], maxidx-i, target-v)
		if ok {
			return []int{i + 1, i + idx + 2}
		}
	}
	panic("unreachable")
}

func bsearch(a []int, n, target int) (int, bool) {
	left, right := 0, n-1
	for left <= right {
		mid := (left + right) / 2
		if v := a[mid]; v < target {
			left = mid + 1
		} else if v > target {
			right = mid - 1
		} else {
			return mid, true
		}
	}
	return left - 1, false
}

func main() {
	fmt.Println(twoSum([]int{2, 7, 11, 15}, 9))
	fmt.Println(twoSum([]int{5, 25, 75}, 100))
	fmt.Println(twoSum([]int{-3, 3, 4, 90}, 0))
}
