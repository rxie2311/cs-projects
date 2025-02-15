public class Errors {
    private static int[] arr;
    private static int i;

    private static void algo1() {
        int[] arr = new int[3];
        int i = 0;
        for (i = 0; i < 3; ++i)
            arr[i] = i;
        i = 10;
        System.out.println("i = " + i);
    }

    public static void main(String[] args) {
        i = 3;
        arr = new int[3];
        for (int i = 0; i < Errors.i; ++i)
            arr[i] = 10;
        algo1();
        System.out.println("i = " + i + " arr[0] = " + arr[0] + " arr[1] = " + arr[1] + " arr[2] = " + arr[2]);
    }
}
