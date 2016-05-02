import java.util.Iterator;
import java.util.LinkedList;
import java.util.Queue;

/**
 * Created by Shawn Hillyer on 1/26/2016.
 *
 * A Binary Search Tree version of the Bag ADT
 *
 */
public class BSTBag<Item extends Comparable<Item>>
implements Iterable<Item>{

    // Each node holds a value and a ptr to left and right subtree
    protected class Node {
        Item value;
        Node left, right;
        int size;

        // Node Constructor
        protected Node(Item val) {
            this.value = val;
            right = left = null;
            int size = 1;
        }
    }

    private Node root;

    public BSTBag() {
        this.root = null;
    }

    // put() -- place val into the BST
    public void put(Item val) {
        root = _put(val, this.root);
    }

    // recursive put
    private Node _put(Item val, Node current) {

        // If current node is null, we've found where we need to insert
        if (current == null) {
//            System.out.println("Succesfully added " + val);
            return new Node(val);
        }
        int cmp = current.value.compareTo(val);

        // Current node is bigger than add value
        if (cmp > 0) {
//            System.out.println(current.value + " is greater than " + val + " so recursively adding to the left");
            current.left = _put(val, current.left);
        }
        else if (cmp < 0) {
//            System.out.println(current.value + " is less than " + val + " so recursively adding to the right");
            current.right = _put(val, current.right);
        }

        return current;
    }

    // contains() -- return true if val in BST, false otherwise
    public boolean contains(Item val) {
        return _contains(val, this.root);
    }

    // recursive contains()
    private boolean _contains(Item val, Node current) {
        // If we arrive at null, value not found
        if (current == null) {
//            System.out.println("Reached a null leaf, value not found.");
            return false;
        }

        int cmp = current.value.compareTo(val);
        if (cmp > 0) {
//            System.out.println("Checking current.value: " + current.value + " vs val: " + val + ". In GREATER than case");
            return _contains(val, current.left);
        }
        else if (cmp < 0) {
//            System.out.println("Checking current.value: " + current.value + " vs val: " + val + ". In LESS than case");
            return _contains(val, current.right);
        }
        // If the node is not null and it's neither greater nor less than, it must be equal
        else {
//            System.out.println("Value found! current.value: " + current.value + ", val: " + val);
            return true;
        }
    }

    // printInOrder() Prints the contents of the BSTBag
    public void printInOrder() {
        printInOrder(root);
    }

    // recursive printInOrder()
    private void printInOrder(Node root) {
        if (root == null)
            return;
        printInOrder(root.left);
        System.out.println(root.value);
        printInOrder(root.right);
    }

    // buildInOrder() -- Used to build a queue containing all of the values in the BSTBag
    private Queue<Node> buildInOrderQueue() {
        Queue<Node> nodes = new LinkedList<Node>();
        nodes = buildInOrder(root, nodes);
        return nodes;
    }

    // recursive buildInOrder()
    private Queue<Node> buildInOrder(Node root, Queue<Node> q) {
        if (root == null) {
            return q;
        }
        // Handle the "less than" (left) subtree
        q = buildInOrder(root.left, q);
        q.add(root);
        q = buildInOrder(root.right, q);
        return q;
    }


    /*
    Iterator function and class
     */

    // iterator() Returns an in-order iterator
    public Iterator<Item> iterator() {
        return new InOrderBSTIterator();
    }

    private class InOrderBSTIterator implements Iterator<Item> {
        Queue<Node> nodes = buildInOrderQueue();

        @Override
        public boolean hasNext() {
            return (nodes.peek() != null);
        }

        @Override
        public Item next() {
            Node current = nodes.poll();
            return current.value;
        }

        @Override
        public void remove() {
            // Intentionally left empty
        }
    }
}
