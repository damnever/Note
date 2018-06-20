// https://leetcode.com/problems/flipping-an-image/description/

package main

import "fmt"

func flipAndInvertImage(A [][]int) [][]int {
	for _, a := range A {
		for f, l := 0, len(a)-1; f <= l; f, l = f+1, l-1 {
			if f == l {
				a[f] = 1 - a[f]
			} else {
				a[f], a[l] = 1-a[l], 1-a[f]
			}
		}
	}
	return A
}

func main() {
	fmt.Println(flipAndInvertImage([][]int{{1, 1, 0}, {1, 0, 1}, {0, 0, 0}}))
}
