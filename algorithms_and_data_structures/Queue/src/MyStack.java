import java.util.Queue;
import java.util.LinkedList;

class MyStack {
    private Queue<Integer> queue1;
    private Queue<Integer> queue2;
    private Queue<Integer> queue3;


    /**
     * Initialize your data structure here.
     */
    public MyStack() {
        this.queue1 = new LinkedList<>();
        this.queue2 = new LinkedList<>();
    }

    /**
     * Push element x onto stack.
     */
    public void push(int x) {
        this.queue1.add(x);
    }

    /**
     * Removes the element on top of the stack and returns that element.
     */
    public int pop() {
        int res = -1;
        while (!this.queue1.isEmpty()) {
            int e = this.queue1.remove();
            if (this.queue1.size() == 0) {
                // 如果是最后一个元素，取出，并中断循环
                res = e;
            } else {
                this.queue2.add(e);
            }
        }
        this.swap();
        return res;
    }

    /**
     * Get the top element.
     */
    public int top() {
        int res = -1;
        while (!this.queue1.isEmpty()) {
            int e = this.queue1.remove();
            if (this.queue1.size() == 0) {
                // 如果是最后一个元素，取出，并中断循环
                res = e;
            }
            this.queue2.add(e);
        }
        this.swap();
        return res;
    }

    /**
     * Returns whether the stack is empty.
     */
    public boolean empty() {
        return queue1.isEmpty();
    }

    /**
     * 完成引用换位，queue1 <-> queue2
     */
    private void swap() {
        this.queue3 = this.queue1; // 3 -> 1
        this.queue1 = this.queue2; // 1 -> 2
        this.queue2 = this.queue3; // 2 -> 3 -> 1
        this.queue3 = null; // 3 -> null
    }

}

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack obj = new MyStack();
 * obj.push(x);
 * int param_2 = obj.pop();
 * int param_3 = obj.top();
 * boolean param_4 = obj.empty();
 */