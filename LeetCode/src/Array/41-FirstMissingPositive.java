package Array;

import java.util.HashMap;
import java.util.Map;

class Solution {
    public static int firstMissingPositive(int[] nums) {
        Map<Integer, Integer> map = new HashMap<Integer, Integer>();

        for (int num : nums)
            map.put(num, num);

        int i = 0, res = 1;
        while (i < nums.length) {
            if (map.containsKey(res))
                res++;
            i++;
        }

        return res;
    }

    public static void main(String[] args) {
        int[] arr1 = {1, 2, 0};
        int t1 = firstMissingPositive(arr1);
        System.out.println(t1);
        System.out.println();
    }
}