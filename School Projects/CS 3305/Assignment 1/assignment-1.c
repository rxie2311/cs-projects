#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
Name: Prime Number Counter
Description: A program that counts prime numbers in between a range of numbers.
Author: Raymond Xie
Student No: 251275727
*/ 

// isPrime: Function to determine if an inputted number is prime or not
int isPrime(int num)
{
    // If the number is less than or equal to 1, it is not prime, 
    // therefore returns 0 (false)
    if(num <= 1) {
        return 0;
    }

    // For loop to cycle through all numbers smaller than num
    // i starts from 2 since a prime number is only prime if it is not divisible by anything but 1 and itself
    for(int i=2; i<num; i++) {
        // If num is divisible by a number other than 1 or itself, returns 0 (false)
        if(num % i == 0) {
            return 0;
        }
    }

    // Returns 1 (true) at the end, if 0 was not returned
    return 1;
}


// countSum: Function to count number of primes within a range of numbers, and sum all primes within the range of numbers together
void countSum(int startNum, int endNum)
{
    // Counter variable for number of primes, sum variable for sum of all primes
    int count = 0; 
    int sum = 0;
    
    // For loop to cycle from the starting number to the ending number
    for(int i=startNum; i<endNum; i++) {
        // Calls on isPrime
        int prime = isPrime(i);
        // If isPrime returns 1, then adds 1 to count and adds i to the total sum
        if(prime == 1) {
            count++;
            sum = sum + i;
        }
    }

    // Prints out the result
    printf("pid: %d, ppid: %d - Count and sum of prime numbers between %d and %d are %d and %d\n", getpid(), getppid(), startNum, endNum, count, sum);
}


// Main method
int main(int argc, char *argv[])
{
    // If the user did not enter 4 arguments (./assignment-1, flag, min, max) in the command line prompt
    if(argc != 4) {
        // Tells the user that the input is invalid
        printf("Error: Did not follow this format: ./assignment-1 (flag) (min) (max)\n");
        // Exits out of the process
        exit(0);
    }

    // Command line parameters
    int flag = atoi(argv[1]);
    int min = atoi(argv[2]);
    int max = atoi(argv[3]);

    // If the inputted flag is 0, run serial mode
    if(flag == 0) {
        // Print out process id
        printf("Process id: %d\n", getpid());

        // Manually call on countSum 4 times, splitting the range into 4 equal parts
        // First part: min - 1/4 of max
        countSum(min, min+(max-min)/4);
        // Second part: 1/4 of max to 1/2 of max
        countSum(min+(max-min)/4, min+(max-min)/2);
        // Third part: 1/2 of max to 3/4 of max
        countSum(min+(max-min)/2, min+3*(max-min)/4);
        // Fourth part: 3/4 of max to max
        countSum(min+3*(max-min)/4, max);

    // If the inputted flag is anything else, run parallel mode  
    } else {
        // Print out process id
        printf("Process id: %d\n", getpid());

        // Create an array of pid_t for child processes
        pid_t pids[4];

        // For loop to create 4 child processes
        for(int i=0; i<4; i++) {
            // Using fork to create child process
            pids[i] = fork();

            // Code for child process
            if(pids[i] == 0) {
                // Split up the range into 4 for the child process by using i from the for loop
                int startNum = min+(i*(max-min)/4);
                int endNum = min+((i+1)*(max-min)/4);

                // Calling on countSum and dividing the range equally into 4 parts
                countSum(startNum, endNum);
            
                // Exiting out after the child process is done and returning pid to parent process
                exit(0);
            }
        }

        // Using wait() to wait for the child processes to finish
        for(int i=0; i<4; i++) {
            // Waiting for the child pid at index i in pids[]
            waitpid(pids[i], NULL, 0);
        }
    }

    // Terminates the parent process
    exit(0);
}
