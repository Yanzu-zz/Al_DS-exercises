import java.util.Arrays;

// MSD 基数排序
public class MSDSort {
    private MSDSort() {
    }

    public static void sort(String[] arr) {
        String[] temp = new String[arr.length]; // 需要开一个辅助数组
        sort(arr, 0, arr.length - 1, 0, temp);
    }

    // r 表示以某个位置的字符，递归基数排序处理 arr[left, right]
    private static void sort(String[] arr, int left, int right, int r, String[] temp) {
        // 递归到底
        if (left >= right)
            return;

        // 基于第 r 位的字符进行计数排序
        int R = 256;
        int[] cnt = new int[R + 1]; // +1 是因为还有空的可能
        int[] index = new int[R + 2];

        // 先计算 r 位置的数组，每组不同数据的个数
        for (int i = left; i <= right; i++)
            cnt[r >= arr[i].length() ? 0 : (arr[i].charAt(r) + 1)]++; // 当我们处理的元素为空元素时，记到 位置0 上去

        // 计算每组分数的边界数组，O(R)
        for (int i = 0; i < R + 1; i++)
            index[i + 1] = index[i] + cnt[i];

        // 进行计数排序覆盖（是稳定的），O(n)
        for (int i = left; i <= right; i++) {
            int p = r >= arr[i].length() ? 0 : (arr[i].charAt(r) + 1);
            temp[left + index[p]++] = arr[i];
        }

        // 覆盖原数组，这里要注意偏移量
        System.arraycopy(temp, 0, arr, 0, temp.length);

        // 继续递归下去
        for (int i = 0; i < R; i++)
            sort(arr, left + index[i], left + index[i + 1] - 1, r + 1, temp);
    }

    public static void main(String[] args) {
        String[] arr1 = {"BCA", "CBAA", "AC", "BADFE", "ABC", "CBA"};
        sort(arr1);
        System.out.println(Arrays.toString(arr1));
    }
}