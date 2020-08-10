import javafx.util.Pair;

/**
 * 递归链表
 */
public class RecursionLinkList<E> {
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

    private Node head;
    private int size;

    public RecursionLinkList() {
        this.head = null;
        this.size = 0;
    }

    public boolean isEmpty() {
        return this.size == 0;
    }

    /**
     * 把元素 e 添加到坐标 index
     *
     * @param e
     */
    public void add(int index, E e) {
        if (index < 0 || index > this.size) {
            throw new IllegalArgumentException("Add failed. Require index >= 0 && index <= " + this.size);
        }
        this.head = this.add(this.head, index, e);
    }

    private Node add(Node node, int index, E e) {
        if (index == 0) {
            this.size++;
            return new Node(e, node);
        }

        node.next = this.add(node.next, index - 1, e);
        return node;
    }

    public void addFirst(E e) {
        this.add(0, e);
    }

    public void addLast(E e) {
        this.add(this.size, e);
    }

    /**
     * 删除下标为 index 的元素
     *
     * @param index
     * @return
     */
    public E remove(int index) {
        if (index < 0 || index >= size)
            throw new IllegalArgumentException("Remove failed. Index is illegal.");

        Pair<Node, E> res = remove(this.head, index);
        this.head = res.getKey();
        return res.getValue();
    }

    // 从以node为头结点的链表中，删除第index位置的元素，递归算法
    // 返回值包含两个元素，删除后的链表头结点和删除的值：）
    private Pair<Node, E> remove(Node node, int index) {
        if (index == 0){
            Node right = node.next;
            this.size--;
            node.next = null;
            return new Pair<>(right, node.e);
        }
        Pair<Node, E> res = remove(node.next, index - 1);
        node.next = res.getKey(); // Pair.getKey() 存储Node，getValye() 存储E
        return new Pair<>(node, res.getValue());
    }

    public E removeFirst() {
        return this.remove(0);
    }

    public E removeLast() {
        return this.remove(this.size - 1);
    }

    /**
     * 删除第一个 e 元素
     *
     * @param e
     */
    public void removeElement(E e) {
        this.removeElement(this.head, e);
    }

    private Node removeElement(Node node, E e) {
        if (node == null) {
            return null;
        }
        if (node.e.equals(e)) {
            Node right = node.next;
            node.next = null;
            this.size--;
            return right;
        }
        node.next = removeElement(node.next, e);
        return node;
    }

    /**
     * @param index
     * @param e
     */
    public void set(int index, E e) {
        this.set(this.head, index, e);
    }

    private Node set(Node node, int index, E e) {
        if (index == 0) {
            node.e = e;
            return node;
        }

        return this.set(node.next, index - 1, e);
    }

    public E get(int index) {
        return this.get(this.head, index).e;
    }

    private Node get(Node node, int index) {
        if (index == 0) {
            return node;
        }
        return this.get(node.next, index - 1);
    }

    @Override
    public String toString() {
        StringBuilder res = new StringBuilder();
        res.append(String.format("RecursionLinkList: size = %d \n", this.size));
        Node cur = this.head;
        while (cur != null) {
            res.append(cur + " -> ");
            cur = cur.next;
        }
        res.append("NULL");
        return res.toString();
    }

    public static void main(String[] args) {

        RecursionLinkList<Integer> list = new RecursionLinkList<>();
        for (int i = 0; i < 10; i++) {
            list.addFirst(i);
            System.out.println(list);

        }
        while (!list.isEmpty()) {
            System.out.println("removed " + list.removeLast());
            System.out.println(list);

        }
    }

}
