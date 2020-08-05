import java.util.Random;

public class ArrayGenerator {
    private ArrayGenerator() {
    }

    public static Integer[] generateOrderArray(int n) {
        Integer[] arr = new Integer[n];
        for (int i = 0; i < n; i++) {
            arr[i] = i;
        }
        return arr;
    }

    /**
     * 生成随即数组，每个元素范围[0, bound)
     * @param n
     * @param bound
     * @return
     */
    public static Integer[] generateRandomArray(int n, int bound) {
        Integer[] arr = new Integer[n];
        Random rand = new Random();
        for (int i = 0; i < n; i++) {
            arr[i] = rand.nextInt(bound);
        }
        return arr;
    }
}
