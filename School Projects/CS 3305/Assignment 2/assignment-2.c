#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
Name: Large Integer Multiplication Calculator
Description: A program that takes two 4 digit integers, partitions them, and calculates the product of the two.
Author: Raymond Xie
Student No: 251275727
*/ 

// calcX: Method to calculate X by doing A * 10^n
int calcX(int A)
{
    // Assuming that n is always 4 since the program only accepts 1000-9999
    int power = 10 * 10 * 10 * 10;
    // Calculating A * 10^4
    int X = A * power;

    // Returns X
    return X;
}


// calcY: Method to calculate Y by doing (B+C) * 10^n/2
int calcY(int B, int C)
{
    // Assuming that n = 4, 4/2 = 2
    int power = 10 * 10;
    // Calculating (B+C) * 10^2
    int Y = (B+C) * power;

    //Returns Y
    return Y;
}


// Main method
int main(int argc, char *argv[])
{
    // If the user entered a integer not within the range of 1000-9999
    if(atoi(argv[1]) < 1000 || atoi(argv[1]) > 9999 || atoi(argv[2]) < 1000 || atoi(argv[2]) > 9999) {
        // Tells the user that the input is invalid
        perror("Error: Values entered were not within the range of 1000-9999\n");
        // Exits out of the process
        exit(0);
    }

    // Command line parameters
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    // Pipe 1: Pipe for parent to send and child to receive
    int port1[2];
    // Checks for failure on the pipe
    if(pipe(port1) < 0) {
        // Outputs an error message
        perror("Pipe 1 error\n");
        // Exits out of the process
        exit(0);
    } 

    // Pipe 2: Pipe for child to send and parent to receive
    int port2[2];
    // Checks for failure on the pipe
    if(pipe(port2) < 0) {
        // Outputs an error message
        perror("Pipe 2 error\n");
        // Exits out of the process
        exit(0);
    } 

    // Variables to be used for operations
    int A, B, C, D;
    int a1, a2, b1, b2;

    // Printing out the user's inputted integers
    printf("Your integers are %d %d\n", a, b);

    // Forking the child process
    pid_t pid;
    pid = fork();
    // Checks for failure of fork()
    if(pid < 0) {
        // Outputs an error message
        perror("Fork error\n");
        // Exits out of the process
        exit(0);
    }
    
    // Code for parent process
    if(pid > 0) {
        // Prints out the parent pid and child pid
        printf("Parent (PID %d): Created child (PID %d)\n", getpid(), pid);

        // Partitioning integer a and b into a1, a2, b1, b2
        a1 = a / 100;
        a2 = a % 100;
        b1 = b / 100;
        b2 = b % 100;

        // Starts calculating X
        // Formatting
        printf("###\n");
        printf("# Calculating X\n");
        printf("###\n");

        // Sending a1 and b1 through the pipe
        write(port1[1], &a1, sizeof(a1));
        printf("Parent (PID %d): Sending %d to child\n", getpid(), a1);

        write(port1[1], &b1, sizeof(b1));
        printf("Parent (PID %d): Sending %d to child\n", getpid(), b1);

        // Receives the product of a1 and b1 (A)
        read(port2[0], &A, sizeof(A));
        printf("Parent (PID %d): Received %d from child\n\n", getpid(), A);
        // Calls on helper function to calculate X
        int X = calcX(A);

        // Starts calculating Y
        // Formatting
        printf("###\n");
        printf("# Calculating Y\n");
        printf("###\n");

        // Sending a2 and b1 through the pipe
        write(port1[1], &a2, sizeof(a2));
        printf("Parent (PID %d): Sending %d to child\n", getpid(), a2);

        write(port1[1], &b1, sizeof(b1));
        printf("Parent (PID %d): Sending %d to child\n", getpid(), b1);

        // Receives the product of a2 and b1 (B)
        read(port2[0], &B, sizeof(B));
        printf("Parent (PID %d): Received %d from child\n\n", getpid(), B);
        
        // Sending a1 and b2 through the pipe
        write(port1[1], &a1, sizeof(a1));
        printf("Parent (PID %d): Sending %d to child\n", getpid(), a1);

        write(port1[1], &b2, sizeof(b2));
        printf("Parent (PID %d): Sending %d to child\n", getpid(), b2);

        // Receives the product of a1 and b2 (C)
        read(port2[0], &C, sizeof(C));
        printf("Parent (PID %d): Received %d from child\n\n", getpid(), C);
        // Calls on helper function to calculate Y
        int Y = calcY(B, C);

        // Starts calculating Z
        // Formatting
        printf("###\n");
        printf("# Calculating Z\n");
        printf("###\n");

        // Sending a2 and b2 through the pipe
        write(port1[1], &a2, sizeof(a2));
        printf("Parent (PID %d): Sending %d to child\n", getpid(), a2);

        write(port1[1], &b2, sizeof(b2));
        printf("Parent (PID %d): Sending %d to child\n", getpid(), b2);

        // Receives the product of a2 and b2 (D)
        read(port2[0], &D, sizeof(D));
        printf("Parent (PID %d): Received %d from child\n\n", getpid(), D);
        // Saves D to Z since D * 10^0 = D * 1 = D
        int Z = D;

        // Calculating the sum of X + Y + Z
        int sum = X + Y + Z;
        // Outputting the final product of a * b
        printf("%d*%d == %d + %d + %d == %d\n", a, b, X, Y, Z, sum);
    }

    // Code for child process
    if(pid == 0) {
        // Variables to store read ints from parent
        int x;
        int y;
        // Variable to store product of multiplication
        int product;

        // Starts calculating X
        // Reading a1 and b1 from the pipe
        read(port1[0], &x, sizeof(x));
        printf("Child (PID %d): Received %d from parent\n", getpid(), x);

        read(port1[0], &y, sizeof(y));
        printf("Child (PID %d): Received %d from parent\n", getpid(), y);

        // Multiplies a1 and b1 and returns the product (A)
        product = x * y;
        write(port2[1], &product, sizeof(product));
        printf("Child (PID %d): Sending %d to parent\n", getpid(), product);

        // Starts calculating Y
        // Reading a2 and b1 from the pipe
        read(port1[0], &x, sizeof(x));
        printf("Child (PID %d): Received %d from parent\n", getpid(), x);

        read(port1[0], &y, sizeof(y));
        printf("Child (PID %d): Received %d from parent\n", getpid(), y);

        // Multiplies a2 and b1 and returns the product (B)
        product = x * y;
        write(port2[1], &product, sizeof(product));
        printf("Child (PID %d): Sending %d to parent\n", getpid(), product);

        // Reading a1 and b2 from the pipe
        read(port1[0], &x, sizeof(x));
        printf("Child (PID %d): Received %d from parent\n", getpid(), x);

        read(port1[0], &y, sizeof(y));
        printf("Child (PID %d): Received %d from parent\n", getpid(), y);

        // Multiplies a1 and b2 and returns the product (C)
        product = x * y;
        write(port2[1], &product, sizeof(product));
        printf("Child (PID %d): Sending %d to parent\n", getpid(), product);

        // Starts calculating Z
        // Reading a2 and b2 from the pipe
        read(port1[0], &x, sizeof(x));
        printf("Child (PID %d): Received %d from parent\n", getpid(), x);

        read(port1[0], &y, sizeof(y));
        printf("Child (PID %d): Received %d from parent\n", getpid(), y);

        // Multiplies a2 and b2 and returns the product (D)
        product = x * y;
        write(port2[1], &product, sizeof(product));
        printf("Child (PID %d): Sending %d to parent\n", getpid(), product);

        // Exiting out after the child process is done and returning pid to parent process
        exit(0);
    }

    // Terminates the parent process
    exit(0);
}    