package Array;

import java.util.Arrays;

class Solution27 {
    public static int removeElement(int[] nums, int val) {
        // 双指针
        int i = 0, j = nums.length - 1;
        while (i <= j) {
            if (nums[i] == val) {
                swap(nums, i, j--);
            } else {
                i++;
            }
        }

        return i;
    }

    private static void swap(int[] nums, int i, int j) {
        int t = nums[i];
        nums[i] = nums[j];
        nums[j] = t;
    }

    public static void main(String[] args) {
        int[] arr1 = {3, 2, 2, 3};
        int ret1 = removeElement(arr1, 3);
        System.out.println(ret1 + " " + Arrays.toString(arr1));

        int[] arr2 = {0, 1, 2, 2, 3, 0, 4, 2};
        int ret2 = removeElement(arr2, 2);
        System.out.println(ret2 + " " + Arrays.toString(arr2));

        int[] arr3 = {1};
        int ret3 = removeElement(arr3, 1);
        System.out.println(ret3 + " " + Arrays.toString(arr3));
    }
}
