package src;

import java.util.Arrays;

/**
 * 递归深度 log n
 * 对于百万数据，不过是 20
 */
public class MergeSort {
    private MergeSort() {
    }

    /**
     * 基础款
     *
     * @param arr
     * @param <E>
     */
    public static <E extends Comparable<E>> void sort(E[] arr) {
        E[] temp = Arrays.copyOfRange(arr, 0, arr.length); // 复制 arr[l, r + 1) 区间到 temp
        MergeSort.sort(arr, 0, arr.length - 1, temp);
    }

    /**
     * Sort-Up-Bottom 自底向下归并排序法
     *
     * @param arr
     * @param l
     * @param r
     * @param temp
     * @param <E>
     */
    private static <E extends Comparable<E>> void sort(E[] arr, int l, int r, E[] temp) {
        if (l >= r) {
            return;
        }
        int mid = l + ((r - l) / 2);
        MergeSort.sort(arr, l, mid, temp);
        MergeSort.sort(arr, mid + 1, r, temp);
        if (arr[mid].compareTo(arr[mid + 1]) > 0) {
            MergeSort.merge(arr, l, mid, r, temp);
        }
    }

    /**
     * Sort-Bottom-Up 自底向上归并排序
     *
     * @param arr
     * @param <E>
     */
    public static <E extends Comparable<E>> void sortBU(E[] arr) {
        E[] temp = Arrays.copyOf(arr, arr.length);
        int length = arr.length;
        for (int size = 1; size < length; size = size + size) {

            for (int i = 0; i + size < length; i = i + size + size) {
                // i 为每个需要合并的数组的起点下标
                // 合并 [i, i+size-1] 与 [i+size, i+size+size]
                if (arr[i + size - 1].compareTo(arr[i + size]) > 0) {
                    merge(arr, i, i + size - 1, Math.min(i + size + size - 1, length - 1), temp);
                }
            }
        }

    }

    public static <E extends Comparable<E>> void sortBUOpt(E[] arr) {
        E[] temp = Arrays.copyOf(arr, arr.length);
        int length = arr.length;

        // 对所有 arr[i, i+15] 使用插入排序
        for (int i = 0; i < length; i = i + 16) {
            InsertionSort.sort(arr, i, Math.min(i + 16 - 1, length - 1));
        }

        // 对size >=16 的使用归并排序
        for (int size = 16; size < length; size = size + size) {
            for (int i = 0; i + size < length; i = i + size + size) {
                if (arr[i + size - 1].compareTo(arr[i + size]) > 0) {
                    merge(arr, i, i + size - 1, Math.min(i + size + size - 1, length - 1), temp);
                }
            }
        }
    }

    /**
     * 合并两个有序区间 arr[l, mid] , arr[mid + 1, r]
     *
     * @param arr 原数组
     * @param l   左分支起点
     * @param mid 中点
     * @param r   右分支起点
     * @param <E>
     */
    private static <E extends Comparable<E>> void merge(E[] arr, int l, int mid, int r, E[] temp) {
        System.arraycopy(arr, l, temp, l, r - l + 1);

        int i = l; // 左分支下标
        int j = mid + 1; // 右分支下标

        // 每轮循环为 arr[k] 赋值
        for (int k = l; k <= r; k++) {

            if (i > mid) {
                // 左分支全部遍历完成
                arr[k] = temp[j];
                j++;
            } else if (j > r) {
                // 右分支全部遍历完成
                arr[k] = temp[i];
                i++;
            } else if (temp[i].compareTo(temp[j]) <= 0) {
                // 左分支小于等于右分支
                arr[k] = temp[i];
                i++;
            } else {
                // 右分支大于左分支
                arr[k] = temp[j];
                j++;
            }
        }
    }

    public static void main(String[] args) {
        int[] dataSize = { 1000000 };
        for (int n : dataSize) {
            Integer[] arr = ArrayGenerator.generateRandomArray(n, n);
            Integer[] arr2 = Arrays.copyOf(arr, arr.length);
            SortingHelper.sortTest("MergeSort", arr);
            SortingHelper.sortTest("MergeSortBUOpt", arr2);
            // SortingHelper.sortTest("SelectionSort", arr);
        }
    }
}
