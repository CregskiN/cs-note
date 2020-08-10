public class Sum {
    public static int sum(int[] arr) {
        return sum(arr, 0);
    }

    // 计算 arr[l,n] 的和
    public static int sum(int[] arr, int startIndex) {
        if (startIndex == arr.length) {
            return 0;
        }
        int right = sum(arr, startIndex + 1);
        return arr[startIndex] + right;
    }

    public static void main(String[] args) {
        int[] arr = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        System.out.println(sum(arr));
    }
}
