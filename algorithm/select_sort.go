package main

import "fmt"

func SelectSort(nums []int) {
	length := len(nums) - 1

	for ; length > 0; length-- {
		max_idx := 0
		for i := 0; i <= length; i++ {
			if nums[i] > nums[max_idx] {
				max_idx = i
			}
		}
		nums[max_idx], nums[length] = nums[length], nums[max_idx]
	}
}

func main() {
	var nums = make([]int, 0, 8)
	nums = []int{2, 6, 4, 8, 1, 3, 7, 5}
	fmt.Println(nums)
	SelectSort(nums)
	fmt.Println(nums)
}
