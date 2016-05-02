import java.lang.Iterable;

public class Main {

    public static void main(String[] args) {
	// write your code here
        try {
            CirDeque<Double> q = new CirDeque<>();
            double next;

            System.out.println("Size is (expect 0): " + q.size());
            System.out.println("Is the queue empty? : " + q.isEmpty());

            q.addBack(5.0);
            System.out.println("Size is (expect 1): " + q.size());
            next = q.popFront();
            System.out.println("Value popFrontd: " + next);
            System.out.println("Size is (expect 0): " + q.size());

            for (double i = 0; i < 10; i++) {
                q.addBack(i*1.1);
                System.out.println("Size is (expect " + (i+1) + "): " + q.size());
            }

            System.out.println("Pushing to front 5 more values [99...95]");
            for (double j = 99; j > 94; j--) {
                q.addFront(j);
                System.out.println(j + " is now in the front of the queue.");
            }
            System.out.println("Size is (expect " + 15 + "): " + q.size());

            for (int k = 0; k < 15; k++) {
                next = q.popFront();
                System.out.println("Value popFrontd: " + next);
            }

            System.out.println("addBack 0 to 5, then popBack() after done...");

            for (int m = 0; m < 6; m++) {
                q.addBack(m * 1.0);
            }

            System.out.println("Is the queue empty? : " + q.isEmpty());

            System.out.println("Popping back now: (expect 5): " + q.popBack());

            for (double d : q) {    // TODO: Fix this syntax error ("for-each not applicable to expression type. Required: array or java.lang.Iterable. found: CirDeque<java.lang.Double>
                System.out.println(d);
            }

            // Calculate the sum using iterator

            double sum = 0;
            double count = 0;

            for (double val : q) {
                sum += val;
                ++count;
            } // for
            System.out.println("Sum of values: " + sum);
            System.out.println("Average of values: " + sum / count);
            System.out.println("Average of values (using .size() ): " + sum / q.size());

            System.out.println("Going to try to blow the stack...");
            for (double blow = 0; blow < 100; blow++)
                q.popBack();
        } // try

        catch (EmptyStackException exc) {
            System.out.println(exc.toString());
            System.out.println("Exiting the try/catch.");
        }
    }
}
