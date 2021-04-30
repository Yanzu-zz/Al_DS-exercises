package Array;

import java.util.*;

class Solution46 {
    public static List<List<Integer>> permute(int[] nums) {
        List<List<Integer>> ret = new ArrayList<>();
        Deque<Integer> path = new ArrayDeque<>();
        boolean[] book = new boolean[nums.length];
        for (int i = 0; i < nums.length; i++)
            book[i] = false;

        dfs(nums, 0, book, path, ret);
        return ret;
    }

    private static void dfs(int[] nums, int step, boolean[] book, Deque<Integer> path, List<List<Integer>> ret) {
        if (step == nums.length) {
            ret.add(new ArrayList<>(path));
            return;
        }

        for (int i = 0; i < nums.length; i++) {
            // 不在里面才能进行处理
            if (!book[i]) {
                book[i] = true;
                path.addLast(nums[i]);
                dfs(nums, step + 1, book, path, ret);
                book[i] = false;
                path.removeLast();
            }
        }
    }

    public static void main(String[] args) {
        int[] arr1 = {1, 2, 3};
        List<List<Integer>> list1;
        list1 = permute(arr1);
        System.out.println(Arrays.asList(list1).toString());
    }
}