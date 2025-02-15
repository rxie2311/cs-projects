public class PowerSet<T> {

    // Instance variable
    Set<T>[] set;

    // Constructor method
    public PowerSet(T[] elements) {
        // Finds out what 2^n - 1 is (How many subsets there should be)
        int x = (int) Math.pow(2,elements.length);

        // Saves set as a new Set
        set = new Set[x];

        // Loops through the amount of subsets in total
        for(int i=0; i<x; i++) {
            // Converts i into a binary string
            String binary = Integer.toBinaryString(i);
            // Pads 0's in front of the binary number so all are the same length
            binary = String.format("%0"+(elements.length)+"d", Integer.parseInt(binary));
            // Sets position i of set as a new smaller set
            set[i] = new Set<T>();

            // Loops through the amount of digits in the binary number
            for(int j=0; j<binary.length(); j++) {
                // Checks each character one at a time
                String temp = binary.substring(j,j+1);
                // If a 1 is found:
                if(temp.equals("1")) {
                    // Adds into the small subset to be added into the bigger set
                    set[i].add(elements[j]);
                }

            }
        }
    }

    // Gets the length of the power set
    public int getLength() {
        return set.length;
    }

    // Gets the subset at the given position of the power set
    public Set<T> getSet(int i) {
        return set[i];
    }

}

