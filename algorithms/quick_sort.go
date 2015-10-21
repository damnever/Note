package main

import "fmt"

func QuickSort(nums []int) {
	if nums == nil || len(nums) <= 1 {
		return
	}
	var pos int = partition(nums)
	QuickSort(nums[:pos])
	QuickSort(nums[pos+1:])
}

func partition(nums []int) int {
	pivot := nums[0]
	left, right := 1, len(nums)-1

	for left <= right {
		for left <= right && nums[left] <= pivot {
			left++
		}
		for left <= right && nums[right] > pivot {
			right--
		}
		if left > right {
			break
		}
		nums[left], nums[right] = nums[right], nums[left]
	}
	nums[0], nums[right] = nums[right], nums[0]
	return right
}

func main() {
	var nums = make([]int, 0, 8)
	nums = []int{2, 8, 4, 7, 6, 1, 5, 3}

	fmt.Println(nums)
	QuickSort(nums)
	fmt.Println(nums)
}
