/**
 * 不使用 dummyHead
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */
class Solution2 {
    public ListNode removeElements(ListNode head, int val) {
        // 1, 解决头部删除的问题
        while(head != null && head.val == val){
//            ListNode delNode = head;
//            head = delNode.next;
//            delNode.next = null;
            head = head.next;
        }

        if(head == null){
            return null;
        }

        ListNode prev = head;
        while(prev.next != null){
            if(prev.next.val == val){
//                ListNode delNode = prev.next;
//                prev.next = delNode.next;
//                delNode.next = null;
                prev.next = prev.next.next;
            }else {
                prev = prev.next;
            }
        }

        return head;
    }
}