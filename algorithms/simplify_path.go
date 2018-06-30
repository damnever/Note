// https://leetcode.com/problems/simplify-path/description/

package main

import (
	"fmt"
	"strings"
)

func simplifyPath(path string) string {
	simplified := []string{"/"}
	n := 1
	for _, p := range strings.Split(path, "/") {
		if p == "." || p == "" {
			continue
		}

		if p == ".." {
			if n > 1 {
				simplified = simplified[:n-1]
				n--
			}
		} else {
			if n > 1 {
				p = "/" + p
			}
			simplified = append(simplified, p)
			n++
		}
	}
	return strings.Join(simplified, "")
}

func main() {
	fmt.Println(simplifyPath("/home/"))
	fmt.Println(simplifyPath("/a/./b/../../c/"))
	fmt.Println(simplifyPath("/home/damnever/"))
	fmt.Println(simplifyPath("/../"))
}
