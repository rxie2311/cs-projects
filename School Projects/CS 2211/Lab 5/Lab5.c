#include<stdio.h>

int main() 
{
    // Q1: Write a program that asks the user to enter a value for x and then displays the value of the following polynomial (watch out for integer overflow)
    // Variables
    int x;

    // User input
    printf("Enter a value for x: ");
    scanf("%d", &x);

    // Output
    int result = (3*(pow(x,5))) + (2*(pow(x,4))) - (5*(pow(x,3))) - (pow(x,2)) + (7*x) - 6;
    printf("The value of 3x^5 + 2x^4 - 5x^3 - x^2 + 7x - 6 when x = %d is: %d", x, result);


    // Q2: Write a program that asks the user to enter two fractions and add them together
    //Variables
    int num1, num2, denom1, denom2, gcd;

    // User input
    printf("\nEnter two fractions separated by a plus sign (Ex: 5/6+3/4): ");
    scanf("%d/%d+%d/%d", &num1, &denom1, &num2, &denom2);

    // Numerator
    int n = (num1*denom2) + (num2*denom1);
    // Denominator
    int d = denom1 * denom2;

    // Reducing to simplest form using GCD
    for(int i=1; i<=n && i<=d; i++) {
        // Checking for GCD
        if(n%i==0 && d%i==0) {
            gcd = i;
        }
    }

    // Result
    printf("The sum is %d/%d", n/gcd, d/gcd);


    // Q3: Write a program that asks the user to enter a three-digit number, then prints the number with its digits reverted
    // Variables
    int num, digit1, digit2, digit3, reverse;

    // User input
    printf("\nEnter a three-digit number: ");
    scanf("%d", &num);

    // Reversing
    digit1 = num / 100;
    digit2 = (num % 100) / 10;
    digit3 = num % 10;

    reverse = (100*digit3) + (10*digit2) + digit1;

    // Result
    printf("The reversal is: %d", reverse);
}