import java.util.Random;

public class Main {
    public static void main(String[] args) {
        int opCount = 100000;
        ArrayQueue<Integer> arrayQueue = new ArrayQueue<>();
        LoopQueue<Integer> loopQueue = new LoopQueue<>();
        double time1 = test(arrayQueue, opCount);
        double time2 = test(loopQueue, opCount);
        System.out.println("ArrayQueue: " + time1);
        System.out.println("LoopQueue: " + time2);
    }

    /**
     * 测试
     *
     * @param q
     * @return
     */
    private static double test(Queue<Integer> q, int opCount) {
        long startTime = System.nanoTime();
        Random rand = new Random();

        for (int i = 0; i < opCount; i++) {
            q.enqueue(rand.nextInt(Integer.MAX_VALUE));
        }
        for (int i = 0; i < opCount; i++) {
            q.dequeue();
        }

        long endTime = System.nanoTime();
        return (endTime - startTime) / 1000000000.0;
    }
}
