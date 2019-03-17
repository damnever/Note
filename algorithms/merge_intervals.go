// https://leetcode.com/problems/merge-intervals/

package main

import (
	"fmt"
	"sort"
)

// Interval definition.
type Interval struct {
	Start int
	End   int
}

func merge(intervals []Interval) []Interval {
	n := len(intervals)
	if n == 0 {
		return nil
	}
	sort.SliceStable(intervals, func(i, j int) bool {
		return intervals[i].Start < intervals[j].Start
	})

	merged := []Interval{intervals[0]}
	lidx := 0
	for _, interval := range intervals[1:] {
		last := merged[lidx]
		if last.End < interval.Start {
			merged = append(merged, interval)
			lidx++
		} else {
			end := interval.End
			if last.End > end {
				end = last.End
			}
			merged[lidx] = Interval{
				Start: last.Start,
				End:   end,
			}
		}
	}
	return merged
}

func main() {
	fmt.Println(merge([]Interval{
		{Start: 1, End: 3},
		{Start: 2, End: 6},
		{Start: 8, End: 10},
		{Start: 15, End: 18},
	}))
	fmt.Println(merge([]Interval{
		{Start: 1, End: 4},
		{Start: 2, End: 3},
	}))
}
