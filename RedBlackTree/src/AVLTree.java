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
        //if (Math.abs(balanceFactor) > 1)
        //    System.out.println("unbalanced: " + balanceFactor);

        // 平衡维护
        // LL
        if (balanceFactor > 1 && getBalanceFactor(node.left) >= 0)
            return rightRotate(node);

        // RR
        if (balanceFactor < -1 && getBalanceFactor(node.right) <= 0)
            return leftRotate(node);

        // LR
        if (balanceFactor > 1 && getBalanceFactor(node.left) < 0) {
            // 先对左子树进行左转操作，然后就和处理普通的 LL 一样了
            node.left = leftRotate(node.left);
            return rightRotate(node);
        }

        // RL
        if (balanceFactor < -1 && getBalanceFactor(node.right) > 0) {
            node.right = rightRotate(node.right);
            return leftRotate(node);
        }

        return node;
    }

    private Node remove(Node node, K key) {
        if (node == null)
            return null;

        Node retNode;
        if (key.compareTo(node.key) < 0) {
            node.left = remove(node.left, key);
            retNode = node;
        } else if (key.compareTo(node.key) > 0) {
            node.right = remove(node.right, key);
            retNode = node;
        } else {
            if (node.left == null) {
                Node rightNode = node.right;
                node.right = null;
                size--;
                retNode = rightNode;
            } else if (node.right == null) {
                Node leftNode = node.left;
                node.left = null;
                size--;
                retNode = leftNode;
            } else {
                Node successor = minimum(node.right);
                successor.right = remove(node.right, successor.key);
                successor.left = node.left;

                node.left = node.right = null;
                retNode = successor;
            }
        }

        if (retNode == null)
            return null;

        // 更新 height
        retNode.height = 1 + Math.max(getHeight(retNode.left), getHeight(retNode.right));

        // 计算平衡因子
        int balanceFactor = getBalanceFactor(retNode);

        // 平衡维护
        // LL
        if (balanceFactor > 1 && getBalanceFactor(retNode.left) >= 0)
            return rightRotate(retNode);

        // RR
        if (balanceFactor < -1 && getBalanceFactor(retNode.right) <= 0)
            return leftRotate(retNode);

        // LR
        if (balanceFactor > 1 && getBalanceFactor(retNode.left) < 0) {
            // 先对左子树进行左转操作，然后就和处理普通的 LL 一样了
            retNode.left = leftRotate(retNode.left);
            return rightRotate(retNode);
        }

        // RL
        if (balanceFactor < -1 && getBalanceFactor(retNode.right) > 0) {
            retNode.right = rightRotate(retNode.right);
            return leftRotate(retNode);
        }

        return retNode;
    }
}
