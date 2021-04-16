import java.util.ArrayList;

public class AVLTree<K extends Comparable<K>, V> {
    private class Node {
        public K key;
        public V value;
        public Node left, right;
        public int height;

        public Node(K key, V value) {
            this.key = key;
            this.value = value;
            left = null;
            right = null;
            height = 1;
        }
    }

    private Node root;
    private int size;

    public AVLTree() {
        root = null;
        size = 0;
    }

    public int getSize() {
        return size;
    }

    public boolean isEmpty() {
        return size == 0;
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

    // 判断该树是否为平衡二叉树
    public boolean isBalanced() {
        return isBalanced(root);
    }

    // 判断当前的树是否平衡
    private boolean isBalanced(Node node) {
        if (node == null)
            return true;

        int balancedFactor = getBalanceFactor(node);
        if (Math.abs(balancedFactor) > 1)
            return false;

        return isBalanced(node.left) && isBalanced(node.right);
    }

    // 获得子树高度
    private int getHeight(Node node) {
        if (node == null)
            return 0;
        return node.height;
    }

    // 获取以 node 为根的数的平衡因子
    private int getBalanceFactor(Node node) {
        if (node == null)
            return 0;
        return getHeight(node.left) - getHeight(node.right);
    }

    // 对结点 y 进行向右旋转操作，返回旋转后新的根结点
    private Node rightRotate(Node y) {
        Node x = y.left;
        Node T3 = x.right;

        // 开始右旋
        x.right = y;
        y.left = T3;

        // 更新结点的 height 值
        // 注意，转完后 y 是 x 的右子树，故要先更新 y 的 height 再更新 x 的
        y.height = Math.max(getHeight(y.left), getHeight(y.right)) + 1;
        x.height = Math.max(getHeight(x.left), getHeight(x.right)) + 1;

        return x;
    }

    // 对结点 y 进行向左旋转操作，返回旋转后新的根结点
    private Node leftRotate(Node y) {
        Node x = y.right;
        Node T3 = x.left;

        // 向左转
        x.left = y;
        y.right = T3;

        // 更新height
        y.height = Math.max(getHeight(y.left), getHeight(y.right)) + 1;
        x.height = Math.max(getHeight(x.left), getHeight(x.right)) + 1;

        return x;
    }

    public void add(K key, V value) {
        root = add(root, key, value);
    }

    // 向以 node 为根的二分搜索树中插入元素（key, value），递归算法
    // 返回插入新结点后二分搜索树的根
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

        // 更新 height
        node.height = 1 + Math.max(getHeight(node.left), getHeight(node.right));

        // 计算平衡因子
        int balanceFactor = getBalanceFactor(node);
        if (Math.abs(balanceFactor) > 1)
            System.out.println("unbalanced: " + balanceFactor);

        // 平衡维护
        // 下面的判断就是在左侧的左侧多插入了一个结点使得树不平衡，进行右旋转
        if (balanceFactor > 1 && getBalanceFactor(node.left) >= 0)
            return rightRotate(node);

        // 右子树多加了结点
        if (balanceFactor < -1 && getBalanceFactor(node.right) <= 0)
            return leftRotate(node);

        return node;
    }

    public static void main(String[] args) {
        System.out.println("Pride and Prejudice");

    }
}
