/**
 * 有size 浪费一个空间
 * @param <E>
 */
public class LoopQueue<E> implements Queue<E> {

    private E[] data;
    private int front, tail;
    private int size;

    public LoopQueue(int capacity) {
        this.data = (E[]) new Object[capacity + 1];
        this.front = 0;
        this.tail = 0;
        this.size = 0;
    }

    public LoopQueue() {
        this(10);
    }

    /**
     * 因 capacity 与 data.length 差 1，所以拆分出该 API
     *
     * @return
     */
    public int getCapacity() {
        return this.data.length - 1;
    }

    @Override
    public int getSize() {
        return this.size;
    }

    /**
     * 判空条件：tail == front
     * 判满条件：tail + 1 == front
     *
     * @return
     */
    @Override
    public boolean isEmpty() {
        return this.front == this.tail;
    }

    /**
     * 入队 O(1)
     *
     * @param e
     */
    @Override
    public void enqueue(E e) {
        if ((this.tail + 1) % data.length == this.front) {
            resize(getCapacity() * 2);
        }
        this.data[this.tail] = e;
        this.tail = (this.tail + 1) % this.data.length;
        this.size++;
    }

    /**
     * 出队 O(1)
     *
     * @return
     */
    @Override
    public E dequeue() {
        if (this.isEmpty()) {
            throw new IllegalArgumentException("Cannot dequeue from an empty queue.");
        }
        E ret = this.data[this.front];
        this.data[this.front] = null;
        this.front = (this.front + 1) % this.data.length;
        this.size--;
        if (this.size == this.getCapacity() / 4 && this.getCapacity() / 2 != 0) {
            resize(this.getCapacity() / 2);
        }
        return ret;
    }

    /**
     * 查看队首元素
     *
     * @return
     */
    public E getFront() {
        if (this.isEmpty()) {
            throw new IllegalArgumentException("Cannot dequeue from an empty queue.");
        }
        return this.data[this.front];
    }


    private void resize(int newCapacity) {
        E[] newData = (E[]) new Object[newCapacity + 1];
        for (int i = 0; i < this.size; i++) {
            newData[i] = this.data[(i + this.front) % this.data.length];
        }
        this.data = newData;
        this.front = 0;
        this.tail = size;
    }

    @Override
    public String toString() {
        StringBuilder res = new StringBuilder();
        res.append(String.format("Queue: size = %d, capacity = %d\n", this.size, getCapacity()));
        res.append("front [");
        for (int i = this.front; i != this.tail; i = (i + 1) % this.data.length) {
            res.append(this.data[i]);
            if ((i + 1) % this.data.length != this.tail) {
                res.append(", ");
            }
        }
        res.append("] tail");
        return res.toString();
    }

    public static void main(String[] args) {
        LoopQueue<Integer> queue = new LoopQueue<>();
        for (int i = 0; i < 10; i++) {
            queue.enqueue(i);
            System.out.println(queue);
            if (i % 3 == 2) {
                queue.dequeue();
                System.out.println(queue);
            }
        }
    }
}
