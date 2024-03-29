import java.util.*;

class Solution_offer_51 {
  private int res = 0;

  public int reversePairs(int[] nums) {
    // this.method1(nums);
    // return this.method2(nums);
    return this.method3(nums);

  }

  /**
   * 暴力
   * 
   * @param nums
   * @return
   */
  private int method1(int[] nums) {
    int res = 0;
    for (int i = 0; i < nums.length; i++) {
      for (int j = i + 1; j < nums.length; j++) {
        if (nums[i] > nums[j]) {
          res++;
        }
      }
    }
    return res;
  }

  /**
   * 归并排序法中，维护状态 res 插入统计逆序对
   * 
   * @param nums
   * @return
   */
  private int method2(int[] nums) {
    this.res = 0;
    int[] temp = new int[nums.length];
    this.sort2(nums, 0, nums.length - 1, temp);
    return res;
  }

  /**
   * 
   * @param arr
   * @param l
   * @param r
   * @param temp
   */
  private void sort2(int[] arr, int l, int r, int[] temp) {
    if (l >= r) {
      return;
    }
    int mid = l + (r - l) / 2;
    this.sort2(arr, l, mid, temp);
    this.sort2(arr, mid + 1, r, temp);
    this.merge2(arr, l, mid, r, temp);
  }

  /**
   * merge 操作
   * 
   * @param arr
   * @param l    左分支起点下标
   * @param mid  左分支最后一点下标
   * @param r    右分支起点下标
   * @param temp 中间数组
   */
  private void merge2(int[] arr, int l, int mid, int r, int[] temp) {
    System.arraycopy(arr, l, temp, l, r - l + 1);
    int i = l;
    int j = mid + 1;
    for (int k = l; k <= r; k++) {
      // 为 arr[k] 赋值
      if (i > mid) {
        // 左分支遍历完成
        arr[k] = temp[j];
        j++;
      } else if (j > r) {
        // 右分支遍历完成
        arr[k] = temp[i];
        i++;
      } else if (temp[i] > temp[j]) {
        // 左分支大于等于右分支
        this.res += (mid - i + 1);
        arr[k] = temp[j];
        j++;
      } else {
        // 右分支大于左分支
        arr[k] = temp[i];
        i++;
      }
    }
  }

  /**
   * 第三种方法 使用递归中返回参数，而不是维护Solution类的状态
   * 
   * @param nums
   * @return
   */
  private int method3(int[] nums) {
    int[] temp = new int[nums.length];
    return this.sort3(nums, 0, nums.length - 1, temp);
  }

  /**
   * 
   * @param arr
   * @param l    左端下标
   * @param r    右端下标
   * @param temp
   * @return
   */
  private int sort3(int[] arr, int l, int r, int[] temp) {
    if (l >= r) {
      return 0;
    }
    int res = 0;
    int mid = l + (r - l) / 2;
    res = this.sort3(arr, l, mid, temp);
    res += this.sort3(arr, mid + 1, r, temp);
    if (arr[mid] > arr[mid + 1]) {
      res += this.merge3(arr, l, mid, r, temp);
    }
    return res;
  }

  private int merge3(int[] arr, int l, int mid, int r, int[] temp) {
    System.arraycopy(arr, l, temp, l, r - l + 1);
    int i = l;
    int j = mid + 1;
    int res = 0; // 逆序对个数

    for (int k = l; k <= r; k++) {
      // 为 arr[k] 赋值

      if (i > mid) {
        // 左分支遍历完成
        arr[k] = temp[j];
        j++;
      } else if (j > r) {
        // 右分支遍历完成
        arr[k] = temp[i];
        i++;
      } else if (temp[i] > temp[j]) {
        // 左分支大于右分支
        arr[k] = temp[j];
        j++;
        res = res + mid - i + 1;
      } else {
        // 右分支大于等于左分支
        arr[k] = temp[i];
        i++;
      }
    }
    return res;
  }

  public static void main(String[] args) {
    Solution_offer_51 s = new Solution_offer_51();
    int[] arr = { 7, 5, 6, 4 };
    System.out.println(s.reversePairs(arr));
  }
}