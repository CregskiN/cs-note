public class ArrayQueue<E> implements Queue<E> {
    private Array<E> array;

    public ArrayQueue(int capacity) {
        this.array = new Array<>(capacity);
    }

    public ArrayQueue() {
        this.array = new Array<>(10);
    }

    @Override
    public int getSize(){
        return this.array.getSize();
    }

    @Override
    public boolean isEmpty(){
        return this.array.isEmpty();
    }

    /**
     * 入队 均摊O(1)
     * @param e
     */
    @Override
    public void enqueue(E e){
        this.array.addLast(e);
    }

    /**
     * 出队 O(n)
     * @return
     */
    @Override
    public E dequeue(){
        return this.array.removeFirst();
    }

    /**
     * 查看队首 O(1)
     * @return
     */
    @Override
    public E getFront(){
        return this.array.getFirst();
    }

    @Override
    public String toString(){
        StringBuilder res = new StringBuilder();
        res.append("Queue: \n");
        res.append("front [ ");
        for(int i = 0 ; i < this.array.getSize() ; i ++){
            res.append(this.array.get(i));
            if(i != this.array.getSize() - 1)
                res.append(", ");
        }
        res.append(" ] tail");
        return res.toString();
    }

    public static void main(String[] args) {
        ArrayQueue<Integer> queue = new ArrayQueue<>();
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
