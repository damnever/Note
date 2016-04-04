// https://leetcode.com/problems/symmetric-tree/
//

package main

import "fmt"

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func isSymmetric(root *TreeNode) bool {
	if root == nil || (root.Left == nil && root.Right == nil) {
		return true
	} else if root.Left == nil || root.Right == nil {
		return false
	}
	nodes := []*TreeNode{root.Left, root.Right}
	count := 2

	for count > 0 && count%2 == 0 {
		for idx := 0; idx < count; idx += 2 {
			left := nodes[idx]
			right := nodes[idx+1]

			if left.Val != right.Val {
				return false
			}
			if left.Left != nil {
				if right.Right != nil {
					nodes = append(nodes, left.Left, right.Right)
				} else {
					return false
				}
			} else if right.Right != nil {
				return false
			}
			if left.Right != nil {
				if right.Left != nil {
					nodes = append(nodes, right.Left, left.Right)
				} else {
					return false
				}
			} else if right.Left != nil {
				return false
			}
		}
		nodes = nodes[count:]
		count = len(nodes)
	}

	return (count == 0)
}

func main() {
	root := TreeNode{Val: 1}
	left := TreeNode{2, nil, nil}
	right := TreeNode{2, nil, nil}
	root.Left = &left
	root.Right = &right

	fmt.Println(isSymmetric(&root))
}
