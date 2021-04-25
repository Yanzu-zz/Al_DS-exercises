package Array;

import java.util.Arrays;

/*先找出最大的索引 k 满足 nums[k] < nums[k+1]，如果不存在，就翻转整个数组；
    再找出另一个最大索引 l 满足 nums[l] > nums[k]；
    交换 nums[l] 和 nums[k]；
    最后翻转 nums[k+1:]。

    举个例子：
    比如 nums = [1,2,7,4,3,1]，下一个排列是什么？
    我们找到第一个最大索引是 nums[1] = 2
    再找到第二个最大索引是 nums[4] = 3
    交换，nums = [1,3,7,4,2,1];
    翻转，nums = [1,3,1,2,4,7]
    完毕!
    所以,
    时间复杂度：O(n)O(n)
    空间复杂度：O(1)O(1)
*/
class Solution31 {
    public static void nextPermutation(int[] nums) {
        if (nums == null || nums.length == 0) return;

        int firstIndex = -1;
        for (int i = nums.length - 2; i >= 0; i--) {
            if (nums[i] < nums[i + 1]) {
                firstIndex = i;
                break;
            }
        }

        if (firstIndex == -1) {
            reverse(nums, 0, nums.length - 1);
            return;
        }

        int secondIndex = nums.length - 1;
        for (int i = nums.length - 1; i >= 0; i--) {
            if (nums[i] > nums[firstIndex]) {
                secondIndex = i;
                break;
            }
        }

        swap(nums, firstIndex, secondIndex);
        reverse(nums, firstIndex + 1, nums.length - 1);
    }

    private static void reverse(int[] nums, int i, int j) {
        while (i < j)
            swap(nums, i++, j--);
    }

    private static void swap(int[] nums, int i, int j) {
        int t = nums[i];
        nums[i] = nums[j];
        nums[j] = t;
    }

    public static void main(String[] args) {
        int[] arr1 = {1, 2, 3};
        nextPermutation(arr1);
        System.out.println(Arrays.toString(arr1));

        int[] arr2 = {1, 1, 5};
        nextPermutation(arr2);
        System.out.println(Arrays.toString(arr2));

        int[] arr3 = {2, 3, 1};
        nextPermutation(arr3);
        System.out.println(Arrays.toString(arr3));
    }
}