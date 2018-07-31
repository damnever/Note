/**
* https://leetcode.com/problems/min-stack/description/
* I saw the hint..
*
* Your MinStack object will be instantiated and called as such:
* obj := Constructor();
* obj.Push(x);
* obj.Pop();
* param_3 := obj.Top();
* param_4 := obj.GetMin();
 */

package main

import "fmt"

type MinStack struct {
	top   int
	shift uint
	cap   int
	mins  []int
	elems []int
}

/** initialize your data structure here. */
func Constructor() MinStack {
	return MinStack{
		top:   -1,
		shift: 1,
		cap:   2,
		mins:  make([]int, 2, 2),
		elems: make([]int, 2, 2),
	}
}

func (s *MinStack) tryallocmore() {
	if s.top+1 >= s.cap {
		s.shift++
		s.cap = int(1 << s.shift)

		elems := make([]int, s.cap, s.cap)
		copy(elems, s.elems)
		s.elems = elems

		mins := make([]int, s.cap, s.cap)
		copy(mins, s.mins)
		s.mins = mins
	}
}

func (s *MinStack) Push(x int) {
	s.tryallocmore()

	min := x
	if s.top >= 0 && x > s.mins[s.top] {
		min = s.mins[s.top]
	}

	s.top++
	s.mins[s.top] = min
	s.elems[s.top] = x
}

func (s *MinStack) Pop() {
	s.top--
}

func (s *MinStack) Top() int {
	return s.elems[s.top]
}

func (s *MinStack) GetMin() int {
	return s.mins[s.top]
}

func main() {
	s := Constructor()
	s.Push(-2)
	s.Push(0)
	s.Push(-3)
	fmt.Println(s.GetMin())
	s.Pop()
	fmt.Println(s.Top())
	fmt.Println(s.GetMin())
}
