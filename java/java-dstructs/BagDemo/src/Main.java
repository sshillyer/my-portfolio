

public class Main {

    public static void main(String[] args) {
        System.out.println("Hello");

        // Make a Bag
        Bag testBag = new Bag();

        System.out.println("Bag is size: " + testBag.getSize());
        testBag.add(5);

        System.out.println("Bag is size: " + testBag.getSize());
        testBag.add(10);

        System.out.println("Bag ccntains 5: " + testBag.contains(5));
        System.out.println("Bag ccntains 8: " + testBag.contains(8));
        System.out.println("Bag ccntains 10: " + testBag.contains(10));

        for (int i = 0; i < 15; i++) {
            testBag.add(i);
        }
        int bagContents[] = testBag.toArray();

        System.out.println("Bag is size: " + testBag.getSize());
        testBag.remove(4);
        System.out.println("Bag is size: " + testBag.getSize());
        testBag.remove(5);
        System.out.println("Bag is size: " + testBag.getSize());

        for (int i = 0; i < bagContents.length; i++) {
            System.out.println("Bag contains: " + bagContents[i]);
        }
    }
}
