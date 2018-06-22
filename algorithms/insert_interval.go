// https://leetcode.com/problems/insert-interval/description/
// The code is fine.. I guess.. do not mind..

package main

import "fmt"

// Interval struct.
type Interval struct {
	Start int
	End   int
}

func insert(intervals []Interval, newInterval Interval) []Interval {
	last := len(intervals) - 1
	if last < 0 {
		return []Interval{newInterval}
	}
	first := intervals[0]
	if newInterval.End < first.Start {
		return append([]Interval{newInterval}, intervals...)
	}
	lastx := intervals[last]
	if newInterval.Start > lastx.End {
		return append(intervals, newInterval)
	}

	starti, found1 := bis(intervals, last, newInterval.Start)
	endi, found2 := bis(intervals[starti:], last-starti, newInterval.End)
	endi += starti

	start := newInterval.Start
	if found1 {
		start = intervals[starti].Start
	}
	end := newInterval.End
	if found2 {
		end = intervals[endi].End
		endi++
	}

	n := last + 1 - endi + starti + 1
	newintervals := intervals[:]
	if n > last+1 { // Alloc
		newintervals = make([]Interval, n)
		copy(newintervals[:starti], intervals[:starti])
	}
	copy(newintervals[starti+1:], intervals[endi:])
	newintervals[starti] = Interval{Start: start, End: end}
	newintervals = newintervals[:n]
	return newintervals
}

func bis(intervals []Interval, n, target int) (int, bool) {
	for i := 0; i <= n; {
		mid := (i + n) / 2
		x := intervals[mid]
		if x.Start > target {
			n = mid - 1
		} else if x.End < target {
			i = mid + 1
		} else {
			return mid, true
		}
	}
	return n + 1, false
}

func main() {
	fmt.Println(insert([]Interval{{2, 5}, {6, 7}, {8, 9}}, Interval{Start: 0, End: 1}))
	fmt.Println(insert([]Interval{{1, 5}}, Interval{Start: 2, End: 3}))
	fmt.Println(insert([]Interval{{3, 5}, {12, 15}}, Interval{Start: 6, End: 6}))
	fmt.Println(insert([]Interval{{0, 5}, {9, 12}}, Interval{Start: 7, End: 16}))
	fmt.Println(insert([]Interval{{1, 5}, {6, 8}}, Interval{Start: 0, End: 9}))
	fmt.Println(insert([]Interval{{1, 5}}, Interval{Start: 0, End: 6}))
	fmt.Println(insert([]Interval{{1, 5}}, Interval{Start: 0, End: 0}))
	fmt.Println(insert([]Interval{}, Interval{Start: 5, End: 7}))
	fmt.Println(insert([]Interval{{1, 3}, {6, 9}}, Interval{Start: 2, End: 5}))
	intervals := []Interval{{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}}
	fmt.Println(insert(intervals, Interval{Start: 4, End: 8}))
}
