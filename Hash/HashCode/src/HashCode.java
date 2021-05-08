import java.util.HashSet;
import java.util.HashMap;

public class HashCode {
    public static void main(String[] args) {
        int a = 42;
        System.out.println(((Integer) a).hashCode());

        int b = -42;
        System.out.println(((Integer) b).hashCode());

        double c = 3.1415926;
        System.out.println(((Double) c).hashCode());

        String d = "Imooc";
        System.out.println(d.hashCode());

        Student stu = new Student(3, 2, "BOBO", "liu");
        System.out.println(stu.hashCode());

        HashSet<Student> set = new HashSet<>();
        set.add(stu);

        HashMap<Student, Integer> scores = new HashMap<>();
        scores.put(stu, 100);
    }
}
