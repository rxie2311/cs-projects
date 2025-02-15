public class ReversibleArray <T> {

    // Instance variables
    T[] array;
    int count;

    // Constructor
    public ReversibleArray(T[] array) {
        this.array = array;
        this.count = array.length;
    }

    // Array reverser
    public void reverse() {
        T t;
        for (int i = 0; i < count / 2; i++) {
            t = array[i];
            array[i] = array[count - i - 1];
            array[count - i - 1] = t;
        }
    }

    public String toString() {
        String S = "";
        for(int i=0; i<array.length; i++) {
            if(i == array.length-1) {
                S = S + array[i];
            } else {
                S = S + array[i] + ", ";
            }
        }

        return S;
    }

}
