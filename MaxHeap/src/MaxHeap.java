import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;

public class MaxHeap<E extends Comparable<E>> {
    private ArrayList<E> data;

    public MaxHeap(int capacity) {
        data = new ArrayList<>(capacity);
    }

    public MaxHeap(E[] arr) {
        data = new ArrayList<>(arr.length);
        //for (E i : arr)
        //    data.add(i);
        data.addAll(Arrays.asList(arr));

        for (int i = parent(arr.length - 1); i >= 0; i--)
            siftDown(i);
    }

    public MaxHeap() {
        data = new ArrayList<>();
    }

    public int size() {
        return data.size();
    }

    public boolean isEmpty() {
        return data.isEmpty();
    }

    // 返回 index 处的双亲元素
    private int parent(int index) {
        if (index == 0)
            return 0;
        return (index - 1) / 2; // 数组从 0 开始
    }

    private int leftChild(int index) {
        return index * 2 + 1;
    }

    private int rightChild(int index) {
        return index * 2 + 1;
    }

    public void add(E e) {
        data.add(e);
        siftUp(data.size() - 1);
    }

    // 上浮
    private void siftUp(int k) {
        while (k > 0 && data.get(parent(k)).compareTo(data.get(k)) < 0) {
            Collections.swap(data, k, parent(k));
            k = parent(k);
        }
    }

    // 下沉
    private void siftDown(int k) {
        while (leftChild(k) < data.size()) {
            int j = leftChild(k);
            // 比较左右两个孩子的大小
            if (j + 1 < data.size() && data.get(j + 1).compareTo(data.get(j)) > 0)
                j++;

            if (data.get(k).compareTo(data.get(j)) >= 0)
                break;

            Collections.swap(data, k, j);
            k = j; // 继续下沉
        }
    }

    // 获取堆中最大元素
    public E findMax() {
        if (data.size() == 0)
            throw new IllegalArgumentException("Cannot findMax when heap is empty");

        return data.get(0);
    }

    public E extractMax() {
        E ret = findMax();
        Collections.swap(data, 0, data.size() - 1);
        data.remove(data.size() - 1);

        siftDown(0);
        return ret;
    }

    // 去除堆中最大元素，并且替换成元素 e
    public E replace(E e) {
        E ret = findMax();

        data.set(0, e);
        siftDown(0);

        return ret;
    }


}
