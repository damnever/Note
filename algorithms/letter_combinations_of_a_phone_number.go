// https://leetcode.com/problems/letter-combinations-of-a-phone-number/description/

package main

import (
	"fmt"
	"sort"
)

var num2chs = map[rune][]string{
	'2': []string{"a", "b", "c"},
	'3': []string{"d", "e", "f"},
	'4': []string{"g", "h", "i"},
	'5': []string{"j", "k", "l"},
	'6': []string{"m", "n", "o"},
	'7': []string{"p", "q", "r", "s"},
	'8': []string{"t", "u", "v"},
	'9': []string{"w", "x", "y", "z"},
}

func letterCombinations(digits string) []string {
	// Maybe some kind of tree to reduce memory usage?..
	combs := []string{}

	for i, d := range digits {
		if i == 0 {
			for _, c := range num2chs[d] {
				combs = append(combs, c)
			}
			continue
		}

		old := combs
		combs = []string{}
		for j := range old {
			x := old[j]
			for _, c := range num2chs[d] {
				combs = append(combs, x+c)
			}
		}
	}

	return combs
}

func main() {
	{
		expected := []string{"adg", "adh", "adi", "aeg", "aeh", "aei", "afg", "afh", "afi", "bdg", "bdh", "bdi", "beg", "beh", "bei", "bfg", "bfh", "bfi", "cdg", "cdh", "cdi", "ceg", "ceh", "cei", "cfg", "cfh", "cfi"}
		sort.Strings(expected)
		fmt.Println(expected)
		res := letterCombinations("234")
		sort.Strings(res)
		fmt.Println(res)
	}

	{
		expected := []string{"jmpt", "jmpu", "jmpv", "jmqt", "jmqu", "jmqv", "jmrt", "jmru", "jmrv", "jmst", "jmsu", "jmsv", "jnpt", "jnpu", "jnpv", "jnqt", "jnqu", "jnqv", "jnrt", "jnru", "jnrv", "jnst", "jnsu", "jnsv", "jopt", "jopu", "jopv", "joqt", "joqu", "joqv", "jort", "joru", "jorv", "jost", "josu", "josv", "kmpt", "kmpu", "kmpv", "kmqt", "kmqu", "kmqv", "kmrt", "kmru", "kmrv", "kmst", "kmsu", "kmsv", "knpt", "knpu", "knpv", "knqt", "knqu", "knqv", "knrt", "knru", "knrv", "knst", "knsu", "knsv", "kopt", "kopu", "kopv", "koqt", "koqu", "koqv", "kort", "koru", "korv", "kost", "kosu", "kosv", "lmpt", "lmpu", "lmpv", "lmqt", "lmqu", "lmqv", "lmrt", "lmru", "lmrv", "lmst", "lmsu", "lmsv", "lnpt", "lnpu", "lnpv", "lnqt", "lnqu", "lnqv", "lnrt", "lnru", "lnrv", "lnst", "lnsu", "lnsv", "lopt", "lopu", "lopv", "loqt", "loqu", "loqv", "lort", "loru", "lorv", "lost", "losu", "losv"}
		sort.Strings(expected)
		fmt.Println(expected)
		res := letterCombinations("5678")
		sort.Strings(res)
		fmt.Println(res)
	}
}
