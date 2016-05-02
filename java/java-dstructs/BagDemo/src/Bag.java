/**
 * Created by Soularpower on 1/12/2016.
 */
public class Bag {
    int size;
    Node first;

    public Bag() {
        size = 0;
        first = null;
    }

    public int getSize(){
        return size;
    }

    public void add(int v) {
        if (size > 0) {
            Node newNode = new Node();
            newNode.value = v;
            newNode.next = first;
            first = newNode;
            ++size;
        }
        else if (size == 0) {
            first = new Node();
            first.value = v;
            ++size;
        }
        else {
            System.out.println("Add failed");
        }
    }

    public boolean remove(int v) {
        boolean removedVal = false;
        Node pNode = first;
        Node prior = pNode;

        while (pNode != null) {
            if (pNode.value == v) {
                prior.next = pNode.next;
                removedVal = true;
                --size;
            } else {
                prior = prior.next;
            }
            pNode = pNode.next;
        }
        return removedVal;
    }

    public boolean contains(int v) {
        Node pNode = first;

        while (pNode != null) {
            if (pNode.value == v) {
                return true;
            }
            pNode = pNode.next;
        }
        return false;
    }

    public int[] toArray() {
        Node pNode = first;
        int contents[] = new int[this.size];

        for (int i = 0; pNode != null ; i++, pNode = pNode.next) {
            contents[i] = pNode.value;
        }

        return contents;
    }
}
