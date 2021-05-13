import java.util.ArrayList;

public class Main {
    private static double testMap(Map<String, Integer> set, String filename) {
        System.out.println(filename);

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
            System.out.println("Frequency of war: " + map.get("war"));
            System.out.println("Frequency of peace: " + map.get("peace"));
        }

        long endTime = System.nanoTime();
        return (endTime - startTime) / 1000000000.0;
    }

    public static void main(String[] args) {
        String filename = "D:\\Front-End\\Github_Projects\\Al_DS-structure\\TestSource\\War and Peace.txt";

        LinkedListMap<String, Integer> linkedListMap = new LinkedListMap<>();
        double time1 = testMap(linkedListMap, filename);
        System.out.println("LinkedList Map: " + time1 + " s");
        System.out.println();

        BSTMap<String, Integer> bstMap = new BSTMap<>();
        double time2 = testMap(bstMap, filename);
        System.out.println("BST Map: " + time2 + " s");
        System.out.println();

        AVLMap<String, Integer> avlMap = new AVLMap<>();
        double time3 = testMap(avlMap, filename);
        System.out.println("AVL Map: " + time3 + " s");
    }
}
