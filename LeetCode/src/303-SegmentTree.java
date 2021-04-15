/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * int param_1 = obj.sumRange(left,right);
 */

class NumArray {
    private interface Merger<E> {
        E merge(E a, E b); // merge 传入的 a和b，然后返回去
    }

    private class SegmentTree<E> {
        private E[] data;
        private E[] tree;
        // 在初始化的时候就定义好了用户是如何指定两个线段子树是如何融合的（如加起来，或喷不同颜色等）
        private Merger<E> merger;

        public SegmentTree(E[] arr, Merger<E> merger) {
            this.merger = merger;// 这里是求和线段树，故这个merger是吧两个线段树加起来
            data = (E[]) new Object[arr.length];
            System.arraycopy(arr, 0, data, 0, arr.length);

            // 线段树只需要开 4*n 的空间就能容下所有数据
            // 即使有些浪费也无所谓，用空间换时间
            tree = (E[]) new Object[4 * arr.length];
            buildSegmentTree(0, 0, data.length - 1);
        }

        // 初始化线段树
        // 在 treeIndex（即数组第几个索引） 的位置创建表示区间 [l...r] 的线段树（以求和为例子）
        private void buildSegmentTree(int treeIndex, int l, int r) {
            if (l == r) {
                tree[treeIndex] = data[l];
                return;
            }

            int leftTreeIndex = leftChild(treeIndex);
            int rightTreeIndex = rightChild(treeIndex);

            // int mid = (l + r) / 2; // 这样写当l，r很大时可能会整形溢出
            int mid = l + (r - l) / 2; // 标准解决方法

            // 创建的时候先递归地把子树的值都给处理完先
            buildSegmentTree(leftTreeIndex, l, mid);
            buildSegmentTree(rightTreeIndex, mid + 1, r);

            // 然后父结点就只需把左右子树的和加起来就得到了线段树（后序遍历）
            tree[treeIndex] = merger.merge(tree[leftTreeIndex], tree[rightTreeIndex]);
        }

        public int getSize() {
            return data.length;
        }

        public E get(int index) {
            if (index < 0 || index >= data.length)
                throw new IllegalArgumentException("Index is illegal.");
            return data[index];
        }

        // 返回完全二叉树的数组表示中，一个索引所表示的元素的左孩子节点的索引
        private int leftChild(int i) {
            // 因为数组从0开始，故左孩子节点为 2*i+1
            return 2 * i + 1;
        }

        private int rightChild(int i) {
            // 因为数组从0开始，故左孩子节点为 2*i+1
            return 2 * i + 2;
        }

        // 线段树区间查询
        // 返回区间 [queryL, queryR] 的值
        public E query(int queryL, int queryR) {
            if (queryL < 0 || queryL >= data.length || queryR < 0 || queryR >= data.length || queryL > queryR)
                throw new IllegalArgumentException("Index is illegal.");

            return query(0, 0, data.length - 1, queryL, queryR);
        }

        // 在以 treeID 为根的线段树中 [l...r] 的范围里，搜索区间 [query...queryR] 的值
        private E query(int treeIndex, int l, int r, int queryL, int queryR) {
            if (l == queryL && r == queryR)
                return tree[treeIndex];

            int mid = l + (r - l) / 2;
            int leftTreeIndex = leftChild(treeIndex);
            int rightTreeIndex = rightChild(treeIndex);

            // 如果需要查询的区间左值比 mid 大，那么左子树完全不用管了
            if (queryL >= mid + 1)
                return query(rightTreeIndex, mid + 1, r, queryL, queryR);
            else if (queryR <= mid) // 这个同理
                return query(leftTreeIndex, l, mid, queryL, queryR);

            // 而如果需要查询的区间在左子树有一点，右子树也有一点，就麻烦点
            E leftResult = query(leftTreeIndex, l, mid, queryL, mid);
            E rightResult = query(rightTreeIndex, mid + 1, r, mid + 1, queryR);

            // 最后按照业务需要返回即可
            return merger.merge(leftResult, rightResult);
        }

        @Override
        public String toString() {
            StringBuilder res = new StringBuilder();
            res.append('[');
            for (int i = 0; i < tree.length; i++) {
                if (tree[i] != null)
                    res.append(tree[i]);
                else
                    res.append("null");

                if (i != tree.length - 1)
                    res.append(", ");
            }
            res.append("]");
            return res.toString();
        }
    }

    private SegmentTree<Integer> segmentTree;

    public NumArray(int[] nums) {
        if (nums.length > 0) {
            Integer[] data = new Integer[nums.length];
            for (int i = 0; i < nums.length; i++)
                data[i] = nums[i];

            segmentTree = new SegmentTree<>(data, (a, b) -> a + b);
        }
    }

    public int sumRange(int i, int j) {
        if (segmentTree == null)
            throw new IllegalArgumentException("Segment Tree is null");

        return segmentTree.query(i, j);
    }
}
