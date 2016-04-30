//
// https://leetcode.com/problems/repeated-dna-sequences/
//
package main

import "fmt"

func findRepeatedDNASequences(s string) []string {
	m := map[string]int{}
	res := []string{}

	for idx := 0; idx+10 <= len(s); idx++ {
		key := s[idx : idx+10]
		if val, exists := m[key]; exists {
			if val == 1 {
				res = append(res, key)
			}
			m[key] = val + 1
		} else {
			m[key] = 1
		}
	}

	return res
}

func main() {
	s := "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
	fmt.Printf("%v -> %v\n", s, findRepeatedDNASequences(s))
	s = "AAAAAAAAAAA"
	fmt.Printf("%v -> %v\n", s, findRepeatedDNASequences(s))
}
