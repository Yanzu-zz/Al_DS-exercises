import java.util.Random;

public class HeapSort {
    private HeapSort() {}

    public static <E extends Comparable<E>> void sort(E[] data) {
        MaxHeap<E> maxHeap = new MaxHeap<>();
        for (E e : data)
            maxHeap.add(e);

        for (int i = data.length - 1; i >= 0; i--)
            data[i] = maxHeap.extractMax();

        for (int i = 1; i < data.length; i++)
            if (data[i - 1].compareTo(data[i]) > 0)
                throw new IllegalArgumentException("Error");
    }

    public static <E extends Comparable<E>> void sort2(E[] data) {
        if (data.length <= 1) return;
        for (int i = (data.length - 2) / 2; i >= 0; i--)
            siftDown(data, i, data.length);

        for (int i = data.length - 1; i >= 0; i--) {
            swap(data, 0, i);
            siftDown(data, 0, i);
        }

        for (int i = 1; i < data.length; i++)
            if (data[i - 1].compareTo(data[i]) > 0)
                throw new IllegalArgumentException("Error");
    }

    // 对 data[0,n) 所形成的最大堆中，索引 k 的元素，执行 siftDown
    private static <E extends Comparable<E>> void siftDown(E[] data, int k, int n) {
        int j;
        while ((j = 2 * k + 1) < n) {
            // 比较左右两个孩子的大小
            if (j + 1 < n && data[j + 1].compareTo(data[j]) > 0)
                j++;

            if (data[k].compareTo(data[j]) >= 0)
                break;

            //Collections.swap(Arrays.asList(data), k, j);
            swap(data, k, j);
            k = j; // 继续下沉
        }
    }

    private static <E> void swap(E[] data, int i, int j) {
        E t = data[i];
        data[i] = data[j];
        data[j] = t;
    }

    public static void main(String[] args) {
        int n = 1000000;

        Random random = new Random();
        Integer[] testData = new Integer[n];
        for (int i = 0; i < n; i++)
            testData[i] = random.nextInt(Integer.MAX_VALUE);

        long startTime = System.nanoTime();
        sort(testData);
        long endTime = System.nanoTime();
        System.out.println("Common heap sort: "+(endTime - startTime) / 1000000000.0 + " s");


        for (int i = 0; i < n; i++)
            testData[i] = random.nextInt(Integer.MAX_VALUE);
        startTime = System.nanoTime();
        sort2(testData);
        endTime = System.nanoTime();
        System.out.println("Heap sort: " + (endTime - startTime) / 1000000000.0 + " s");
    }
}
