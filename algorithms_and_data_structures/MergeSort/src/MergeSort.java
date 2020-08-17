import java.util.Arrays;

public class MergeSort {
    private MergeSort() {
    }

    public static <E extends Comparable<E>> void sort(E[] arr) {
        sort(arr, 0, arr.length - 1); // 对 arr[0, length - 1] 排列
    }

    private static <E extends Comparable<E>> void sort(E[] arr, int l, int r) {
        if (l >= r) {
            return;
        }
        int mid = l + (r - l) / 2;
        MergeSort.sort(arr, l, mid);
        MergeSort.sort(arr, mid + 1, r);
        MergeSort.merge(arr, l, mid, r);
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
    private static <E extends Comparable<E>> void merge(E[] arr, int l, int mid, int r) {
        E[] temp = Arrays.copyOfRange(arr, l, r + 1); // 复制 arr[l, r + 1) 区间到 temp
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
            } else if (temp[i - l].compareTo(temp[j - l]) > 0) {
                // 右区间更小
                arr[k] = temp[j - l];
                j++;
            }
        }
    }

    public static <E extends Comparable<E>> void sortDepth(E[] arr) {
        MergeSort.sortDepth(arr, 0, arr.length - 1, 0);
    }

    private static <E extends Comparable<E>> void sortDepth(E[] arr, int l, int r, int depth) {
        String depthString = MergeSort.generateDepthString(depth);
        System.out.print(depthString);
        System.out.println(String.format("mergesort arr[%d, %d]", l, r));

        if (l >= r) {
            return;
        }
        int mid = l + (r - l) / 2;
        MergeSort.sortDepth(arr, l, mid, depth + 1);
        MergeSort.sortDepth(arr, mid + 1, r, depth + 1);
        MergeSort.merge(arr, l, mid, r);

        System.out.print(depthString);
        System.out.print(String.format("after merge arr[%d, %d] : ", l, r));
        for (E e : arr) {
            System.out.print(e + " ");
        }
        System.out.println();
    }

    /**
     * 生成深度字符串
     *
     * @param depth
     * @return
     */
    private static String generateDepthString(int depth) {
        StringBuilder res = new StringBuilder();
        for (int i = 0; i < depth; i++) {
            res.append("--");
        }
        return res.toString();
    }

    public static void main(String[] args) {
        int[] dataSize = {100000};
        for (int n : dataSize) {
            Integer[] arr = ArrayGenerator.generateRandomArray(n, n);
            Integer[] arr2 = Arrays.copyOf(arr, arr.length);
            SortingHelper.sortTest("MergeSort", arr);
            SortingHelper.sortTest("InsertionSort", arr2);
//        SortingHelper.sortTest("SelectionSort", arr);
        }
    }
}
