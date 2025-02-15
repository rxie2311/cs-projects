import java.lang.Math;

/*
Name: Raymond Xie
Student No: 251275727
*/

public class PrimeTester2 {
    public static void main(String[] args) {
        // Variables
        int smallestCounter = 1;
        // While loop to loop through all positive integers until P(n) is prime
        while(smallestCounter > 0) {
            // Formula (P(n) = x^2 - 79x + 1601)
            int n = ((int) Math.pow(smallestCounter, 2)) - (79*smallestCounter) + 1601;
            // Checks if n is not prime
            if(!isPrime(n)) {
                // Result of formula
                System.out.println("4b. n: " + n);
                // If prime, prints out the smallest counterexample and breaks out of the loop
                System.out.println("4b. Smallest counterexample: " + smallestCounter);
                break;
            }
            // If smallestCounter was not the smallest counterexample, add 1 to smallestCounter and check again
            smallestCounter++;
        }
    }
    // Method to check if a number is prime
    public static boolean isPrime(int n) {
        // Makes sure n is not 1 or a negative number
        if(n <= 1) {
            return false;
        }
        // Checks multiples of n starting from 2 all the way to n-1
        for(int i = 2; i < n; i++) {
            if(n%i == 0) {
                return false;
            }
        }
        // If no multiples of any other number other than 1 is found, return true (means number is prime)
        return true;
    }
}
