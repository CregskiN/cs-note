import java.util.Queue;
import java.util.LinkedList;

/**
 * 创建变量 top 存储栈顶元素，使 top 复杂度由 O(n) -> O(1)
 */
class MyStack2 {
    private Queue<Integer> queue1;
    private Queue<Integer> queue2;
    private Queue<Integer> queue3;
    private int top; // 记录栈顶元素

    /**
     * Initialize your data structure here.
     */
    public MyStack2() {
        this.queue1 = new LinkedList<>();
        this.queue2 = new LinkedList<>();
    }

    /**
     * Push element x onto stack.
     */
    public void push(int x) {
        this.top = x;
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
                // e 是倒数第一个元素
                res = e;
            } else {
                if (this.queue1.size() == 1) {
                    // e 是倒数第二个元素
                    this.top = e;
                }
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
        return this.top;
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