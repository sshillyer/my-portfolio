public class BSTDemo {

    public static void main(String[] args) {
        BSTBag<Double> bag = new BSTBag<Double>();

        // Builds a balanced tree with values from the set [-100, 100]
        for (double v = 0; v <= 100.0 && v >= -100.0; ) {
            bag.put(v);
            if (v >= 0) {
                v++;
                v = -1 * v;
            } else {
                v--;
                v = -1 * v;
            }
        }

        // Print the contents in order using public method
        bag.printInOrder();

        // Test if bag contains variosu values
        for(double i = -110.0; i <= 110.0; i++) {
            System.out.println("Bag contains " + i + "?: " + bag.contains(i));
        }

        // Use the iterator (implicitly with for-each)
        for(double item : bag) {
            System.out.println("Bag contains: " + item);
        }
    }
}
