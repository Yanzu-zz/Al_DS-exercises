import java.util.Arrays;

public class LSDSort {
    private LSDSort() {
    }

    // W 为固定长度，因为LSD算法只能处理等长的数据
    public static void sort(String[] arr, int W) {
        for (String s : arr)
            if (s.length() != W)
                throw new IllegalArgumentException("All String's length must be the same.");

        // 基于第 r位的字符进行计数排序
        int R = 256;
        int[] cnt = new int[R];
        int[] index = new int[R + 1];
        String[] temp = new String[arr.length]; // 需要开一个辅助数组

        for (int r = W - 1; r >= 0; r--) {
            Arrays.fill(cnt, 0); // 重置 cnt 数组
            // index 默认全是0，而下面的操作是基于索引0进行计算的，我们这样索引0永远是0，故不用重置 index 数组
            // temp 也是会覆盖正确的值，因此也不用担心

            for (String s : arr)
                cnt[s.charAt(r)]++; // 计算每位排序组的字符个数

            // 计算每组分数的边界数组，O(R)
            for (int i = 0; i < R; i++)
                index[i + 1] = index[i] + cnt[i];

            // 进行计数排序（是稳定的），O(n)
            for (String s : arr)
                temp[index[s.charAt(r)]++] = s; // 操作完后数组就是有序的

            // 覆盖原数组，O(n)
            System.arraycopy(temp, 0, arr, 0, arr.length);
        }
    }
    // 故这里我们写的计数排序时间复杂度是：O(W * (n+R)) => O(n)，但前面的常数 W 很大，别忽略

    public static void main(String[] args) {
        String[] arr1 = {"BCA", "CAB", "ACB", "BAC", "ABC", "CBA"};
        sort(arr1, 3);
        System.out.println(Arrays.toString(arr1));
    }
}
