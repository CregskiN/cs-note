/**
 * 无size，浪费一个空间
 * @param <E>
 */
public class LoopDeque3<E> implements Deque<E> {
    private E[] data;
    private int front;
    private int tail;

    public LoopDeque3(int capacity) {
        this.data = (E[]) new Object[capacity + 1];
        this.front = 0;
        this.tail = 0;
    }

    public LoopDeque3() {
        this(10);
    }

    @Override
    public boolean isEmpty() {
        return this.front == this.tail;
    }

    public int getCapacity() {
        return this.data.length - 1;
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

    private int getFrontIndex(int index){
        if(index < 0){
            // [a, b(front), c, d, null(tail), null, null] front=1,tail=4,length=7
            return this.data.length + index; // -1时，返回length-1
        }
        return index;
    }

    /**
     * 在队首添加元素
     *
     * @param e
     */
    public void addFront(E e) {
        this.data[getFrontIndex(this.front - 1)] = e;
        this.front = getFrontIndex(this.front - 1);
        if (this.getSize() == this.getCapacity()) {
            this.resize(this.getCapacity() * 2);
        }
    }

    /**
     * 删除队首元素，并返回
     *
     * @return
     */
    public E removeFront() {
        E ret = this.data[this.front];
        this.data[this.front] = null;
        this.front = (this.front + 1) % this.data.length;

        if (this.getSize() == this.getCapacity() / 4 && this.getCapacity() / 2 != 0) {
            this.resize(this.getCapacity() / 2);
        }
        return ret;
    }

    /**
     * 在队尾添加元素
     *
     * @param e
     */
    public void addLast(E e) {
        this.data[this.tail] = e;
        this.tail = (this.tail + 1) % this.data.length;
        if (this.getSize() == this.getCapacity()) {
            this.resize(this.getCapacity() * 2);
        }
    }

    /**
     * 删除队尾元素，并返回
     *
     * @return
     */
    public E removeLast() {
        E ret = this.data[this.tail];
        this.data[this.tail] = null;
        this.tail = (this.tail - 1) % this.data.length;
        if (this.getSize() == this.getCapacity() / 4 && this.getCapacity() / 2 != 0) {
            this.resize(this.getCapacity() / 2);
        }
        return ret;
    }

    @Override
    public E getFront() {
        return this.get(this.front);
    }

    @Override
    public E getLast() {
        return this.get(this.tail);
    }

    private E get(int index) {
        return this.data[index];
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

        // 在下面的双端队列的测试中，偶数从队尾加入；奇数从队首加入
        LoopDeque3<Integer> dq = new LoopDeque3<>();
        for (int i = 0; i < 16; i++) {
            if (i % 2 == 0) dq.addLast(i);
            else dq.addFront(i);
            System.out.println(dq);
        }

        // 之后，我们依次从队首和队尾轮流删除元素
        System.out.println();
        for (int i = 0; !dq.isEmpty(); i++) {
            if (i % 2 == 0) dq.removeFront();
            else dq.removeLast();
            System.out.println(dq);
        }
    }

}
