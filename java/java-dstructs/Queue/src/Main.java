public class Main {

    public static void main(String[] args) {

        Queue q = new Queue();

        // Feedback
        System.out.println("q.empty(): " + q.isEmpty());
        System.out.println("q.size(): " + q.size());

        int qty = 10;

        for (int i = 0; i < qty; i++) {
            q.enqueue(i);
            System.out.println("q.enqueue(" + i + ")...");
        }

        q.enqueue(55);
        q.enqueue(55);

        for (int i = 0; i < qty; i++) {
            System.out.println("q.dequeue(): " + q.dequeue());
            System.out.println("q.size(): " + q.size());
        }

        System.out.println("q.dequeue(): " + q.dequeue());
        System.out.println("q.dequeue(): " + q.dequeue());

        System.out.println("q.empty(): " + q.isEmpty());

    }
}
