/**
 * Definition for singly-linked list.
 * public class ListNode {
 * int val;
 * ListNode next;
 * ListNode(int x) { val = x; }
 * }
 */
class Solution {

    // 非递归解法
//    public ListNode reverseList(ListNode head) {
//        ListNode prev = null;
//        ListNode cur = head;
//
//        while (cur != null) {
//            ListNode next = cur.next;
//            cur.next = prev; // cur.next -> prev
//            prev = cur; // prev -> cur
//            cur = next; // cur -> next
//        }
//
//        return prev;
//    }

    public ListNode reverseList(ListNode head){
        if(head == null || head.next == null) {
            return head;
        }

        ListNode rev = reverseList(head.next);
        head.next.next = head;
        head.next = null;
        return rev;
    }
}