package Array;

import java.util.Arrays;

class Solution26 {
    public static int removeDuplicates(int[] nums) {
        int len = nums.length;
        if (len <= 1)
            return len;

        int slow = 1, fast = 1;
        while (fast < nums.length) {
            if (nums[fast] != nums[fast - 1]) {
                nums[slow] = nums[fast];
                slow++;
            }
            fast++;
        }

        return slow;
    }

    public static void main(String[] args) {
        int[] arr1 = {1, 1, 2};
        int ret1 = removeDuplicates(arr1);
        System.out.println(Arrays.toString(arr1));

        int[] arr2 = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
        int ret2 = removeDuplicates(arr2);
        System.out.println(Arrays.toString(arr2));
    }
}