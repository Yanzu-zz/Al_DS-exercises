import java.util.TreeMap;

public class Trie {
    private class Node {
        public boolean isWord;
        public TreeMap<Character, Node> next;

        public Node(boolean isWord) {
            this.isWord = isWord;
            next = new TreeMap<>();
        }

        public Node() {
            this(false);
        }
    }

    private Node root; // 字典树的根结点
    private int size; // 整颗字典树存储单词的数量

    public Trie() {
        root = new Node();
        size = 0;
    }

    public int getSize() {
        return size;
    }

    // 向 Trie 中添加一个新的单词 word
    public void add(String word) {
        Node cur = root;

        for (int i = 0; i < word.length(); i++) {
            // 下面就是插入新的字符结点了
            char c = word.charAt(i);
            // 如果不包含到下一结点的映射，new 一个
            if (cur.next.get(c) == null)
                cur.next.put(c, new Node());
            // 向下走
            cur = cur.next.get(c);
        }

        // 当循环结束后，cur 就来到了 word 字符串最后一个所处的结点位置
        // 此时不管它是否为别的单词的前缀，都把次结点标记为 isWord
        // 当然，有可能会有重复添加 word 的可能，故判断一下即可
        if (!cur.isWord) {
            cur.isWord = true;
            size++;
        }
    }

    // 查询单词 word 是否在 Trie 中
    public boolean contains(String word) {
        // 整体和添加的思路逻辑是一致的
        Node cur = root;
        for (int i = 0; i < word.length(); i++) {
            char c = word.charAt(i);
            if (cur.next.get(c) == null)
                return false;
            cur = cur.next.get(c);
        }

        return cur.isWord;
    }

    // 查询是否在 Trie 中有单词以 prefix 为前缀
    // 前缀搜索和单词搜索的逻辑非常非常相近，区别就是前缀搜索不判断所搜的字符串是否添加入了树中
    // 注意：一个单词也是这个单词的前缀
    public boolean isPrefix(String prefix) {
        Node cur = root;
        for (int i = 0; i < prefix.length(); i++) {
            char c = prefix.charAt(i);
            if (cur.next.get(c) == null)
                return false;
            cur = cur.next.get(c);
        }

        // 这里的逻辑自己好好体会下
        return true;
    }
}
