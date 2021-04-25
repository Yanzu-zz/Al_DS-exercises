package Array;

class Solution35 {
    public static int searchInsert(int[] nums, int target) {
        int left = 0, right = nums.length - 1;
        int mid = left + (right - left) / 2;

        while (nums[mid] != target && left < right) {
            if (nums[mid] > target)
                right = mid - 1;
            else
                left = mid + 1;
            mid = left + (right - left) / 2;
        }

        if (nums[mid] >= target)
            return mid;
        else
            return mid + 1;
    }

    public static void main(String[] args) {
        int[] arr1 = {1, 3, 5, 6};
        int ret1 = searchInsert(arr1, 5);
        int ret2 = searchInsert(arr1, 2);
        int ret3 = searchInsert(arr1, 0);
        int ret4 = searchInsert(arr1, 7);
        System.out.println(ret1);
        System.out.println(ret2);
        System.out.println(ret3);
        System.out.println(ret4);
    }
}
