package test;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertTrue;

import java.util.ArrayList;
import java.util.Random;

import Main.BSTree;


public class SimpleBSTree {
    @Test
    public void orderTest() {
        BSTree<Integer> bst = new BSTree<Integer>();
        Random random = new Random();
        int n = 1000;

        for (int i = 0; i < n; i++)
            bst.add(random.nextInt(10000));

        ArrayList<Integer> nums = new ArrayList<>();
        while (!bst.isEmpty())
            nums.add(bst.removeMin());

        //System.out.println(nums);
        boolean isOrder = true;
        for (int i = 1; i < nums.size(); i++) {
            if (nums.get(i - 1) > nums.get(i)) {
                isOrder = false;
                break;
            }
        }
        assertTrue(isOrder);

        nums.clear();
        while (!bst.isEmpty())
            nums.add(bst.removeMax());

        isOrder = true;
        for (int i = 1; i < nums.size(); i++) {
            if (nums.get(i - 1) < nums.get(i)) {
                isOrder = false;
                break;
            }
        }
        assertTrue(isOrder);
    }
}
