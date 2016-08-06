package bptree

type Tree struct {
	root     tNode
	nodeSize int
}

type TreeIter struct {
	tree    *Tree
	current *lnode
	pos     int
}

func New(nodeSize int) *Tree {
	return &Tree{
		root:     nil,
		nodeSize: nodeSize,
	}
}

func (self *Tree) Set(key string, value string) {
	if self.root == nil {
		self.root = newLeafNode(self.nodeSize)
		self.root.insertKeyAt(0, newLeafKey(key, value))
		return
	}

	var stack []tNode
	next := self.root
	for !next.isLeaf() {
		stack = append(stack, next)
		next, _ = next.(*inode).findNext(key)
	}

	// update leaf node
	idx, found := next.searchKey(key)
	if found {
		next.(*lnode).updateValue(idx, value)
		return
	}
	// insert to leaf node
	next.insertKeyAt(idx, newLeafKey(key, value))

	// split recursively
	for {
		if !next.needSplit() {
			return
		}
		left, right := next.splitKey()
		newKey := right.firstKey().keyStr()

		// root
		if len(stack) == 0 {
			newRoot := newInternalNode(self.nodeSize)
			newRoot.insertKeyAt(0, newInternalKey(newKey))
			newRoot.setChildAt(0, left)
			newRoot.setChildAt(1, left)
			self.root = newRoot
			return
		}

		// other
		top := len(stack) - 1
		next, stack = stack[top], stack[:top]
		idx, _ = next.searchKey(newKey)
		// if found, merge ?? is that possible ??
		next.insertKeyAt(idx, newInternalKey(newKey))
		next.(*inode).setChildAt(idx, left)
		next.(*inode).setChildAt(idx+1, left)
	}
}

func (self *Tree) Get(key string) (string, bool) {
	if self.root == nil {
		return "", false
	}
	next := self.root
	for !next.isLeaf() {
		next, _ = next.(*inode).findNext(key)
	}
	idx, found := next.searchKey(key)
	if !found {
		return "", false
	}
	return next.(*lnode).getValue(idx), true
}

func (self *Tree) Del(key string) bool {
	return false
}

func NewIter(tree *Tree) *TreeIter {
	return &TreeIter{}
}

func (self *TreeIter) HasNext() bool {
	return false
}

func (self *TreeIter) Next() (string, string) {
	return "", ""
}
