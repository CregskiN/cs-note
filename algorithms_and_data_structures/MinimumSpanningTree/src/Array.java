public class Array<E> {
    private E[] data;
    private int size;

    /**
     * 构造函数 传入容量
     *
     * @param capacity
     */
    public Array(int capacity) {
        this.data = (E[]) new Object[capacity];
        this.size = 0;
    }

    /**
     * 默认传入参数 函数重载
     */
    public Array() {
        this(10);
    }

    /**
     * 获取当前元素个数
     *
     * @return
     */
    public int getSize() {
        return this.size;
    }

    /**
     * 获取数组的容量
     *
     * @return
     */
    public int getCapacity() {
        return this.data.length;
    }

    /**
     * 获取数组是否为空
     *
     * @return
     */
    public boolean isEmpty() {
        return this.size == 0;
    }

    /**
     * 添加到头部 O(n)
     *
     * @param e
     */
    public void addFirst(E e) {
        add(0, e);
    }

    /**
     * 添加到最后 O(1)
     *
     * @param e
     */
    public void addLast(E e) {
        add(this.size, e);
    }


    /**
     * 添加值 e 到指定 index O(n)
     *
     * @param index
     * @param e
     */
    public void add(int index, E e) {
        if(this.size == this.data.length){
//            throw new IllegalArgumentException("Add failed. Array is full.");
            this.resize(this.data.length * 2);
        }
        if (index < 0 || index > size) {
            throw new IllegalArgumentException("Add failed.Require index >=0 , and <= " + this.size);
        }
        for (int i = index; i < size; i++) {
            // data[index] 开始，往后移
            this.data[i + 1] = this.data[i];
        }
        this.data[index] = e;
        this.size++;
    }

    /**
     * 获取 index 位置的元素值。O(1)
     *
     * @param index
     * @return
     */
    public E get(int index) {
        if (index < 0 || index > size) {
            throw new IllegalArgumentException("Get failed.Require index >=0 , and <= " + this.size);
        }
        return this.data[index];
    }

    /**
     * 设置 index 位置的元素为 e。O(1)
     *
     * @param index
     * @param e
     */
    public void set(int index, E e) {
        if (index < 0 || index > size) {
            throw new IllegalArgumentException("Set failed.Require index >=0 , and <= " + this.size);
        }
        this.data[index] = e;
    }

    /**
     * 查询是否包含。O(n)
     *
     * @param e
     * @return boolean
     */
    public boolean contains(E e) {
        for (int i = 0; i < this.size; i++) {
            if (this.data[i].equals(e)) {
                return true;
            }
        }
        return false;
    }

    /**
     * 查询元素 e 所在的 index。O(n)
     *
     * @param e
     * @return int
     */
    public int find(E e) {
        for (int i = 0; i < this.size; i++) {
            if (this.data[i].equals(e)) {
                return i;
            }
        }
        return -1;
    }

    /**
     * 删除第一个，并返回被删除元素。均摊复杂度O(n)
     *
     * @return
     */
    public E removeFirst() {
        return this.remove(0);
    }

    /**
     * 删除最后一个，并返回被删除元素。均摊复杂度O(1)
     *
     * @return
     */
    public E removeLast() {
        return this.remove(this.size - 1);
    }

    /**
     * 删除指定值的元素(只删除第一个)。均摊复杂度O(1)
     *
     * @param e
     */
    public void removeElement(E e) {
        int index = this.find(e);
        if (index != -1) {
            this.remove(index);
        }
    }

    /** 删除指定 index 位置的元素，并返回。 O(n)
     * @param index
     * @return
     */
    public E remove(int index) {
        if (index < 0 || index > size) {
            throw new IllegalArgumentException("Remove failed. Index is illegal.");
        }

        E ret = this.data[index];
        for (int i = index; i < size; i++) {
            this.data[i] = this.data[i + 1];
        }
        this.size--;
        this.data[size] = null; // loitering objects 零散对象，无法被清除

        if (this.size == this.data.length / 4 && this.data.length / 2 != 0) {
            // 缩容
            this.resize(this.data.length / 2);
        }

        return ret;
    }

    /**
     * 数组扩容与缩容
     *
     * @param newCapacity
     */
    private void resize(int newCapacity) {
        E[] newData = (E[]) new Object[newCapacity];
        for (int i = 0; i < this.size; i++) {
            newData[i] = this.data[i];
        }
        this.data = newData;
    }

    @Override
    public String toString() {
        StringBuilder res = new StringBuilder();
        res.append(String.format("Array: size = %d, capacity = %d \n", this.size, this.data.length));
        res.append("[");
        for (int i = 0; i < this.data.length; i++) {
            res.append(this.data[i]);
            if (i != this.data.length - 1) {
                res.append(", ");
            }
        }
        res.append("]");
        return res.toString();
    }

}
