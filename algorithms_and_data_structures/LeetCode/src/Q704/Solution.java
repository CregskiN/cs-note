package Q704;

class Solution {
    public int search(int[] nums, int target) {
        return search(nums, 0, nums.length - 1, target);
    }

    private static int search(int[] data, int l, int r, int target) {
        if (l > r) {
            return -1;
        }

        int mid = l + (r - l) / 2;
        if (data[mid] == target) {
            // 正中目标元素
            return mid;
        } else if (data[mid] < target) {
            // target > data[mid]，在右分支寻找
            return search(data, mid + 1, r, target);
        }
        // target < data[min] 在左分支寻找
        return search(data, l, mid - 1, target);

    }
}
