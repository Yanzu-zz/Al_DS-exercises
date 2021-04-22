import java.util.ArrayList;

public class Main {
    public static void main(String[] args) {
        String filename = "D:\\Front-End\\Github_Projects\\Al_DS-structure\\TestSource\\The Hobbit.txt";
        System.out.println("The Hobbit");

        long startTime = System.nanoTime();
        ArrayList<String> words = new ArrayList<>();
        if (FileOperation.readFile(filename, words)) {
            System.out.println("Total words: " + words.size());

            LinkedListMap<String, Integer> map = new LinkedListMap<>();
            for (String word : words) {
                if (map.contains(word))
                    map.set(word, map.get(word) + 1);
                else
                    map.add(word, 1);
            }

            System.out.println("Total different words: " + map.getSize());
            System.out.println("Frequency of ring: " + map.get("ring"));
            System.out.println("Frequency of hobbit: " + map.get("hobbit"));
        }
        long endTime = System.nanoTime();
        System.out.println((endTime - startTime) / 1000000000.0);
        System.out.println();

        words.clear();
        startTime = System.nanoTime();
        if (FileOperation.readFile(filename, words)) {
            System.out.println("Total words: " + words.size());

            BSTMap<String, Integer> map2 = new BSTMap<>();
            for (String word : words) {
                if (map2.contains(word))
                    map2.set(word, map2.get(word) + 1);
                else
                    map2.add(word, 1);
            }

            System.out.println("Total different words: " + map2.getSize());
            System.out.println("Frequency of ring: " + map2.get("ring"));
            System.out.println("Frequency of hobbit: " + map2.get("hobbit"));
        }
        endTime = System.nanoTime();
        System.out.println((endTime - startTime) / 1000000000.0);
    }
}
