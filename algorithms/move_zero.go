/*
 * https://leetcode.com/problems/move-zeroes/
 *
 * Play with Golang, YOU DIAN GUAI YI...
 * Convert the Go code into C or Python to test it.
 */
package main

import "fmt"

func moveZeroes(nums []int) {
	length := len(nums)
	if length <= 1 {
		return
	}

	for i := length - 1; i >= 0; i-- {
		if nums[i] == 0 {
			tmp := i
			for j := i + 1; j < length; j++ {
				if nums[j] == 0 {
					break
				}
				nums[tmp], nums[j] = nums[j], nums[tmp]
				tmp = j
			}
		}
	}
}

func main() {
	var nums = []int{0, 1, 0, 3, 12, 0}
	fmt.Println(nums)
	moveZeroes(nums)
	fmt.Println(nums)
}
