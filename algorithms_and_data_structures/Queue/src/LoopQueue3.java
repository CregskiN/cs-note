/**
 * 浪费一个空间，不实用 size 实现
 *
 * @param <E>
 */
public class LoopQueue3<E> implements Queue<E> {
    private E[] data;
    private int front;
    private int tail;

    public LoopQueue3(int capacity) {
        this.data = (E[]) new Object[capacity + 1];
        this.front = 0;
        this.tail = 0;
    }

    @Override
    public boolean isEmpty() {
        return this.front == this.tail;
    }

    public LoopQueue3() {
        this(10);
    }

    public int getCapacity() {
        return this.data.length - 1;
    }

    @Override
    public E getFront() {
        return this.data[this.front];
    }


    @Override
    public int getSize() {
        if (this.front < this.tail) {
            return this.tail - this.front;
        } else if (this.front > this.tail) {
            // [a, b, c(tail),"space" ,d, e(front), f, g, null, null] front=5,tail=2,length=10,size=7
            return this.tail + this.data.length - this.front; // 2 + 10 - 5 = 7
        } else {
            return 0;
        }
    }

    @Override
    public void enqueue(E e) {
        this.data[this.tail] = e;
        this.tail = (this.tail + 1) % this.data.length;
        if (this.getSize() == this.getCapacity()) {
//        if ((this.tail + 1) % this.data.length == this.front) { // 两种判满都可以
            this.resize(this.getCapacity() * 2);
        }
    }

    @Override
    public E dequeue() {
        E ret = this.data[this.front];
        this.data[this.front] = null;
        this.front = (this.front + 1) % this.data.length;

        if (this.getSize() == this.getCapacity() / 4 && this.getCapacity() / 2 != 0) {
            this.resize(this.getCapacity() / 2);
        }
        return ret;
    }


    private void resize(int newCapacity) {
        E[] newData = (E[]) new Object[newCapacity + 1];
        int size = this.getSize();
        for (int i = 0; i < size; i++) {
            newData[i] = this.data[(i + this.front) % this.data.length];
        }
        this.data = newData;
        this.front = 0;
        this.tail = size;
    }

    @Override
    public String toString() {
        StringBuilder res = new StringBuilder();
        res.append(String.format("Queue: size = %d, capacity = %d\n", this.getSize(), this.getCapacity()));
        res.append("front [");
//        for (int i = 0; i < this.getSize(); i++) {
//            res.append(this.data[(this.front + i) % this.data.length]);
//            if (i != this.getSize() - 1) {
//                res.append(", ");
//            }
//        }
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
        LoopQueue3<Integer> queue = new LoopQueue3<>();
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
