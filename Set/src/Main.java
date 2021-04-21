import java.util.ArrayList;

public class Main {
    public static void main(String[] args) {
        String rootDir = "src\\";
        String fileName1 = rootDir + "Les_Miserables.txt";
        System.out.println(fileName1);
        ArrayList<String> words1 = new ArrayList<>();

        if (FileOperation.readFile(fileName1, words1)) {
            System.out.println("Total words: " + words1.size());

            BSTSet<String> set1 = new BSTSet<>();
            for (String word : words1)
                set1.add(word);
            System.out.println("Total different words: " + set1.getSize());
        }
    }
}
