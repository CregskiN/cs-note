package src;

import java.util.Arrays;

public class QuickSort {
    private QuickSort() {
    }

    public static <E extends Comparable<E>> void sort(E[] arr) {
        QuickSort.sort(arr, 0, arr.length - 1);
    }

    private static <E extends Comparable<E>> void sort(E[] arr, int l, int r) {
        if (l >= r) {
            return;
        }
        // 先处理，再递归
        int p = QuickSort.partition(arr, l, r);
        QuickSort.sort(arr, l, p - 1);
        QuickSort.sort(arr, p + 1, r);
    }

    public static <E extends Comparable<E>> void sort2(E[] arr) {
        QuickSort.sort2(arr, 0, arr.length - 1);
    }

    private static <E extends Comparable<E>> void sort2(E[] arr, int l, int r) {
        if (r - l < 15) {
            InsertionSort.sort(arr, l, r);
            return;
        }
        // 先处理，再递归
        int p = QuickSort.partition(arr, l, r);
        QuickSort.sort(arr, l, p - 1);
        QuickSort.sort(arr, p + 1, r);
    }

    /**
     * 返回 v 所在的索引
     * @param arr
     * @param l
     * @param r
     * @param <E>
     * @return
     */
    private static <E extends Comparable<E>> int partition(E[] arr, int l, int r) {
        int j = l; // <v 分支最后一个元素下标

        for (int i = l + 1; i <= r; i++) {
            // 把 arr[i] 安排到合适位置
            // 循环不变量 arr[l+1, j] < v , arr[j+1, i) >v
            if (arr[i].compareTo(arr[l]) < 0) {
                j++;
                QuickSort.swap(arr, i, j);
            }
        }
        QuickSort.swap(arr, l, j);
        return j;
    }


    /**
     * 交换位置
     *
     * @param arr
     * @param i
     * @param j
     * @param <E>
     */
    private static <E extends Comparable<E>> void swap(E[] arr, int i, int j) {
        E temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    public static void main(String[] args) {
        int n = 1000000;
        Integer[] arr = ArrayGenerator.generateRandomArray(n, n);
        Integer[] arr2 = Arrays.copyOf(arr, arr.length);
//        SortingHelper.sortTest("MergeSort", arr);
        SortingHelper.sortTest("QuickSort2", arr);
        SortingHelper.sortTest("QuickSort", arr2);

    }
}