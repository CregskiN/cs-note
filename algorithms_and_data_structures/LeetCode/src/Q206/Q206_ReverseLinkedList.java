public class Q206_ReverseLinkedList {
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
            // 头节点为空 || 尾节点
            return head;
        }

        ListNode rev = reverseList(head.next);
        head.next.next = head;
        head.next = null;
        return rev;
    }
}
