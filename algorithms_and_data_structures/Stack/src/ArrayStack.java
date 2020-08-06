public class ArrayStack<E> implements Stack<E> {
    Array<E> array;

    public ArrayStack(int capacity) {
        this.array = new Array<E>(capacity);
    }

    public ArrayStack(){
        this.array = new Array<E>();
    }

    /**
     * 获取 size
     * @return
     */
    @Override
    public int getSize(){
        return this.array.getSize();
    }

    /**
     * 判空
     * @return
     */
    @Override
    public boolean isEmpty(){
        return this.array.isEmpty();
    }

    /**
     * 获取 capacity
     * @return
     */
    public int getCapacity(){
        return this.array.getCapacity();
    }

    /**
     * 入栈
     * @param e
     */
    @Override
    public void push(E e){
        this.array.addLast(e);
    }

    /**
     * 出栈
     * @return
     */
    @Override
    public E pop(){
        return this.array.removeLast();
    }

    /**
     * 查看栈顶元素
     * @return
     */
    @Override
    public E peek(){
        return this.array.getLast();
    }

    @Override
    public String toString(){
        StringBuilder res = new StringBuilder();
        res.append("Stack: ");
        res.append("[");
        for(int i = 0; i < this.array.getSize(); i ++){
            res.append(this.array.get(i));
            if(i != this.array.getSize() - 1){
                res.append(", ");
            }
        }
        res.append("] top");
        return res.toString();
    }
}
