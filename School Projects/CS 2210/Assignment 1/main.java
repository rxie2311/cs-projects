public class main {
    public static void main(String args[]) {

        int[] arr = {1,1,1,2};
        int num = 1;
        int n = arr.length;

        //int result = copies(arr, n, num);
        //System.out.println("Question 5: " + result);

        int[] numL = {2,2,2,7,8,10};
        int x = 1;
        int first = 0;
        int last = 5;

        int result = finder(numL, first, last, x);

        System.out.println(result);

    }
    public static int copies(int[] L, int n, int x) {

        int c=0;

        if(x == L[0]) {
            c=1;
        }

        for(int i=0; i<n-1; i++) {
            if(x == L[i]) {
                c=c+1;
            }
        }
        return c;
    }

    public static int finder(int[] L, int first, int last, int x) {

        if(first > last) {
            return -1;
        } else {
            int numValues = last - first + 1;
            int third = (int) (first + Math.floor(numValues/3));
            System.out.println("third: " + third);

            if(x == L[third]) {
                return third;
            } else if(x < L[third]) {
                return finder(L, first, third, x);
            } else {
                int twoThird = (int) (first + (2*Math.floor(numValues/3)));
                System.out.println("twothird: " + twoThird);

                if(x == L[twoThird]) {
                    return twoThird;
                } else if(x < L[twoThird]) {
                    return finder(L, third, twoThird, x);
                } else {
                    return finder(L, twoThird, last, x);
                }
            }
        }



    }

}
