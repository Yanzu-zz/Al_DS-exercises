package Array;

class Solution11 {
    public static int maxArea(int[] height) {
        int i = 0, j = height.length - 1;
        int maxLiter = 0;

        while (i < j) {
            int distance = j - i;
            boolean moveLeft = height[i] < height[j];
            int curArea = (moveLeft ? height[i] : height[j]) * distance;

            maxLiter = Math.max(curArea, maxLiter);

            if (moveLeft)
                i++;
            else
                j--;
        }

        return maxLiter;
    }

    public static void main(String[] args) {
        int[] arr = {1, 8, 6, 2, 5, 4, 8, 3, 7};
        int max = maxArea(arr);
        System.out.println(max);

        int[] arr2 = {4, 3, 2, 1, 4};
        int max2 = maxArea(arr2);
        System.out.println(max2);
    }
}
