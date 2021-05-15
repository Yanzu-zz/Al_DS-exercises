import java.util.Arrays;

class Solution {
    // 更一般的计数排序
    public static void sortColors(int[] nums) {
        int R = 3;

        int[] cnt = new int[R]; // 计算三种颜色的个数，索引对应每种颜色
        for (int num : nums)
            cnt[num]++;

        // 每组数字的边界数组
        int[] index = new int[R + 1]; // [index[i], index[i+1]) 的值为 i
        for (int i = 0; i < R; i++)
            index[i + 1] = index[i] + cnt[i];

        // 接下来就是覆盖原数组了
        for (int i = 0; i + 1 < index.length; i++)
            for (int j = index[i]; j < index[i + 1]; j++)
                nums[j] = i;
    }

    public static void main(String[] args) {
        int[] arr1 = {2, 0, 2, 1, 1, 0};
        sortColors(arr1);
        System.out.println(Arrays.toString(arr1));

        int[] arr2 = {0};
        sortColors(arr2);
        System.out.println(Arrays.toString(arr2));
    }
}