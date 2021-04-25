package Array;

class Solution33 {
    // 看到顺序要第一时间想到二分查找法
    // 但本题我觉得你要找到 旋转点 都要遍历一次数组了，那还不如直接遍历找答案
    public int search(int[] nums, int target) {
        int ret = -1;
        for (int i = 0; i < nums.length; i++) {
            if (nums[i] == target) {
                ret = i;
                break;
            }
        }

        return ret;
    }

    // 二分法实现
    /*public int search(int[] nums, int target) {
        int ret = -1;
        int left,right;

        return ret;
    }*/
}