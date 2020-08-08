public class LinkedListQueue<E> implements Queue<E> {
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
    private Node tail;
    private int size;

    public LinkedListQueue(){
        this.head = null;
        this.tail = null;
        this.size = 0;
    }

    @Override
    public int getSize(){
        return this.size;
    }

    @Override
    public boolean isEmpty(){
        return this.size == 0;
    }

    /**
     * 将尾节点作为队尾，从尾节点入队
     * @param e
     */
    @Override
    public void enqueue(E e){
        if(this.tail == null){
            this.tail = new Node(e);
            this.head = this.tail;
        }else {
            this.tail.next = new Node(e,null);
            this.tail = this.tail.next;
        }
        this.size ++;
    }

    /**
     * 将头节点作为队首，从头节点出队
     * @return
     */
    @Override
    public E dequeue(){
        if(isEmpty()){
            throw new IllegalArgumentException("Dequeue failed. Queue is empty.");
        }
        Node retNode = this.head;
        this.head = retNode.next;
        retNode.next = null;
        if(this.head == null){
            this.tail = null;
        }
        this.size --;
        return retNode.e;
    }

    @Override
    public E getFront(){
        if(isEmpty()){
            throw new IllegalArgumentException("GetFront failed. Queue is empty.");
        }
        return this.head.e;
    }

    @Override
    public String toString(){
        StringBuilder res = new StringBuilder();
        res.append("Queue: front ");

        Node cur = head;
        while(cur != null) {
            res.append(cur + " -> ");
            cur = cur.next;
        }
        res.append("NULL tail");
        return res.toString();
    }

    public static void main(String[] args){

        LinkedListQueue<Integer> queue = new LinkedListQueue<>();
        for(int i = 0 ; i < 10 ; i ++){
            queue.enqueue(i);
            System.out.println(queue);

            if(i % 3 == 2){
                queue.dequeue();
                System.out.println(queue);
            }
        }
    }
}
