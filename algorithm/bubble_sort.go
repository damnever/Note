package main

import "fmt"

func BubbleSort(nums []int) {
	length := len(nums) - 1

	for ; length > 0; length-- {
		for i := 0; i < length; i++ {
			if nums[i] > nums[i+1] {
				nums[i], nums[i+1] = nums[i+1], nums[i]
			}
		}
	}
}

func main() {
	var nums = []int{2, 8, 4, 9, 6, 5}
	fmt.Println(nums)
	BubbleSort(nums)
	fmt.Println(nums)
}
