public class AlgorithmDemo {

    public static void main(String[] args) {
	// write your code here
        char letters[] = { 'h', 'x', 'v', 's', 'd', 'a', 'D', 'z', 'Z', 'g' };

        for(char c : letters) {
            System.out.print(c + " ");
        }
        System.out.print("\n");

        Quicksort.qsort(letters);

        for(char c : letters) {
            System.out.print(c + " ");
        }
        System.out.print("\n");
    }
}
