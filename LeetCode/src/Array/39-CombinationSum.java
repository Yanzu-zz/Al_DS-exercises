package Array;

import java.util.*;

class Solution39 {
    public static List<List<Integer>> combinationSum(int[] candidates, int target) {
        List<List<Integer>> res = new ArrayList<>();
        Deque<Integer> path = new ArrayDeque<>();

        Arrays.sort(candidates); // 要剪枝就要先把数组排好序
        dfs(candidates, 0, target, path, res);
        return res;
    }

    /**
     * 不带剪枝版
     *
     * @param candidates 候选数组
     * @param begin      搜索起点
     * @param target     每减去一个元素，目标值变小
     * @param path       从根结点到叶子结点的路径，是一个栈
     * @param res        结果集列表
    private static void dfs(int[] candidates, int begin, int target, Deque<Integer> path, List<List<Integer>> res) {
    // 边界条件
    if (target < 0)
    return;
    if (target == 0) {
    res.add(new ArrayList<>(path));
    return;
    }

    for (int i = begin; i < candidates.length; i++) {
    path.addLast(candidates[i]);
    dfs(candidates, i, target - candidates[i], path, res);
    path.removeLast();
    }
    }
     */

    /**
     * 带剪枝版
     *
     * @param candidates 候选数组
     * @param begin      搜索起点
     * @param target     每减去一个元素，目标值变小
     * @param path       从根结点到叶子结点的路径，是一个栈
     * @param res        结果集列表
     */
    private static void dfs(int[] candidates, int begin, int target, Deque<Integer> path, List<List<Integer>> res) {
        if (target == 0) {
            res.add(new ArrayList<>(path));
            return;
        }

        for (int i = begin; i < candidates.length; i++) {
            if (target - candidates[i] < 0) break;

            path.addLast(candidates[i]);
            dfs(candidates, i, target - candidates[i], path, res);
            path.removeLast();
        }
    }

    public static void main(String[] args) {
        int[] arr1 = {2, 3, 6, 7};
        int target1 = 7;
        List<List<Integer>> list1;
        list1 = combinationSum(arr1, target1);
        System.out.println(Arrays.asList(list1).toString());

        int[] arr2 = {2, 3, 5};
        int target2 = 8;
        List<List<Integer>> list2;
        list2 = combinationSum(arr2, target2);
        System.out.println(Arrays.asList(list2).toString());
    }
}
