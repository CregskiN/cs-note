import java.util.Stack;

class MyQueue {
    private Stack<Integer> stack1;
    private Stack<Integer> stack2;
    private Stack<Integer> stack3;
    private boolean isStack1; // 标志是否是stack1，与出队有关
    private Integer front;

    /**
     * Initialize your data structure here.
     */
    public MyQueue() {
        this.stack1 = new Stack<>();
        this.stack2 = new Stack<>();
        this.stack3 = null;
        this.isStack1 = true;
        this.front = -1;
    }

    /**
     * Push element x to the back of queue.
     */
    public void push(int x) {
        if (this.stack1.size() == 0) {
            // 如果stack 为空
            this.front = x;
        }

        if (this.isStack1) {
            this.stack1.push(x);
        } else {
            while (!this.stack1.isEmpty()) {
                int e = this.stack1.pop();
                this.stack2.push(e);
                if (this.stack1.size() == this.stack1.capacity()) {
                    this.front = e;
                }
            }
            this.stack2.push(x);
            this.swap();
        }
    }

    /**
     * Removes the element from in front of queue and returns that element.
     * 对于stack1，队首在栈底，队尾在栈顶
     * 对于stack2，队首在栈顶，队尾在栈底
     */
    public int pop() {
        int res = -1;
        if (this.isStack1) {
            while (!this.stack1.isEmpty()) {
                int e = this.stack1.pop();
                int size = this.stack1.size();
                if (size == 0) {
                    res = e;
                } else {
                    this.stack2.push(e);
                    this.front = this.stack2.peek();
                }
            }
            this.swap();
        } else {
            res = this.stack1.pop();
            if (!this.stack1.isEmpty()) {
                this.front = this.stack1.peek();
            }
        }

        return res;
    }

    /**
     * Get the front element.
     */
    public int peek() {
        return this.front;
    }

    /**
     * Returns whether the queue is empty.
     */
    public boolean empty() {
        return this.stack1.isEmpty();
    }

    /**
     * 完成引用换位，stack1 <-> stack2
     */
    private void swap() {
        this.stack3 = this.stack1; // 3 -> 1
        this.stack1 = this.stack2; // 1 -> 2
        this.stack2 = this.stack3; // 2 -> 3 -> 1
        this.stack3 = null; // 3 -> null
        this.isStack1 = !this.isStack1;
    }
}

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue obj = new MyQueue();
 * obj.push(x);
 * int param_2 = obj.pop();
 * int param_3 = obj.peek();
 * boolean param_4 = obj.empty();
 */