// https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/

use std::cell::RefCell;
use std::rc::Rc;

// Definition for a binary tree node.
#[derive(Debug, PartialEq, Eq)]
pub struct TreeNode {
    pub val: i32,
    pub left: Option<Rc<RefCell<TreeNode>>>,
    pub right: Option<Rc<RefCell<TreeNode>>>,
}

impl TreeNode {
    #[inline]
    pub fn new(val: i32) -> Self {
        TreeNode {
            val,
            left: None,
            right: None,
        }
    }
}

pub struct Solution {}

impl Solution {
    pub fn sorted_array_to_bst(nums: Vec<i32>) -> Option<Rc<RefCell<TreeNode>>> {
        let length = nums.len();
        if length == 0 {
            return None;
        }

        let mid = (length - 1) / 2;
        let node = Rc::new(RefCell::new(TreeNode::new(nums[mid])));
        if mid > 0 {
            node.borrow_mut().left =
                Solution::sorted_array_to_bst((&nums[..mid]).iter().cloned().collect());
        }
        if mid < length - 1 {
            node.borrow_mut().right =
                Solution::sorted_array_to_bst((&nums[(mid + 1)..]).iter().cloned().collect());
        }
        Some(node)
    }
}

pub fn main() {}
