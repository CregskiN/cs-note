public interface Deque<E> {
    int getSize();
    boolean isEmpty();
    void addFront(E e);
    void addLast(E e);
    E removeFront();
    E removeLast();
    E getFront();
    E getLast();
}
