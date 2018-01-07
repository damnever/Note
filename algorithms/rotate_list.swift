// https://leetcode.com/problems/rotate-list/description/

class ListNode {
    var val: Int
    var next: ListNode?

    init(val: Int, next: ListNode?) {
        self.val = val
        self.next = next
    }

    func pp() {
        var head: ListNode? = self
        while true {
            guard let current = head else {
                break
            }
            print("\(current.val)", terminator: " ")
            head = current.next
        }
        print("")
    }
}

class Solution {
    func rotateRight(_ head: ListNode?, _ k: Int) -> ListNode? {
        if k == 0 {
            return head
        }

        var current = head
        var arr = [ListNode]()

        while true {
            guard let tmp = current else {
                break
            }

            arr.append(tmp)
            current = tmp.next
        }
        if arr.count == 0 {
            return nil
        }
        let ik = k % arr.count
        if ik == 0 || arr.count == ik {
            return head
        }

        let leftBegin = arr[0]
        let iRightBegin = arr.count - ik
        let leftEnd = arr[iRightBegin-1]
        let rightBegin = arr[iRightBegin]
        let rightEnd = arr[arr.count-1]

        leftEnd.next = nil
        rightEnd.next = leftBegin
        return rightBegin
    }

    func main() {
        let head: ListNode? = ListNode(val: 1, next: ListNode(val: 2, next: ListNode(val: 3, next: ListNode(val: 4, next: ListNode(val: 5, next: nil)))))
        if let r = head {
            r.pp()
        }
        let res = rotateRight(head, 2)
        if let r = res {
            r.pp()
        }

        print("")

        let res2 = rotateRight(nil, 2)
        if let r = res2 {
            r.pp()
        }

        print("")

        let head2: ListNode? = ListNode(val: 1, next: nil)
        if let r = head2 {
            r.pp()
        }

        let res3 = rotateRight(head2, 1)
        if let r = res3 {
            r.pp()
        }
    }
}

Solution().main()
