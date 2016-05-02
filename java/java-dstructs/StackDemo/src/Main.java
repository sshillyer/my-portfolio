public class Main {

    public static void main(String[] args) {
	// write your code here
        Stack stck = new Stack();

        System.out.println("stck.size() = " + stck.size());
        System.out.println("stck.isEmpty(): " + stck.isEmpty());

        for (int i = 0; i < 15; i++) {
            stck.push(i);
            System.out.println("stck.push(" + i + ")");
        }
        System.out.println("stck.isEmpty(): " + stck.isEmpty());

        System.out.println("stck.size() = " + stck.size());

        for (int j = 0; j < 7; j++) {
            System.out.println("stck.pop() returns: " + stck.pop());
        }

        System.out.println("stck.size() = " + stck.size());

        stck.push(15);
        stck.push(25);
        System.out.println("stck.size() = " + stck.size());
        System.out.println("Popping 25: " + stck.pop());
        System.out.println("stck.size() = " + stck.size());
        System.out.println("Popping 15: " + stck.pop());
        System.out.println("stck.size() = " + stck.size());
    }
}
