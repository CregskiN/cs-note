import java.util.Arrays;

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
        MergeSort.merge(arr, l, mid, r, temp);

    }

    /**
     * Sort-Bottom-Up 自底向上归并排序
     *
     * @param arr
     * @param <E>
     */
    public static <E extends Comparable<E>> void sortBU(E[] arr) {
        E[] temp = Arrays.copyOfRange(arr, 0, arr.length);
        int length = arr.length;

        for (int size = 1; size < length; size = size * 2) {
            // 合并区间长度为 sz 的数组
            for (int i = 0; i + size < length; i = size * 2 + i) {
                // 遍历两个区间的起始位置 i
                // 合并 [i, i + size - 1], [i + size, i + size + size - 1]
                if (arr[i + size - 1].compareTo(arr[i + size]) > 0) {
                    // 一步优化
                    MergeSort.merge(arr, i, i + size - 1, Math.min(length - 1, i + size + size - 1), temp);
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
        int i = l; // 左分支索引 -> temp
        int j = mid + 1; // 右分支索引 -> temp

        for (int k = l; k <= r; k++) {
            // 为 arr[k] 赋值
            if (i > mid) {
                // 如果左分支全部处理完成
                arr[k] = temp[j - l]; // temp 从索引 0 开始
                j++;
            } else if (j > r) {
                // 如果右分支全部处理完成
                arr[k] = temp[i - l];
                i++;
            } else if (temp[i - l].compareTo(temp[j - l]) <= 0) {
                // 左区间更小
                arr[k] = temp[i - l];
                i++;
            } else {
                // 右区间更小 if (temp[i - l].compareTo(temp[j - l]) > 0)
                arr[k] = temp[j - l];
                j++;
            }
        }
    }

    public static void main(String[] args) {
        int[] dataSize = {100000};
        for (int n : dataSize) {
            Integer[] arr = ArrayGenerator.generateRandomArray(n, n);
            Integer[] arr2 = Arrays.copyOf(arr, arr.length);
            SortingHelper.sortTest("MergeSort", arr);
            SortingHelper.sortTest("MergeSort4", arr2);
//        SortingHelper.sortTest("SelectionSort", arr);
        }
    }
}


