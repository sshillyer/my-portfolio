/**
 * Created by Soularpower on 1/13/2016.
 */
public class Queue {
    protected class Node {
        protected int value;
        protected Node next;
        protected Node prev;

        protected Node(int value, Node next, Node prev) {
            this.value = value;
            this.next = next;
            this.prev = prev;
        }
    }

    private int size;
    private Node front;
    private Node back;

    // Create an Empty Queue
    public Queue() {
        size = 0;
        front = null;
        back = null;
    }

    // Add an item to back of Queue
    public void enqueue(int value) {
        // Handle empty Queue
        if (isEmpty()) {
            back = front = new Node(value, null, null);;
//            front.prev = back;
        }
        // Special handling for first node...
//        else if (size == 1) {
//            Node newNode = new Node(value, back, null);
//            back = newNode;
//            front.prev = back;
//        }

        // Make a new node, link old back's prev to it, and point Queue's back to it
        else {
            Node newNode = new Node(value, back, null);
            back.prev = newNode;
            back = newNode;
        }
        ++size;
    }

    // Remove an item from front of Queue
    public int dequeue() {
        int frontValue = front.value;
        if (size > 1) {
            Node newFront = front.prev;
            front.prev = null;
            front = newFront;
            front.next = null; // unlinks front of the queue
        }
        else if (size == 1) {
            // Make nothing point to the node and free for garbage collection
            front = null;
            back = null;
        }
        else {
            return -999; // TODO: would rather throw an out of bounds exception
        }
        --size;
        return frontValue;
    }

    // Check if queue is empty
    public boolean isEmpty() {
        return (size == 0);
    }

    public int size() {
        return size;
    }

}
