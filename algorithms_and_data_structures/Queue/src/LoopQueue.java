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
     * @return
     */
    public int getCapacity(){
        return this.data.length - 1;
    }

    @Override
    public int getSize(){
        return this.size;
    }

    @Override
    public boolean isEmpty(){
        return this.front == this.tail;
    }

    @Override
    public void enqueue(E e){
        if((this.tail + 1) % data.length == this.front){
            resize(getCapacity() * 2);
        }
        this.tail = (this.tail + 1) % this.data.length;
    }

    private void resize(int newCapacity){
        E[] newData = (E[])new Object[newCapacity + 1];
        for(int i = 0; i < this.size; i++){
            newData[i] = this.data[(i + this.front) % this.data.length];
        }
        this.data = newData;
        this.front = 0;
        this.tail = size;
    }
}
