package Main;

import java.util.Queue;
import java.util.Stack;
import java.util.LinkedList;

public class BSTree<E extends Comparable<E>> {
    private class Node {
        public E e;
        public Node left, right;

        public Node(E e) {
            this.e = e;
            left = null;
            right = null;
        }
    }

    private Node root;
    private int size;

    public BSTree() {
        root = null;
        size = 0;
    }

    public int size() {
        return size;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public void add(E e) {
        root = add(root, e);
        //add(root, e);
    }

    private Node add(Node node, E e) {
        if (node == null) {
            size++;
            return new Node(e);
        }

        if (e.compareTo(node.e) < 0)
            node.left = add(node.left, e);
        else if (e.compareTo(node.e) > 0)
            node.right = add(node.right, e);
        // 相等的话啥事不干

        return node;
    }
    /*private void add(Node node, E e) {
        if (node == null) {
            size++;
            node = new Node(e);
            return;
        }

        Node parent = node;
        while (node != null) {
            if (node.e.compareTo(e) > 0) {
                parent = node;
                node = node.left;
            } else if (node.e.compareTo(e) < 0) {
                parent = node;
                node = node.right;
            } else
                return;
        }

        if (parent.e.compareTo(e) > 0) {
            size++;
            parent.left = new Node(e);
        } else {
            size++;
            parent.right = new Node(e);
        }
    }*/

    public boolean contains(E e) {
        return contains(root, e);
    }

    private boolean contains(Node node, E e) {
        if (node == null)
            return false;

        if (node.e.compareTo(e) > 0)
            return contains(node.left, e);
        else if (node.e.compareTo(e) < 0)
            return contains(node.right, e);
        else
            return true;
    }

    public void preOrder() {
        preOrder(root);
    }

    private void preOrder(Node node) {
        if (node == null)
            return;

        System.out.println(node.e);
        preOrder(node.left);
        preOrder(node.right);
    }

    // 前序遍历非递归算法
    public void preOrderNR() {
        Stack<Node> stack = new Stack();
        stack.push(root);
        while (!stack.isEmpty()) {
            Node cur = stack.pop();
            System.out.println(cur.e);

            if (cur.right != null)
                stack.push(cur.right);

            if (cur.left != null)
                stack.push(cur.left);
        }
    }

    public void inOrder() {
        inOrder(root);
    }

    private void inOrder(Node node) {
        if (node == null)
            return;

        preOrder(node.left);
        System.out.println(node.e);
        preOrder(node.right);
    }

    public void postOrder() {
        postOrder(root);
    }

    private void postOrder(Node node) {
        if (node == null)
            return;

        preOrder(node.left);
        preOrder(node.right);
        System.out.println(node.e);
    }

    // 层序遍历
    public void levelOrder() {
        // JAVA 的队列只是提供了一个接口，具体实现需要自己选择一个底层数据结构
        Queue<Node> q = new LinkedList<>();
        q.add(root);
        while (!q.isEmpty()) {
            Node cur = q.remove();
            System.out.println(cur.e);

            if (cur.left != null)
                q.add(cur.left);

            if (cur.right != null)
                q.add(cur.right);
        }
    }

    // 寻找二分搜索树的最小元素
    public E minimum() {
        if (size == 0)
            throw new IllegalArgumentException("BST is empty!");

        //return minimum(root).e;
        return minimumNR(root).e;
    }

    private Node minimum(Node node) {
        if (node.left == null)
            return node;

        return minimum(node.left);
    }

    private Node minimumNR(Node node) {
        while (node.left != null)
            node = node.left;

        return node;
    }

    public E maximum() {
        if (size == 0)
            throw new IllegalArgumentException("BST is empty!");

        return maximum(root).e;
    }

    private Node maximum(Node node) {
        if (node.right == null)
            return node;

        return maximum(node.right);
    }

    private Node maximumNR(Node node) {
        while (node.right != null)
            node = node.right;

        return node;
    }

    // 从二分搜索树中删除最小值节点，并返回最小节点的值
    public E removeMin() {
        E ret = minimum();
        root = removeMin(root);

        return ret;
    }

    // 删除掉以 node 为根的二分搜索树中的最小结点
    // 同时返回删除结点后新的二分搜索树的根
    private Node removeMin(Node node) {
        if (node.left == null) {
            Node rightNode = node.right;
            node.right = null;
            size--;
            return rightNode;
        }

        node.left = removeMin(node.left);
        return node;
    }

    public E removeMax() {
        E ret = maximum();
        root = removeMax(root);

        return ret;
    }

    private Node removeMax(Node node) {
        if (node.right == null) {
            Node leftNode = node.left;
            node.left = null;
            size--;
            return leftNode;
        }

        node.right = removeMax(node.right);
        return node;
    }

    public void remove(E e) {
        root = remove(root, e);
    }

    // 删除掉以 node 为根的二分搜索树中值为 e 的结点
    // 返回删除结点后新的二分搜索树的根
    private Node remove(Node node, E e) {
        if (node == null)
            return null;

        if (node.e.compareTo(e) > 0) {
            node.left = remove(node.left, e);
            return node;
        } else if (node.e.compareTo(e) < 0) {
            node.right = remove(node.right, e);
            return node;
        }
        // 上面都是寻找待删除结点的操作，下面才是真正找到了结点进行删除
        else {
            // 只有单颗子树的情况
            if (node.left == null) {
                Node rightNode = node.right;
                node.right = null;
                size--;
                return rightNode;
            }
            if (node.right == null) {
                Node leftNode = node.left;
                node.left = null;
                size--;
                return leftNode;
            }
            // 左右子树都有的情况
            // 找到比待删除结点大的最小结点（右子树的最小结点）并用其替换待删除的结点
            Node successor = minimum(node.right);
            successor.right = removeMin(node.right); // 注意，size 已经在 removeMin 中维护了
            successor.left = node.left;
            node.left = node.right = null;

            return successor;
        }
    }

    @Override
    public String toString() {
        StringBuilder res = new StringBuilder();
        generateBSTString(root, 0, res);
        return res.toString();
    }

    private void generateBSTString(Node node, int depth, StringBuilder res) {
        if (node == null) {
            res.append(generaDepthString(depth) + "null\n");
            return;
        }

        res.append(generaDepthString(depth) + node.e + "\n");
        generateBSTString(node.left, depth + 1, res);
        generateBSTString(node.right, depth + 1, res);
    }

    private String generaDepthString(int depth) {
        StringBuilder res = new StringBuilder();
        for (int i = 0; i < depth; i++)
            res.append("--");
        return res.toString();
    }
}
