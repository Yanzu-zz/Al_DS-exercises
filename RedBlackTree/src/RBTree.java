import java.util.ArrayList;

class RBTree<K extends Comparable<K>, V> {
    private static final boolean RED = true;
    private static final boolean BLACK = false;

    private class Node {
        public K key;
        public V value;
        public Node left, right;
        public boolean color;

        public Node(K key, V value) {
            this.key = key;
            this.value = value;
            left = null;
            right = null;
            color = RED;
        }
    }

    private Node root;
    private int size;

    public RBTree() {
        root = null;
        size = 0;
    }

    public int getSize() {
        return size;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    // 设置这个函数的原因主要还是为了处理空结点
    // 空结点是黑色的，因为空结点肯定没融合，故不可能为红色
    private boolean isRed(Node node) {
        if (node == null)
            return BLACK;
        return node.color;
    }

    private Node leftRotate(Node node) {
        // 左旋转
        Node x = node.right;
        node.right = x.left;
        x.left = node;

        // 维持颜色
        x.color = node.color;
        node.color = RED;

        return x;
    }

    private Node rightRotate(Node node) {
        Node x = node.left;
        // 右旋转
        node.left = x.right;
        x.right = node;

        // 维持颜色
        x.color = node.color;
        node.color = RED;

        return x;
    }

    // 颜色翻转（要满足对应的形状，这个自己判断即可）
    private void flipColors(Node node) {
        node.color = RED;
        node.left.color = BLACK;
        node.right.color = BLACK;
    }

    private Node getNode(Node node, K key) {
        Node cur = node;
        while (cur != null) {
            if (key.compareTo(node.key) < 0)
                cur = cur.left;
            else if (key.compareTo(node.key) > 0)
                cur = cur.right;
            else
                return cur;
        }
        return null;
    }

    // 判断是否为一颗二叉搜索树
    public boolean isBST() {
        ArrayList<K> keys = new ArrayList<>();
        inOrder(root, keys);
        for (int i = 1; i < keys.size(); i++)
            if (keys.get(i - 1).compareTo((keys.get(i))) > 0)
                return false;
        return true;
    }

    private void inOrder(Node node, ArrayList<K> keys) {
        if (node == null)
            return;

        inOrder(node.left, keys);
        keys.add(node.key);
        inOrder(node.right, keys);
    }

    public void add(K key, V value) {
        root = add(root, key, value);
        root.color = BLACK; // 手动置根结点为黑色
    }

    public V remove(K key) {
        Node node = getNode(root, key);
        if (node != null) {
            root = remove(root, key);
            return node.value;
        }
        return null;
    }

    private Node minimum(Node node) {
        Node retNode = node;
        while (retNode != null)
            retNode = retNode.left;

        return retNode;
    }

    // 向以 node 为根的中插入元素（key, value），递归算法
    // 返回插入新结点后的根
    private Node add(Node node, K key, V value) {
        if (node == null) {
            size++;
            return new Node(key, value);
        }

        if (key.compareTo(node.key) < 0)
            node.left = add(node.left, key, value);
        else if (key.compareTo(node.key) > 0)
            node.right = add(node.right, key, value);
        else
            node.value = value; // 覆盖

        return node;
    }

    private Node remove(Node node, K key) {
        if (node == null)
            return null;

        Node retNode;
        if (key.compareTo(node.key) < 0) {
            node.left = remove(node.left, key);
            return node;
        } else if (key.compareTo(node.key) > 0) {
            node.right = remove(node.right, key);
            return node;
        } else {
            if (node.left == null) {
                Node rightNode = node.right;
                node.right = null;
                size--;
                return rightNode;
            } else if (node.right == null) {
                Node leftNode = node.left;
                node.left = null;
                size--;
                return leftNode;
            } else {
                Node successor = minimum(node.right);
                successor.right = remove(node.right, successor.key);
                successor.left = node.left;

                node.left = node.right = null;
                return successor;
            }
        }
    }
}
