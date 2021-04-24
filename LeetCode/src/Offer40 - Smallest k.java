import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;

class Solution40 {
    public int getLeastNumbers(int[] arr, int k) {
        // 注意，维护 前k小 的元素用的是最大堆
        PriorityQueue<Integer> pq = new PriorityQueue<>();
        for (int i = 0; i < k; i++)
            pq.enqueue(arr[i]);

        // 维护堆
        for (int i = k; i < arr.length; i++) {
            // 如当前元素比堆顶元素还小，就把堆顶元素 pop，然后加入新元素
            if (!pq.isEmpty() && arr[i] < pq.getFront()) {
                pq.dequeue();
                pq.enqueue(arr[i]);
            }
        }

        int[] res = new int[k];
        for (int i = 0; i < k; i++)
            res[i] = pq.dequeue();

        return res[k - 1];
    }

    public interface Queue<E> {
        int getSize();

        boolean isEmpty();

        void enqueue(E e);

        E dequeue();

        E getFront();
    }

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

    public class PriorityQueue<E extends Comparable<E>> implements Queue<E> {
        private MaxHeap<E> maxHeap;

        public PriorityQueue() {
            maxHeap = new MaxHeap<>();
        }

        @Override
        public int getSize() {
            return maxHeap.size();
        }

        @Override
        public boolean isEmpty() {
            return maxHeap.isEmpty();
        }

        @Override
        public E getFront() {
            return maxHeap.findMax();
        }

        @Override
        public void enqueue(E e) {
            maxHeap.add(e);
        }

        @Override
        public E dequeue() {
            //  判断边界问题里面代码有了，这里就不用重复写了
            return maxHeap.extractMax();
        }
    }
}