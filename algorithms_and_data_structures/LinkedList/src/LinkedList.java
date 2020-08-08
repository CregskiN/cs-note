public class LinkedList<E> {
    private class Node<E> {
        public E data;
        public Node next;

        public Node(E e, Node next) {
            this.data = e;
            this.next = next;
        }

        public Node(E e) {
            this.data = e;
            this.next = null;
        }

        public Node() {
            this(null, null);
        }

        @Override
        public String toString() {
            return this.data.toString();
        }
    }

    private Node head;
    private int size;

    public LinkedList() {
        this.head = null;
        this.size = 0;
    }

    public boolean isEmpty() {
        return this.size == 0;
    }

    public int getSize() {
        return this.size;
    }

    /**
     * 在链表头添加元素
     *
     * @param e
     */
    public void addFirst(E e) {
        this.head = new Node(e, this.head);
        this.size++;
    }

    /**
     * 在索引 index 位置添加节点
     *
     * @param index
     * @param e
     */
    public void add(int index, E e) {
        if(index < 0 || index > size){
            throw new IllegalArgumentException("Add failed. Illegal index.");
        }
        if(index == 0){
            // 对于 index == 0 使用特殊逻辑。可使用虚拟头节点
            this.addFirst(e);
        }else {
            Node prev = this.head;
            for (int i = 0; i < index - 1; i++) {
                prev = prev.next;
            }
            prev.next = new Node(e, prev.next);
        }
        this.size ++;
    }

    public void addLast(E e){
        this.add(size, e);
    }
}
