/**
 * 使用递归
 * // https://leetcode-cn.com/problems/remove-linked-list-elements/submissions/
 * Definition for singly-linked list.
 * public class ListNode {
 * int val;
 * ListNode next;
 * ListNode(int x) { val = x; }
 * }
 */
class Solution {
    public ListNode removeElements(ListNode head, int val) {
        // 1. 最小情况
        if (head == null) {
            return null;
        }

        // 2. 处理头部情况
//        if (head.val == val) {
//            // 头部删除
//            return removeElements(head.next, val);
//        } else {
//            // 头部不删除
//            head.next = removeElements(head.next, val);
//            return head;
//        }

        head.next = removeElements(head.next, val);
        return head.val == val ? head.next : head;


    }
}