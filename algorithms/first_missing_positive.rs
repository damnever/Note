// https://leetcode.com/problems/first-missing-positive/
struct Solution {}

impl Solution {
    pub fn first_missing_positive(nums: Vec<i32>) -> i32 {
        let mut nums = nums;
        let n = nums.len();
        for i in 0..n {
            let idx = i;
            loop {
                let v = nums[idx];
                if v <= 0 {
                    break
                }
                let next_idx = (v-1) as usize;
                if v as usize > n || v == nums[next_idx] {
                    break
                }
                nums.swap(idx, next_idx);
            }
        }

        for (i, v) in nums.iter().enumerate() {
            let expect = (i+1) as i32;
            if expect != *v {
                return expect;
            }
        }
        if n == 0 {
            1
        } else {
            nums[n-1] + 1
        }
    }
}

fn main() {
    println!("{}", Solution::first_missing_positive(vec![]));
    println!("{}", Solution::first_missing_positive(vec![1]));
    println!("{}", Solution::first_missing_positive(vec![1,2,0]));
    println!("{}", Solution::first_missing_positive(vec![3,4,-1,1]));
    println!("{}", Solution::first_missing_positive(vec![7,8,9,11,12]));
}
