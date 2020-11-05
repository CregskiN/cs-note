
public class BinarySearch {
    private BinarySearch() {
    }

    /**
     * 第一版：第一类：递归实现的二分搜索 searchRecursion
     *
     * @param data
     * @param target
     * @param <E>
     * @return 返回目标元素的下标，如没有，返回 -1
     */
    public static <E extends Comparable<E>> int searchRecursion(E[] data, E target) {
        return BinarySearch.searchRecursion(data, 0, data.length - 1, target);
    }

    private static <E extends Comparable<E>> int searchRecursion(E[] data, int l, int r, E target) {
        if (l > r) {
            return -1;
        }

        int mid = l + (r - l) / 2;
        if (data[mid].compareTo(target) == 0) {
            // 正中目标元素
            return mid;
        } else if (data[mid].compareTo(target) < 0) {
            // target > data[mid]，在右分支寻找
            return BinarySearch.searchRecursion(data, mid + 1, r, target);
        } else {
            // target < data[min] 在左分支寻找
            return BinarySearch.searchRecursion(data, l, mid - 1, target);
        }
    }

    /**
     * 第一版：第二类：非递归实现二分搜索
     *
     * @param data
     * @param target
     * @param <E>
     * @return 返回目标元素的下标，如没有，返回 -1
     */
    public static <E extends Comparable<E>> int search(E[] data, E target) {
        int l = 0, r = data.length - 1;
        int mid = -1;

        while (l <= r) {
            // 循环不变量
            // data[l] < target
            // data[r] > target
            // l <= r
            mid = l + (r - l) / 2;
            if (data[mid].compareTo(target) > 0) {
                // target < data[mid]，到左分支寻找
                r = mid - 1;
            }
            if (data[mid].compareTo(target) < 0) {
                // target > data[mid]，到右分支寻找
                l = mid + 1;
            } else {
                // target = data[mid]，命中
                return mid;
            }
        }

        return -1;
    }

    /**
     * 第二版：修改循环不变量实现二分查找法
     * 前一版循环不变量：
     * data[l, r] 查找 target
     * 改为
     * data[l, r) 查找 target
     *
     * @param data
     * @param target
     * @param <E>
     * @return 返回目标元素的下标，如没有，返回 -1
     */
    public static <E extends Comparable<E>> int search2(E[] data, E target) {
        int l = 0, r = data.length;
        while (l < r) { // 也可写作 l <= r - 1
            int mid = l + (r - l) / 2;
            if (data[mid].compareTo(target) > 0) {
                // target < data[mid]，在左分支寻找
                r = mid;
            } else if (data[mid].compareTo(target) < 0) {
                // target > data[mid]，在右分支寻找
                l = mid + 1;
            } else {
                return mid;
            }
        }
        return -1;
    }

    /**
     * 第一个变种：返回比target大的最小值的索引
     *
     * @param target
     * @param <E>
     * @return 比target大的最小值的索引
     */
    public static <E extends Comparable<E>> int upper(E[] data, E target) {
        int l = 0, r = data.length;
        // 如果找不到，返回 length r
        while (l < r) {
            // 循环不变量：在data[l, r] 中寻找比target大的最小值

            // l = r ，则 data[i] 一定是解

            // 先找 target 或 target+ & target- 再找 target+
            int mid = l + (r - l) / 2;
            if (data[mid].compareTo(target) <= 0) {
                // target >= data[mid]，在右分支寻找
                l = mid + 1;
            } else {
                // target < data[mid]，在左分支寻找
                r = mid;
            }
        }

        return l;
    }


    public static void main(String[] args) {
        Integer[] nums = {-1, 0, 3, 5, 5, 9, 9, 12};
        int target = 9;
        System.out.println(BinarySearch.search(nums, target)); // 5
        System.out.println(BinarySearch.searchRecursion(nums, target)); // 5
        System.out.println(BinarySearch.search2(nums, target)); // 6

        for (int i = -1; i < nums.length; i++) {
            int index = BinarySearch.upper(nums, i);
            System.out.print(i + "<" + nums[index] + " ");
        }
    }

}
