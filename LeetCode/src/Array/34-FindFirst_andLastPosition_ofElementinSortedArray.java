package Array;

import java.util.Arrays;

class Solution34 {
    // 看到已经排好序的数组第一时间要想到二分查找法
    // O(logn) 和 O(n) 的差别是很大的！
    public static int[] searchRange(int[] nums, int target) {
        int[] ret = new int[]{-1, -1};
        if (nums == null || nums.length == 0)
            return ret;

        int left = 0, right = nums.length - 1;
        int mid = left + (right - left) / 2; // 这种算 mid 方法可以防止越界

        while (nums[mid] != target) {
            if (left >= right)
                return ret;

            if (nums[mid] > target)
                right = mid - 1;
            else
                left = mid + 1;
            mid = left + (right - left) / 2;
        }

        int i = mid, j = mid;
        while (i > 0 && nums[i - 1] == target)
            i--;

        while (j < nums.length - 1 && nums[j + 1] == target)
            j++;

        ret[0] = i;
        ret[1] = j;
        return ret;
    }

    public static void main(String[] args) {
        int[] arr1 = {5, 7, 7, 8, 8, 10};
        System.out.println(Arrays.toString(searchRange(arr1, 8)));

        int[] arr2 = {5, 7, 7, 8, 8, 10};
        System.out.println(Arrays.toString(searchRange(arr2, 6)));

        int[] arr3={};
        System.out.println(Arrays.toString(searchRange(arr3, 1)));
    }
}
