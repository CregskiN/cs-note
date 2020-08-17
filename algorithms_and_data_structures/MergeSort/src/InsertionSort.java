import java.util.Arrays;

public class InsertionSort {
    private InsertionSort() {
    }

    /**
     * 插入排序 复杂度O(n^2)
     *
     * @param arr
     * @param <E>
     */
    public static <E extends Comparable<E>> void sort(E[] arr) {
        for (int i = 0; i < arr.length; i++) {
            for (int j = i; j - 1 >= 0 && arr[j].compareTo(arr[j - 1]) < 0; j--) {
                swap(arr, j, j - 1);
            }
        }
    }

    /**
     * 插入排序 优化版 复杂度O(n^2)
     * 细节上看，底层寻址更少，整体速度更快
     * 对于有序数组，复杂度O(n^2)
     *
     * @param arr
     * @param <E>
     */
    public static <E extends Comparable<E>> void sort2(E[] arr) {
        for(int i = 0; i < arr.length; i ++){

            // 将 arr[i] 插入到合适的位置
            E t = arr[i];
            int j;
            for(j = i; j - 1 >= 0 && t.compareTo(arr[j - 1]) < 0; j --){
                arr[j] = arr[j - 1];
            }
            arr[j] = t;
        }
    }

    /**
     * 换一种循环不变量
     *
     * @param arr
     * @param <E>
     */
    public static <E extends Comparable<E>> void sort3(E[] arr) {
        for (int i = arr.length - 1; i >= 0; i--) {
            // arr[0, i) 未排序 ，arr[i, n) 升序
            // 将 arr[i] 移动到 [i, n) 中合适的位置
            E tem = arr[i];
            int j;
            for (j = i; j + 1 < arr.length && tem.compareTo(arr[j + 1]) > 0; j++) {
                // arr[i] 比 arr[i+1] 大，左移
                arr[j] = arr[j + 1];
            }
            arr[j] = tem;
        }
    }

    private static <E> void swap(E[] arr, int i, int j) {
        E tem = arr[i];
        arr[i] = arr[j];
        arr[j] = tem;
    }

    public static void main(String[] args) {
        int[] dataSize = {10000, 100000};
        for (int n : dataSize) {
            Integer[] arr = ArrayGenerator.generateRandomArray(n, n);
            Integer[] arr2 = Arrays.copyOf(arr, arr.length);
            SortingHelper.sortTest("InsertionSort1", arr);
            SortingHelper.sortTest("SelectionSort", arr2);
        }
    }
}
