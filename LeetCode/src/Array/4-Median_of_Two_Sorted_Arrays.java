package Array;

class Solution4 {
    public static double findMedianSortedArrays(int[] nums1, int[] nums2) {
        int m = nums1.length;
        int n = nums2.length;
        int nums3[] = new int[m + n];

        int i = 0, j = 0, k = 0;
        for (int x = 0; x < m + n; x++) {
            if (i >= m) {
                nums3[k++] = nums2[j++];
                continue;
            } else if (j >= n) {
                nums3[k++] = nums1[i++];
                continue;
            } else if (nums1[i] >= nums2[j]) {
                nums3[k++] = nums2[j++];
            } else if (nums1[i] < nums2[j]) {
                nums3[k++] = nums1[i++];
            }
        }

        double ret;
        double mid = (m + n) / 2;
        if ((m + n) % 2 == 0) {
            ret = nums3[(int) mid] + nums3[(int) (mid - 1)];
            ret /= 2;
        } else {
            ret = nums3[(int) Math.floor(mid)];
        }
        return ret;
    }

    public static void main(String[] args) {
        int[] nums1 = {1, 3}, nums2 = {2};
        double ret = findMedianSortedArrays(nums1, nums2);
        System.out.println(ret);

        int[] nums3 = {1, 2}, nums4 = {3, 4};
        double ret2 = findMedianSortedArrays(nums3, nums4);
        System.out.println(ret2);
    }
}