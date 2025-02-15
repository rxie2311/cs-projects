public class Primes {
    // Name: Raymond Xie
    // Student No: 251275727

    // Main function:
    public static void main(String[] args) {
        // Finding all prime numbers from 0-100:
        for(int i=0; i<=400; i++) {
            // Checks if i is prime
            if(isPrime(i)) {
                // Inserting p into the formula Mp = 2^p - 1
                double result = (Math.pow(2,i)) - 1;
                if(isPrime(result)) {
                    // If Mp is prime
                    System.out.println("Prime Number (p): " + i + ", Result (Mp): Mp is prime (" + result + ")");
                } else {
                    // If Mp is not prime
                    System.out.println("Prime Number (p): " + i + ", Result (Mp): Mp is not prime (" + result + ")");
                }
            }
        }
    }

    // isPrime function to check if inserted number n is a prime number or not
    public static boolean isPrime(double n) {
        // Check if n is less than or equal to 1
        if (n <= 1) {
            // Not prime if n is negative, 0 or 1
            return false;

        // Check if n is equal to 2
        } else if (n == 2) {
            // Prime if n is 2
            return true;

        // Check if n is a multiple of 2
        } else if (n % 2 == 0) {
            // Not prime if divisible by 2
            return false;
        }

        // If not divisible by 2, then just check every multiple starting from 3 until the square root of n
        // Jumps 2 multiples at a time to check odd numbers
        for (int i = 3; i <= Math.sqrt(n); i += 2) {
            // If n is divisible by one of them, it is not prime
            if (n % i == 0)
                return false;
        }
        // If n passes all tests, n is prime
        return true;
    }
}
