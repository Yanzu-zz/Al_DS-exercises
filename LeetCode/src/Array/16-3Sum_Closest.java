package Array;

class Solution16 {
    public static int threeSumClosest(int[] nums, int target) {
        int closetSection = Integer.MAX_VALUE;
        int ret = 0;

        for (int i = 0; i < nums.length; i++) {
            for (int j = i + 1; j < nums.length; j++) {
                for (int k = j + 1; k < nums.length; k++) {
                    int t = nums[i] + nums[j] + nums[k];
                    if (Math.abs(target - t) < closetSection) {
                        closetSection = Math.abs(target - t);
                        ret = t;
                    }
                }
            }
        }

        return ret;
    }

    public static void main(String[] args) {
        int[] arr = {-1, 2, 1, -4};
        int ret = threeSumClosest(arr, 1);
        System.out.println(ret);
    }
}