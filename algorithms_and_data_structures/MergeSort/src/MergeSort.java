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
        if(arr[mid].compareTo(arr[mid+1]) > 0){
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

    /**
     * 合并两个有序区间 arr[l, mid] , arr[mid + 1, r]
     *
     * @param arr 原数组
     * @param l   左分支起点
     * @param mid 中点
     * @param r   右分支起点
     * @param <E>
     */
    private static <E extends Comparable<E>> void merge(E[] arr, int l, int mid, int r, E[] aux){

        System.arraycopy(arr, l, aux, l, r - l + 1);

        int i = l, j = mid + 1;

        // 每轮循环为 arr[k] 赋值
        for(int k = l; k <= r; k ++){

            if(i > mid){
                arr[k] = aux[j]; j ++;
            }
            else if(j > r){
                arr[k] = aux[i]; i ++;
            }
            else if(aux[i].compareTo(aux[j]) <= 0){
                arr[k] = aux[i]; i ++;
            }
            else{
                arr[k] = aux[j]; j ++;
            }
        }
    }

    public static void main(String[] args) {
        int[] dataSize = { 1000000 };
        for (int n : dataSize) {
            Integer[] arr = ArrayGenerator.generateRandomArray(n, n);
            Integer[] arr2 = Arrays.copyOf(arr, arr.length);
            SortingHelper.sortTest("MergeSort", arr);
            SortingHelper.sortTest("MergeSortBU", arr2);
            // SortingHelper.sortTest("SelectionSort", arr);
        }
    }
}
