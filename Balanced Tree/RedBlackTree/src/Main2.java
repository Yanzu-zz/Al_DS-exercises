import java.util.ArrayList;

public class Main2 {
    public static void main(String[] args) {
        System.out.println("The Hobbit");
        String filename = "D:\\Front-End\\Github_Projects\\Al_DS-structure\\TestSource\\The Hobbit.txt";

        ArrayList<String> words = new ArrayList<>();
        if (FileOperation.readFile(filename, words)) {
            System.out.println("Total words: " + words.size());
            long startTime = System.nanoTime();
            RBTree<String, Integer> rbt = new RBTree<>();
            for (String word : words) {
                if (rbt.contains(word))
                    rbt.set(word, rbt.get(word) + 1);
                else
                    rbt.add(word, 1);
            }

            for (String word : words)
                rbt.contains(word);

            long endTime = System.nanoTime();
            System.out.println("RBT: " + (endTime - startTime) / 1000000000.0 + " s");
        }
    }
}
