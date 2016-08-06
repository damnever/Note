package bptree

import (
	"math"
	"strings"
)

type tKey interface {
	compare(str string) int
	keyStr() string
}

type tNode interface {
	searchKey(str string) (int, bool)
	insertKeyAt(idx int, key tKey)
	deleteKeyAt(idx int)
	needSplit() bool
	splitKey() (tNode, tNode)
	isLeaf() bool
	firstKey() tKey
}

// key in internal node
type ikey string

// key in leaf node
type lkey struct {
	key   string
	value string
}

type keys []tKey

// internal node
type inode struct {
	splitPoint int
	cap        int
	keys       *keys
	childs     []tNode
}

// leaf node
type lnode struct {
	splitPoint int
	cap        int
	keys       *keys
	next       *lnode
}

/* internal node key function and mehtod */
func newInternalKey(str string) *ikey {
	ik := ikey(str)
	return &ik
}

func (self *ikey) keyStr() string {
	return string(*self)
}

func (self *ikey) compare(str string) int {
	return strings.Compare(string(*self), str)
}

/* leaf node key function and method */
func newLeafKey(key string, value string) *lkey {
	return &lkey{
		key:   key,
		value: value,
	}
}

func (self *lkey) keyStr() string {
	return self.key
}

func (self *lkey) compare(str string) int {
	return strings.Compare(self.key, str)
}

/* keys methods */
func (ks *keys) search(str string) (int, bool) {
	low, high, mid := 0, len(*ks)-1, 0

	for low < high {
		mid = (low + high) / 2
		cmped := (*ks)[mid].compare(str)
		if cmped < 0 {
			low = mid + 1
		} else if cmped > 1 {
			high = mid - 1
		} else {
			return mid, true
		}
	}

	return low, false
}

func (ks *keys) insertAt(idx int, key tKey) {
	if idx == len(*ks) {
		(*ks) = append((*ks), key)
		return
	}
	(*ks) = append((*ks)[:idx], append(keys{key}, (*ks)[idx:]...)...)
}

func (ks *keys) deleteAt(idx int) {
	last := len((*ks)) - 1
	if idx != last {
		copy((*ks)[idx:], (*ks)[idx+1:])
	}
	(*ks)[last] = nil
	(*ks) = (*ks)[:last]
}

/* internal node function and methods */
func newInternalNode(cap int) *inode {
	return &inode{
		cap:        cap,
		splitPoint: int(math.Ceil(float64(cap) / 2)),
		keys:       &keys{},
		childs:     make([]tNode, 0, cap+1),
	}
}

func (self *inode) searchKey(str string) (int, bool) {
	return self.keys.search(str)
}

func (self *inode) insertKeyAt(idx int, key tKey) {
	self.keys.insertAt(idx, key)
}

func (self *inode) deleteKeyAt(idx int) {
	self.keys.deleteAt(idx)
	idx += 1
	last := len(self.childs) - 1
	if idx != last {
		copy(self.childs[idx:], self.childs[idx+1:])
	}
	self.childs[last] = nil
	self.childs = self.childs[:last]
}

func (self *inode) needSplit() bool {
	return (len(*self.keys) == self.cap)
}

func (self *inode) splitKey() (tNode, tNode) {
	rkeys := (*self.keys)[self.splitPoint:]
	rchilds := self.childs[self.splitPoint+1:]

	(*self.keys) = (*self.keys)[:self.splitPoint]
	self.childs = self.childs[:self.splitPoint+1]

	right := newInternalNode(self.cap)
	(*right.keys) = append((*right.keys), rkeys...)
	right.childs = append(right.childs, rchilds...)

	return self, right
}

func (self *inode) isLeaf() bool {
	return false
}

func (self *inode) firstKey() tKey {
	return (*self.keys)[0]
}

func (self *inode) findNext(str string) (tNode, int) {
	idx, found := self.searchKey(str)
	if found {
		idx += 1
	}
	return self.childs[idx], idx
}

func (self *inode) setChildAt(idx int, child tNode) {
	if idx == len(self.childs) {
		self.childs = append(self.childs, child)
		return
	}
	self.childs = append(self.childs[:idx], append([]tNode{child}, self.childs[idx:]...)...)
}

/* leaf node function and methods */
func newLeafNode(cap int) *lnode {
	return &lnode{
		splitPoint: int(math.Ceil(float64(cap) / 2)),
		cap:        cap,
		keys:       &keys{},
		next:       nil,
	}
}

func (self *lnode) searchKey(str string) (int, bool) {
	return self.keys.search(str)
}

func (self *lnode) insertKeyAt(idx int, key tKey) {
	self.keys.insertAt(idx, key)
}

func (self *lnode) deleteKeyAt(idx int) {
	self.keys.deleteAt(idx)
}

func (self *lnode) needSplit() bool {
	return (len(*self.keys) == self.cap)
}

func (self *lnode) splitKey() (tNode, tNode) {
	rkeys := (*self.keys)[self.splitPoint:]
	(*self.keys) = (*self.keys)[:self.splitPoint]
	right := newLeafNode(self.cap)
	(*right.keys) = append((*right.keys), rkeys...)
	return self, right
}

func (self *lnode) isLeaf() bool {
	return true
}

func (self *lnode) firstKey() tKey {
	return (*self.keys)[0]
}

func (self *lnode) updateValue(idx int, value string) {
	(*self.keys)[idx].(*lkey).value = value
}

func (self *lnode) getValue(idx int) string {
	return (*self.keys)[idx].(*lkey).value
}
