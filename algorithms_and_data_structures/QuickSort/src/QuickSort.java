package src;

import java.util.*;

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

    private static <E extends Comparable<E>> int partition(E[] arr, int l, int r) {
        int j = l; // <v 分支最后一个元素下标

        for (int i = l + 1; i <= r; i++) {
            // 把 arr[i] 安排到合适位置
            // 循环不变量 arr[l+1, j] < v , arr[j+1, i) >= v
            if (arr[i].compareTo(arr[l]) < 0) {
                j++;
                QuickSort.swap(arr, i, j);
            }
        }
        QuickSort.swap(arr, l, j);

        // 如果arr[l, r]中，j = l，说明arr[l]最小
        return j;
    }

    /**
     * 第二版，选取随机元素
     * 解决问题：解决第一版中 orderArray 爆栈问题
     * 方法：partition时，随机选取 v
     * @param <E>
     * @param arr
     */
    public static <E extends Comparable<E>> void sort2(E[] arr) {
        Random random = new Random();
        QuickSort.sort2(arr, 0, arr.length - 1, random);
    }

    private static <E extends Comparable<E>> void sort2(E[] arr, int l, int r, Random random) {
        if (l >= r) {
            return;
        }
        // 先处理，再递归
        int p = QuickSort.partitionFix(arr, l, r, random);
        QuickSort.sort2(arr, l, p - 1, random);
        QuickSort.sort2(arr, p + 1, r, random);
    }

    private static <E extends Comparable<E>> int partitionFix(E[] arr, int l, int r, Random random) {
        int p = l + random.nextInt(r - l + 1); // 生成 [l, r] 的整数
        QuickSort.swap(arr, p, l);
        int j = l;
        for (int i = l + 1; i <= r; i++) {
            if (arr[i].compareTo(arr[l]) < 0) {
                j++;
                QuickSort.swap(arr, i, j);
            }
        }
        QuickSort.swap(arr, l, j);
        return j;
    }

    /**
     * 第三版：双路排序算法
     * 解决问题：第二版对于 sameValueArray 会爆栈，每次递归 partition 返回的 index 总是 arr[[0]]
     * 方法：
     * @param <E>
     * @param arr
     */
    public static <E extends Comparable<E>> void sort2ways(E[] arr) {
        Random random = new Random();
        QuickSort.sort2ways(arr, 0, arr.length - 1, random);
    }

    private static <E extends Comparable<E>> void sort2ways(E[] arr, int l, int r, Random random) {
        if (l >= r) {
            return;
        }
        // 先处理，再递归
        int p = QuickSort.partition2(arr, l, r, random);
        QuickSort.sort2ways(arr, l, p - 1, random);
        QuickSort.sort2ways(arr, p + 1, r, random);
    }

    private static <E extends Comparable<E>> int partition2(E[] arr, int l, int r, Random random) {
        int p = l + random.nextInt(r - l + 1); // 生成[l, r]随机索引
        QuickSort.swap(arr, l, p);

        int i = l + 1, j = r;
        // 整个过程，arr 只会被扫描一次（虽然有嵌套）
        // 循环不变量
        // arr[l+1, i-1] <= v
        // arr[j+1, r] >= v
        while (true) {
            while (i < j && arr[i].compareTo(arr[l]) < 0) {
                // 还有未遍历元素 && 选中的元素arr[i] < v
                i++;
            }
            while (j > i && arr[j].compareTo(arr[l]) > 0) {
                // 还有元素未遍历 && 选中的元素arr[j] > v
                j--;
            }

            // 判断 i j 是否停在一个位置
            if (i >= j) {
                // 停在一个位置，可以确定 arr[i] = arr[j] = v
                break;
            }

            // i j 不是停在一个位置
            QuickSort.swap(arr, i, j);
            i++;
            j--;
        }
        QuickSort.swap(arr, l, j);
        return j;
    }

    /**
     * 第四版：三路排序算法
     * 原因：双路排序算法中，对于sameValueArray对左右分支有可避免的重复处理，这可以避免
     *
     * @param arr
     * @param <E>
     */
    public static <E extends Comparable<E>> void sort3Ways(E[] arr) {
        Random random = new Random();
        QuickSort.sort3Ways(arr, 0, arr.length - 1, random);
    }

    private static <E extends Comparable<E>> void sort3Ways(E[] arr, int l, int r, Random random) {
        if (l >= r) {
            return;
        }

        QuickSort.partition3Ways(arr, l, r, random);
    }

    private static <E extends Comparable<E>> void partition3Ways(E[] arr, int l, int r, Random random) {
        int p = l + random.nextInt(r - l + 1); // l + [0, r-l+1) = [l, r]
        QuickSort.swap(arr, l, p);

        int i = l + 1, lt = l, gt = r + 1;
        while (i < gt) {
            // 循环不变量
            // arr[l+1, lt] < v
            // arr[lt+1, i-1] = v
            // arr[gt, r] > v
            // 将 arr[i] 分配到合适位置
            if (arr[l].compareTo(arr[i]) > 0) {
                // arr[i] < v
                lt++;
                QuickSort.swap(arr, lt, i);
                i++;
            } else if (arr[l].compareTo(arr[i]) < 0) {
                // arr[i] > v
                gt--;
                QuickSort.swap(arr, i, gt);
                // i++; // swap前 arr[gt]未排序，换到arr[i]后，也是未排序的，故此处不需要i++
            } else {
                // arr[i] = v
                i++;
            }
            if (i >= gt) {
                break;
            }
        }
        // 终止
        // arr[l+1, lt] < v
        // arr[lt+1, gt-1] = v
        // arr[gt, r] > v
        QuickSort.swap(arr, l, lt);
        // 交换完毕后
        // arr[l, lt-1] < v
        // arr[lt, gt-1] = v
        // arr[gt, r] > v
        // arr[lt] 为 v

        // 三路快排目的是，对于=v的元素，不再进行partition
        QuickSort.sort3Ways(arr, l, lt - 1, random);
        QuickSort.sort3Ways(arr, gt, r, random);
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
        if (i == j) {
            return;
        }
        E temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    public static void main(String[] args) {
        int n = 100000;

//        System.out.println("Random array");
//        Integer[] arrtemp = ArrayGenerator.generateRandomArray(n, n);
//        Integer[] arr1 = Arrays.copyOf(arrtemp, arrtemp.length);
//        Integer[] arr2 = Arrays.copyOf(arrtemp, arrtemp.length);
//        SortingHelper.sortTest("MergeSort", arr1);
//        SortingHelper.sortTest("QuickSort", arr2);
//        System.out.println(" ");

//        System.out.println("Order array");
//        Integer[] orderTemp = ArrayGenerator.generateOrderArray(n);
//        Integer[] orderArr1 = Arrays.copyOf(orderTemp, orderTemp.length);
//        Integer[] orderArr2 = Arrays.copyOf(orderTemp, orderTemp.length);
//        SortingHelper.sortTest("QuickSort", orderArr1);
//        SortingHelper.sortTest("QuickSort2", orderArr2);
//        System.out.println(" ");

        System.out.println("Same value array");
        Integer[] sameValueArray = ArrayGenerator.generateRandomArray(n, 1);
        Integer[] sameValueArray2 = Arrays.copyOf(sameValueArray, sameValueArray.length);
        SortingHelper.sortTest("QuickSort2Ways", sameValueArray);
        SortingHelper.sortTest("QuickSort3Ways", sameValueArray2);
        System.out.println(" ");


    }
}