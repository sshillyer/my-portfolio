/**
 * Created by Soularpower on 1/21/2016.
 */
public class Quicksort {

    // Public method to call recursive quicksort
    static void qsort(char items[]) {
        qs(items, 0, items.length-1);
    }

    // Recursive quicksort
    private static void qs(char items[], int left, int right) {
        int lft, rgt;
        char pvt, y;

        lft = left; rgt = right;
        pvt = items[(right+left) / 2]; // get the middle index to use as pivot / partition

        do {
            // Slide up the array until we find a value that is >= to the pivot
            while((items[lft] < pvt) && (lft < right)) {
                lft++;
            }
            while((items[rght]))
        }
    }
}
