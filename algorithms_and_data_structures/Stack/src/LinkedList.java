/**
 * 增: O(n)
 * 删: O(n)
 * 改: O(n)
 * 查: O(n)
 * 优点：1. 头操作是O(1) 2. 动态
 * @param <E>
 */
public class LinkedList<E> {
    private class Node {
        public E e;
        public Node next;

        public Node(E e, Node next) {
            this.e = e;
            this.next = next;
        }

        public Node(E e) {
            this.e = e;
            this.next = null;
        }

        public Node() {
            this(null, null);
        }

        @Override
        public String toString() {
            return this.e.toString();
        }
    }

    private Node dummyHead;
    private int size;

    public LinkedList() {
        this.dummyHead = new Node(null, null);
        this.size = 0;
    }

    public boolean isEmpty() {
        return this.size == 0;
    }

    public int getSize() {
        return this.size;
    }

    /**
     * O(n/2) = O(n)
     * 在索引 index 位置添加节点
     *
     * @param index
     * @param e
     */
    public void add(int index, E e) {
        if (index < 0 || index > size) {
            throw new IllegalArgumentException("Add failed. Illegal index.");
        }

        Node prev = this.dummyHead;
        for (int i = 0; i < index; i++) {
            // 循环不变量：当前 prev 为 i 的前节点
            prev = prev.next;
        }
        prev.next = new Node(e, prev.next);

        this.size++;
    }

    /**
     * O(1)
     * 在链表头添加元素
     *
     * @param e
     */
    public void addFirst(E e) {
        this.add(0, e);
    }

    /**
     * O(n)
     *
     * @param e
     */
    public void addLast(E e) {
        this.add(size, e);
    }

    /**
     * O(n)
     * 获取 index 位置的元素
     *
     * @param index
     * @return
     */
    public E get(int index) {
        if (index < 0 || index >= size) {
            throw new IllegalArgumentException("Get failed. Illegal index.");
        }
        Node cur = this.dummyHead.next;
        for (int i = 0; i < index; i++) {
            cur = cur.next;
        }
        return cur.e;
    }

    public E getFirst() {
        return get(0);
    }

    public E getLast() {
        return get(this.size - 1);
    }

    /**
     * O(n)
     * 设置 index 位置的元素为 e
     *
     * @param index
     * @param e
     */
    public void set(int index, E e) {
        if (index < 0 || index >= size) {
            throw new IllegalArgumentException("Set failed. Illegal index.");
        }
        Node cur = this.dummyHead.next;
        for (int i = 0; i < index; i++) {
            // 循环不变量：i 为当前 cur 的下标
            cur = cur.next;
        }
        cur.e = e;
    }

    /**
     * O(n)
     * 查询链表中是否有元素 e
     *
     * @param e
     * @return
     */
    public boolean contains(E e) {
        Node cur = this.dummyHead.next;
        while (cur != null) {
            if (cur.e.equals(e)) {
                return true;
            }
            cur = cur.next;
        }
        return false;
    }


    /**
     * O(n)
     * 删除下标为 index 的元素
     *
     * @param index
     * @return
     */
    public E remove(int index) {
        if (index < 0 || index >= size) {
            throw new IllegalArgumentException("Remove failed. Illegal index.");
        }

        Node prev = this.dummyHead;
        for (int i = 0; i < index; i++) {
            prev = prev.next;
        }
        Node delNode = prev.next;
        prev.next = delNode.next;
        delNode.next = null;
        this.size--;
        return delNode.e;
    }

    /**
     * O(1)
     *
     * @return
     */
    public E removeFirst() {
        return this.remove(0);
    }

    /**
     * O(n)
     *
     * @return
     */
    public E removeLast() {
        return this.remove(this.size - 1);
    }


    @Override
    public String toString() {
        StringBuilder res = new StringBuilder();
        res.append(String.format("LinkedList: size = %d\n", this.size));
        Node cur = this.dummyHead.next;
        for (int i = 0; i < this.size; i++) {
            res.append(cur + " -> ");
            if (cur.next != null) {
                cur = cur.next;
            }
        }
        res.append("NULL");
        return res.toString();
    }
}
