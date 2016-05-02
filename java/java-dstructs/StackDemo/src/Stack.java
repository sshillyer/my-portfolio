/**
 * LinkedList implementation of a stack
 * Created by Shawn Hillyer on 1/13/2016.
 */
public class Stack {
    class Node {
        int value;
        Node next;

        protected Node(int val, Node next) {
            this.value = val;
            this.next = next;
        }
    }

    private int size;
    private Node top;

    public Stack() {
        size = 0;
        top = null;
    }

    public void push(int val) {
        if (size() == 0) {
            top = new Node(val, null);
        } else {
            Node newNode = new Node(val, top);
            top = newNode;
        }
        ++size;
    }

    public int pop() {
        if (!isEmpty()) {
            // Explicitly remove references and point top to new top
            int topValue = top.value;
            Node newTop = top.next;
            top.next = null; // not sure if needed
            top = newTop;
            --size;
            return topValue;
        }
        else {
            return -1;  // TODO throw exception instead?
        }
    }

    public boolean isEmpty() {
        assert(size > 0);
        return (size <= 0);
    }

    public int size() {
        return size;
    }
}
