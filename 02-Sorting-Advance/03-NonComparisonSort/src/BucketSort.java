import java.util.Arrays;
import java.util.Collections;
import java.util.LinkedList;

public class BucketSort {
    private BucketSort() {
    }

    // 分为 B 个桶
    public static void sort(Integer[] arr, int B) {
        if (B <= 1)
            throw new IllegalArgumentException("B must be larger than 1");

        Integer[] temp = new Integer[arr.length];
        sort(arr, 0, arr.length - 1, B, temp);
    }


    // 基于 MSD 的桶排序
    private static void sort(Integer[] arr, int left, int right, int B, Integer[] temp) {
        // 处理边界条件
        if (left >= right)
            return;

        // 找到数组中的最大最小值
        int maxv = Integer.MIN_VALUE, minv = Integer.MAX_VALUE;
        for (int item : arr) {
            maxv = Math.max(maxv, item);
            minv = Math.min(minv, item);
        }

        if (maxv == minv)
            return;

        // 向上取整，这里不用 ceil 函数的写法
        int d = (maxv - minv + 1) / B + ((maxv - minv + 1) % B > 0 ? 1 : 0);
        int[] cnt = new int[B]; // +1 是因为还有空的可能
        int[] index = new int[B + 1];

        // 计算出每个桶中元素的个数
        for (int i = left; i <= right; i++)
            cnt[(arr[i] - minv) / d]++;

        // 计算每组分数的边界数组，O(R)
        for (int i = 0; i < B + 1; i++)
            index[i + 1] = index[i] + cnt[i];

        // 将不同元素分进其对应的桶内
        for (int i = left; i <= right; i++) {
            int p = (arr[i] - minv) / d;
            temp[left + index[p]++] = arr[i];
        }

        // 覆盖原数组，这里要注意偏移量
        System.arraycopy(temp, 0, arr, 0, temp.length);

        // 继续递归下去
        sort(arr, left, left + index[0] - 1, B, temp);
        for (int i = 0; i < B; i++)
            sort(arr, left + index[i], left + index[i + 1] - 1, B, temp);
    }

    // 更简单的桶排序（把数据分成若干千桶，直接对每一个桶中的元素进行排序）
    // c 表示每一个桶中的元素取值范围
    private static void sort2(Integer[] arr, int c) {
        if (c <= 0)
            throw new IllegalArgumentException("c must be > 0");

        // 计算需要分几个桶
        int B = arr.length / c + (arr.length % c > 0 ? 1 : 0);

        // 开辅助空间（初始化需要分元素的桶）
        LinkedList<Integer>[] buckets = new LinkedList[B];
        for (int i = 0; i < B; i++)
            buckets[i] = new LinkedList<>();

        // 找到数组中的最大最小值
        int maxv = Integer.MIN_VALUE, minv = Integer.MAX_VALUE;
        for (int item : arr) {
            maxv = Math.max(maxv, item);
            minv = Math.min(minv, item);
        }

        // 找到最大值和最小值之后，就能把遍历到的元素扔到对应的桶中了
        for (int e : arr)
            buckets[(e - minv) / c].add(e);
        // 加入桶中后，对每个桶进行排序
        for (int i = 0; i < B; i++)
            Collections.sort(buckets[i]);

        // 最后顺序的把每个元素赋值回给原数组
        int index = 0;
        for (int i = 0; i < B; i++)
            for (int e : buckets[i])
                arr[index++] = e;
    }

    public static void main(String[] args) {
        Integer[] arr1 = {6, 12, 28, 9, 33, 69};
        sort(arr1, 2);
        System.out.println(Arrays.toString(arr1));
    }
}
