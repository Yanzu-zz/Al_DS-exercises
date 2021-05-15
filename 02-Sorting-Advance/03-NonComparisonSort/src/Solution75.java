import java.util.Arrays;

/**
 * 这里以力扣第75题为例学习计数排序
 * 给定一个包含红色、白色和蓝色，一共 n 个元素的数组，原地对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。
 * 此题中，我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。
 */
public class Solution75 {
    public static void sortColors(int[] nums) {
        int[] cnt = new int[3]; // 计算三种颜色的个数，索引对应每种颜色
        for (int num : nums)
            cnt[num]++;

        // 覆盖元素 0
        for (int i = 0; i < cnt[0]; i++)
            nums[i] = 0;
        int oneEnd = cnt[0] + cnt[1];
        // 覆盖元素 1
        for (int i = cnt[0]; i < oneEnd; i++)
            nums[i] = 1;
        // 元素2
        for (int i = oneEnd; i < oneEnd + cnt[2]; i++)
            nums[i] = 2;
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
