public class SelectionSort {
    private SelectionSort() {
    }

    /**
     * 升序排序（原地排序）复杂度 O(n^2)
     *
     * @param arr
     * @param <E>
     */
    public static <E extends Comparable<E>> void sort(E[] arr) {
        // arr[0,i) 有序，arr[i,n) 无序
        for (int i = 0; i < arr.length; i++) {
            // 选择 arr[i...n) 的最小值的索引
            int minIndex = i;
            for (int j = i; j < arr.length; j++) {
                if (arr[j].compareTo(arr[minIndex]) < 0) { // <
                    minIndex = j;
                }
            }
            swap(arr, i, minIndex);
        }
    }

    public static <E extends Comparable<E>> void sort2(E[] arr) {
        for (int i = arr.length - 1; i >= 0; i--) {
            // arr(i, n] 升序，arr[0, i] 未排序
            int maxIndex = i;
            for (int j = i; j >= 0; j--) {
                if (arr[j].compareTo(arr[maxIndex]) > 0) {
                    maxIndex = j;
                }
            }
            swap(arr, i, maxIndex);
        }
    }

    private static <E> void swap(E[] arr, int i, int j) {
        E tem = arr[i];
        arr[i] = arr[j];
        arr[j] = tem;
    }

    public static void main(String[] args) {
//        Integer[] arr = {1, 4, 2, 3, 6, 5};
//        SelectionSort.sort(arr);
//        for (int e : arr) {
//            System.out.println(e);
//        }
//
//        Student[] students = {
//                new Student("Alice", 40),
//                new Student("Bobo", 50),
//                new Student("Charles", 12)
//        };
//        SelectionSort.sort(students);
//        for (Student e : students) {
//            System.out.println(e);
//        }

        int[] dataSize = {10000, 100000};
        for (int n : dataSize) {
            Integer[] arr2 = ArrayGenerator.generateRandomArray(n, n);
            SortingHelper.sortTest("SelectionSort", arr2);
        }
    }
}
