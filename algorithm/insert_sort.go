package main

import "fmt"

func InsertSort(nums []int) {
	length := len(nums)

	for i := 1; i < length; i++ {
		j := i - 1
		if nums[i] < nums[j] {
			tmp := nums[i]
			for ; j >= 0 && tmp < nums[j]; j-- {
				nums[j+1] = nums[j]
			}
			nums[j+1] = tmp
		}
	}
}

func main() {
	// Can not change a array
	var nums = []int{3, 5, 4, 7, 2, 1}
	fmt.Println(nums)
	InsertSort(nums)
	fmt.Println(nums)
}
