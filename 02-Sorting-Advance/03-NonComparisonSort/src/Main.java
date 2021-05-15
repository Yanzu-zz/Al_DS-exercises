import java.util.Random;

public class Main {
    // 验证计数排序算法的正确性和稳定性
    private static void checkStability(Student[] students) {
        int n = students.length;
        for (int i = 1; i < n; i++) {
            if (students[i - 1].getScore() > students[i].getScore())
                throw new RuntimeException("Counting Sort failed");

            // 查看是否稳定，排序方式是暴力写死的名字顺序
            if (students[i - 1].getScore() == students[i].getScore()) {
                if (students[i - 1].getName().compareTo(students[i].getName()) > 0)
                    throw new RuntimeException("Non-Stable counting sort");
            }
        }
    }

    public static void main(String[] args) {
        int n = 26 * 26 * 26 * 26;
        // 初始化每个学生的数据
        Student[] students = new Student[n];
        int k = 0; // 为每个学生单独赋值的游标
        Random random = new Random();
        for (char c1 = 'a'; c1 <= 'z'; c1++)
            for (char c2 = 'a'; c2 <= 'z'; c2++)
                for (char c3 = 'a'; c3 <= 'z'; c3++)
                    for (char c4 = 'a'; c4 <= 'z'; c4++)
                        students[k++] = new Student("" + c1 + c2 + c3 + c4, random.nextInt(101));

        // 计数排序过程
        int R = 101;

        // 获取每组学生分数出现的频次，O(n)
        int cnt[] = new int[R];
        for (Student student : students)
            cnt[student.getScore()]++; // 初始化每个学生不同分数的个数数组

        // 计算每组分数的边界数组，O(R)
        int[] index = new int[R + 1];
        for (int i = 0; i < R; i++)
            index[i + 1] = index[i] + cnt[i];

        // 进行计数排序（是稳定的），O(n)
        Student[] temp = new Student[n]; // 需要开一个辅助数组
        for (Student student : students)
            temp[index[student.getScore()]++] = student; // 操作完后数组就是有序的

        // 覆盖原数组，O(n)
        for (int i = 0; i < n; i++)
            students[i] = temp[i];

        // 故这里我们写的计数排序时间复杂度是：O(n + R)

        // 验证我们的排序是否正确
        checkStability((students));
    }
}
