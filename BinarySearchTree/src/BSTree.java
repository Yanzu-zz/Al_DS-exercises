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
