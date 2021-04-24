import java.util.HashMap;

class Solution1 {
    public static int[] twoSum(int[] nums, int target) {
        HashMap<Integer, Integer> hashMap = new HashMap<>();

        for (int i = 0; i < nums.length; i++)
            hashMap.put(nums[i], i);

        int[] ret = new int[2];
        for (int i = 0; i < nums.length; i++) {
            if (hashMap.containsKey(target - nums[i]) && hashMap.get(target - nums[i]) != i) {
                ret[0] = i;
                ret[1] = hashMap.get(target - nums[i]);
                break;
            }
        }

        return ret;
    }

    public static void main(String[] args) {
        int[] arr = {3, 2, 4};
        int[] ret;
        ret = twoSum(arr, 6);

        for (int i : ret)
            System.out.println(i);
    }
}
