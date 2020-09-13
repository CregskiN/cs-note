import java.util.Arrays;

public class MergeSortDemo {

    private MergeSortDemo() {
    }

    /**
     * 基础款
     *
     * @param arr
     * @param <E>
     */
    public static <E extends Comparable<E>> void sort(E[] arr) {
        MergeSortDemo.sort(arr, 0, arr.length - 1);
    }

    private static <E extends Comparable<E>> void sort(E[] arr, int l, int r) {
        if (l >= r) {
            return;
        }

        int mid = l + ((r - l) / 2);
        MergeSortDemo.sort(arr, l, mid);
        MergeSortDemo.sort(arr, mid + 1, r);
        MergeSortDemo.merge(arr, l, mid, r);

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
            } else {
                // 右区间更小 if (temp[i - l].compareTo(temp[j - l]) > 0)
                arr[k] = temp[j - l];
                j++;
            }
        }
    }


    /**
     * 优化：比较两片段尾、首，决定是否merge
     *
     * @param arr
     * @param <E>
     */
    public static <E extends Comparable<E>> void sort2(E[] arr) {
        sort2(arr, 0, arr.length - 1); // 对 arr[0, length - 1] 排列
    }

    private static <E extends Comparable<E>> void sort2(E[] arr, int l, int r) {
        if (l >= r) {
            return;
        }
        int mid = l + (r - l) / 2;
        MergeSortDemo.sort2(arr, l, mid);
        MergeSortDemo.sort2(arr, mid + 1, r);

        // 如果前一个片段末尾 < 后一个片段开头，可以说明这两个片段符合升序
        if (arr[mid].compareTo(arr[mid + 1]) > 0) {
            MergeSortDemo.merge(arr, l, mid, r);
        }
    }

    /**
     * 对于小规模数据，使用插入排序优化
     * 有些语言中，可能性能更差。如python js
     *
     * @param arr
     * @param <E>
     */
    public static <E extends Comparable<E>> void sort3(E[] arr) {
        MergeSortDemo.sort3(arr, 0, arr.length - 1); // 对 arr[0, length - 1] 排列
    }

    private static <E extends Comparable<E>> void sort3(E[] arr, int l, int r) {
//        if (l >= r) {
//            return;
//        }
        if (r - l <= 15) {
            InsertionSort.sort(arr, l, r);
            return;
        }
        int mid = l + (r - l) / 2;
        MergeSortDemo.sort3(arr, l, mid);
        MergeSortDemo.sort3(arr, mid + 1, r);
        MergeSortDemo.merge(arr, l, mid, r);
    }

    public static <E extends Comparable<E>> void sortDepth(E[] arr) {
        MergeSortDemo.sortDepth(arr, 0, arr.length - 1, 0);
    }

    private static <E extends Comparable<E>> void sortDepth(E[] arr, int l, int r, int depth) {
        String depthString = MergeSortDemo.generateDepthString(depth);
        System.out.print(depthString);
        System.out.println(String.format("mergesort arr[%d, %d]", l, r));

        if (l >= r) {
            return;
        }
        int mid = l + (r - l) / 2;
        MergeSortDemo.sortDepth(arr, l, mid, depth + 1);
        MergeSortDemo.sortDepth(arr, mid + 1, r, depth + 1);
        MergeSortDemo.merge(arr, l, mid, r);

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

    /**
     * 使用公共 temp，避免每次merge都copy
     *
     * @param arr
     * @param <E>
     */
    public static <E extends Comparable<E>> void sort4(E[] arr) {
        E[] temp = Arrays.copyOf(arr, arr.length);
        sort4(arr, 0, arr.length - 1, temp); // 对 arr[0, length - 1] 排列
    }

    private static <E extends Comparable<E>> void sort4(E[] arr, int l, int r, E[] temp) {
        if (l >= r) {
            return;
        }
        int mid = l + (r - l) / 2;
        MergeSortDemo.sort4(arr, l, mid, temp);
        MergeSortDemo.sort4(arr, mid + 1, r, temp);
        if (arr[mid].compareTo(arr[mid + 1]) > 0) {
            MergeSortDemo.merge4(arr, l, mid, r, temp);
        }
    }

    private static <E extends Comparable<E>> void merge4(E[] arr, int l, int mid, int r, E[] temp) {
        System.arraycopy(arr, l, temp, l, r - l + 1);
        int i = l; // 左分支索引 -> temp
        int j = mid + 1; // 右分支索引 -> temp

        for (int k = l; k <= r; k++) {
            // 为 arr[k] 赋值
            if (i > mid) {
                // 如果左分支全部处理完成
                arr[k] = temp[j];
                j++;
            } else if (j > r) {
                // 如果右分支全部处理完成
                arr[k] = temp[i];
                i++;
            } else if (temp[i].compareTo(temp[j]) <= 0) {
                // 左区间更小
                arr[k] = temp[i];
                i++;
            } else {
                // 右区间更小 if (temp[i - l].compareTo(temp[j - l]) > 0)
                arr[k] = temp[j];
                j++;
            }
        }
    }
}
