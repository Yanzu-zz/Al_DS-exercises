package Array;


import java.util.*;

class Solution15 {
    public static List<List<Integer>> threeSum(int[] nums) {
        List<List<Integer>> lists = new ArrayList<>();
        if (nums.length < 3) {
            return lists;
        }

        Integer[] arr = new Integer[nums.length];
        for (int i = 0; i < nums.length; i++)
            arr[i] = nums[i];

        int i = 0, j = i + 1, k = i + 2;
        Set<List<Integer>> set = new HashSet<>();
        while (k < nums.length) {
            while (j < k) {
                int curVal = arr[i] + arr[j] + arr[k];
                if (curVal == 0) {
                    set.add(Arrays.asList(arr[i], arr[j], arr[k]));
                }
                j++;
            }
            j = i + 1;
            k++;
        }

        lists.addAll(set);
        return lists;
    }

    public static void main(String[] args) {
        //List<List<Integer>> lists = new ArrayList<>();
        //int[] arr = {-1, 0, 1, 2, -1, -4};
        //lists = threeSum(arr);
        //System.out.println(Arrays.toString(lists.toArray()));

        //List<List<Integer>> lists2 = new ArrayList<>();
        //int[] arr2 = {0, 0, 0, 0};
        //lists2 = threeSum(arr2);
        //System.out.println(Arrays.toString(lists2.toArray()));

        List<List<Integer>> lists3 = new ArrayList<>();
        int[] arr3 = {-1, 0, 1, 0};
        lists3 = threeSum(arr3);
        System.out.println(Arrays.toString(lists3.toArray()));
    }
}
