import java.util.Iterator;

/**
 * Created by Shawn S Hillyeron 1/19/2016.
 * A doubly-linked, circular implementation of a double-ended queue using a sentinel node
 */

public class CirDeque<Item> implements Iterable<Item> {

    // Doubly linked node
    protected class Node {
        Item value;
        Node next;
        Node prev;

        // Constructor
        // Pre: None
        // Post: Node will have value, next, prev set
        protected Node(Item value, Node next, Node prev) {
            this.value = value;
            this.next = next;
            this.prev = prev;
        }
    }

    // Private Data Members
    private int size;
    private Node head;


    // Contructor
    // Pre: None
    // Post: size 0, head points to a sentinel node
    public CirDeque() {
        int size = 0;
        this.head = new Node (null, this.head, this.head);    // Sentinel
        head.next = head;
        head.prev = head;
        assert(size == 0);
    }


    // Enqueue an item to front of CirDeque
    public void addBack(Item val) {
        Node oldEnd;
        oldEnd = head.next;
        Node newNode = new Node(val, oldEnd, head);
        oldEnd.prev = newNode;
        head.next = newNode;

        ++size;
    }

    public void addFront(Item val) {
        Node oldFront;
        oldFront = head.prev;
        Node newNode = new Node(val, head, oldFront);
        oldFront.next = newNode;
        head.prev = newNode;

        ++size;
    }

    // Dequeue an item from back of CirDeque
    public Item popFront() throws EmptyStackException
    {
        if (!isEmpty()) {
            Item returnVal = head.prev.value;
            Node newFront = head.prev.prev;
            newFront.next = head;
            head.prev = newFront;
            --size;
            return returnVal;
        } else {
            throw new EmptyStackException();
        }
    }

    public Item popBack() throws EmptyStackException {
        if (!isEmpty()) {
            Item returnVal = head.next.value;
            Node newBack = head.next.next;
            newBack.prev = head;
            head.next = newBack;
            --size;
            return returnVal;
        }
        else {
            throw new EmptyStackException();
        }

    }

    public int size() {
        return size;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public Iterator<Item> iterator() {
        return new DequeIterator();
    }

    // Iterator class
    private class DequeIterator implements Iterator<Item> {
        private Node current = head;

        public boolean hasNext() { return current.next != head; }

        public Item next() {
            current = current.next;
            return current.value;
        }

        public void remove() { } // Intentionally blank
    }
}
