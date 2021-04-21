package Main;

import Main.BSTree;

public class Main {
    public static void main(String[] args) {
        BSTree<Integer> bst = new BSTree<Integer>();
        int[] nums = {5, 3, 6, 8, 4, 2};
        for (int num : nums)
            bst.add(num);

        bst.preOrder();
        System.out.println();
        bst.preOrderNR();
        System.out.println();
        //System.out.println(bst);
        bst.levelOrder();
    }
}
