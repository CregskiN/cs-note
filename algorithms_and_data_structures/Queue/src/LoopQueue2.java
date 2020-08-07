/**
 * 有 size 实现不浪费那一个空间
 *
 * @param <E>
 */
public class LoopQueue2<E> implements Queue<E> {
    private E[] data;
    private int front;
    private int tail;
    private int size;

    public LoopQueue2(int capacity) {
        this.data = (E[]) new Object[capacity];
    }

    public LoopQueue2() {
        this(10);
    }

    @Override
    public boolean isEmpty() {
        return size == 0;
    }

    public boolean isFull() {
        return size == this.data.length;
    }

    @Override
    public int getSize() {
        return this.size;
    }

    public int getCapacity() {
        return this.data.length;
    }

    @Override
    public void enqueue(E e) {
        this.data[tail] = e;
        this.tail = (this.tail + 1) % this.data.length;
        this.size++;
        if (this.isFull()) {
            this.resize(this.getCapacity() * 2);
        }
    }

    @Override
    public E dequeue() {
        E ret = this.data[this.front];
        this.data[this.front] = null;
        this.front = (this.front + 1) % this.data.length;
        this.size--;
        if (this.size == this.getCapacity() / 4 && this.getCapacity() / 2 != 0) {
            resize(this.getCapacity() / 2);
        }
        return ret;
    }

    @Override
    public E getFront() {
        return this.data[this.front];
    }

    private void resize(int newCapacity) {
        E[] newData = (E[]) new Object[newCapacity];
        for (int i = 0; i < this.size; i++) {
            newData[i] = this.data[(i + this.front) % this.data.length];
        }
        this.data = newData;
        this.front = 0;
        this.tail = this.size;
    }

    @Override
    public String toString() {
        StringBuilder res = new StringBuilder();
        res.append(String.format("Queue: size = %d, capacity = %d\n", this.size, getCapacity()));
        res.append("front [");
        // 不能让 i = front，否则无法在内部判断最后一个元素，从而添加 ，号
        for (int i = 0; i < this.size; i++) {
            res.append(this.data[(this.front + i) % this.data.length]);
            if (i != this.size - 1) {
                res.append(", ");
            }
        }
        res.append("] tail");
        return res.toString();
    }

    public static void main(String[] args) {
        LoopQueue2<Integer> queue = new LoopQueue2<>();
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
