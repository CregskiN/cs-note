package Q75;


class Solution {
    public void sortColors(int[] nums) {
        int i = 0, lt = i - 1, gt = nums.length;

        while(i < gt){
            if(nums[i] == 0){
                // arr[i] = 0 在左分支
                lt++;
                this.swap(nums, i, lt);
                i++;
            }else if(nums[i] == 2){
                // arr[i] = 2 在右分支
                gt--;
                this.swap(nums, i, gt);
            }else {
                // arr[i] = 1 在中分支
                i++;
            }
        }
    }

    private void swap(int[]arr, int i, int j){
        if(i == j){
            return;
        }
        int tem = arr[i];
        arr[i] = arr[j];
        arr[j] = tem;
    }
}