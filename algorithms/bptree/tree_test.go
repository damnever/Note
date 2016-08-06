package bptree

import "testing"

func check(t *testing.T, tree *Tree, key string, value string) {
	if val, exists := tree.Get(key); exists && val != value {
		t.Fatalf("%v != %v\n", value, val)
	}
}

func TestBasic(t *testing.T) {
	tree := New(3)

	tree.Set("a", "b")
	check(t, tree, "a", "b")
	tree.Set("a", "c")
	check(t, tree, "a", "c")

	kvs := map[string]string{
		"sadfaw":     "werwq",
		"wqeui":      "837tidbsj",
		"23894gsj":   "wqwe8ubr",
		"34q08jld98": "395i",
		"dsfgiw9":    "342096pth;",
		"vcfhry":     "28lvxcdi72",
	}

	for k, v := range kvs {
		tree.Set(k, v)
		check(t, tree, k, v)
	}
}
