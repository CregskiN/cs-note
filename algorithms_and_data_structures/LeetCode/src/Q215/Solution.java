package Q215;

import java.util.Random;

/**
 * 重点，使用快速排序法 partition 的思路
 * <p>
 * 例：arr.length = 10，找第 K 个小的元素 p = partition(arr) p == K ? p 就是第K个小的元素 : p > K
 * ? 第K个小的元素在p左侧 : 第K个小的元素在K右
 */
class Solution {
    public int findKthLargest(int[] nums, int k) {
        Random random = new Random();
        int k2i = nums.length - k;
        return nums[this.partition(nums, 0, nums.length - 1, k2i, random)];
    }

    /**
     * 返回原地排序后，v的下标
     *
     * @param arr
     * @param l
     * @param r
     * @param k2i
     * @param random
     * @return
     */
    private int partition(int[] arr, int l, int r, int k2i, Random random) {

        int p = l + random.nextInt(r - l + 1);
        this.swap(arr, l, p);

        // 双路快速排序
        int i = l + 1, j = r;
        while (true) {
            // 循环不变量
            // arr[l+1, i-1] < v
            // arr[j+1, r] > v
            while (i <= j && arr[l] > arr[i]) {
                // arr[i] < v
                i++;
                // 遇 >=v 停止
            }
            while (i <= j && arr[l] < arr[j]) {
                // arr[i] > v
                j--;
                // 与 <=v 停止
            }

            // i = j
            // 或 arr[i]>v & arr[j]<v
            if (i >= j) {
                break;
            }

            this.swap(arr, i, j);
            i++;
            j--;
        }
        this.swap(arr, l, j);


        if (j > k2i) {
            // 目标在左分支
            return this.partition(arr, l, j - 1, k2i, random);
        } else if (j < k2i) {
            // 目标在右分支
            return this.partition(arr, j + 1, r, k2i, random);
        } else {
            // 正中目标
            return j;
        }
    }

    private void swap(int[] arr, int i, int j) {
        int tem = arr[i];
        arr[i] = arr[j];
        arr[j] = tem;
    }
}