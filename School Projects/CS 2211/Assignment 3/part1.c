#include <stdio.h>

/*
Name: Part 1
Description: A program that rearranges and prints out user inputted arrays.
Author: Raymond Xie
Student No: 251275727
*/ 

// FUNCTIONS:
// Part 1: Printing out the array and index
int printArr(int arrSize, int numArr[]) 
{
    // Printing out the array
    printf("\nPart 1:");
    printf("\n  Your array is: ");
    // For loop to cycle through all elements in array
    for(int i=0; i<arrSize; i++) {
        // Checking if it is the last element in array for formatting
        if(i == arrSize-1) {
            printf("[%d] = %d ", i, numArr[i]);
        } else {
            printf("[%d] = %d, ", i, numArr[i]);
        }
    }
}

// Part 2: Printing out the array and index in reverse order
int reverseArr(int arrSize, int numArr[])
{
    // Printing out the array
    printf("\n");
    printf("\nPart 2:");
    printf("\n  Your array in reverse is: ");
    // For loop in reverse
    for(int i=arrSize-1; i>=0; i--) {
        // Checking if it is the first element in array for formatting
        if(i == 0) {
            printf("[%d] = %d ", i, numArr[i]);
        } else {
            printf("[%d] = %d, ", i, numArr[i]);
        }
    }
}

// Part 3: Printing out even elements in the array
int even(int arrSize, int numArr[])
{
    // Temporary arrays to store indexes and values
    int tempIndex[arrSize];
    int tempValue[arrSize];
    int count = 0;

    // For loop to cycle through all elements in array
    for(int i=0; i<arrSize; i++) {
        // Checking if element is even
        if(numArr[i] % 2 == 0) {
            // Stores the index and the value in temporary arrays
            tempIndex[count] = i;
            tempValue[count] = numArr[i];
            // Adds 1 to count
            count++;
        }
    }

    // Printing out the array
    printf("\n");
    printf("\nPart 3:");
    printf("\n  The even elements in the array is: ");
    for(int i=0; i<count; i++) {
        // Checking if it is the last element in array for formatting
        if(i == count-1) {
            printf("[%d] = %d ", tempIndex[i], tempValue[i]);
        } else {
            printf("[%d] = %d, ", tempIndex[i], tempValue[i]);
        }
    }
}

// Part 4: Printing out the sum of all values in the array
int sum(int arrSize, int numArr[]) 
{
    // Variable to store the sum
    int sum = 0;

    // For loop to cycle through all elements in the array
    for(int i=0; i<arrSize; i++) {
        sum = sum + numArr[i];
    }

    // Printing out result
    printf("\n");
    printf("\nPart 4:");
    printf("\n  The sum of all values in your array is: %d", sum);
}

// Part 5: Sorting the array by ascending order
int sort(int arrSize, int numArr[])
{
    // Temporary arrays to store sorted array values with indexes
    int tempIndex[arrSize];
    int tempValue[arrSize];

    // Making a copy of the original array and indexes
    for(int i=0; i<arrSize; i++) {
        tempValue[i] = numArr[i];
        tempIndex[i] = i;
    }

    // Variables to sort with
    int tmp, tmpIndex, m, n, min;

    // Double for loop to compare each value to every value in the array
    for(int i=0; i<arrSize-1; i++) {
        // Storing the minimum index as the first index to begin
        min = i;
        for(int j=i+1; j<arrSize; j++) {
            // If the value at index j is smaller than the one at the current min index
            if(tempValue[j] < tempValue[min]) {
                // Swaps the min index with index j
                min = j;
            }
        }

        // Swaps the minimum element with the first element and their indexes
        tmp = tempValue[min];
        tmpIndex = tempIndex[min];
        tempValue[min] = tempValue[i];
        tempIndex[min] = tempIndex[i];
        tempValue[i] = tmp;
        tempIndex[i] = tmpIndex;
    }

    // Printing out the array
    printf("\n");
    printf("\nPart 5:");
    printf("\n  Your array in sorted order is: ");
    // For loop to cycle through all elements in array
    for(int i=0; i<arrSize; i++) {
        // Checking if it is the last element in array for formatting
        if(i == arrSize-1) {
            printf("[%d] = %d ", tempIndex[i], tempValue[i]);
        } else {
            printf("[%d] = %d, ", tempIndex[i], tempValue[i]);
        }
    }
}

// Part 6: Print out the array but the first and last elements are swapped when printed
int swap(int arrSize, int numArr[]) 
{
    // Printing out the array
    printf("\n");
    printf("\nPart 6:");
    printf("\n  Your array with first and last element switched is: ");
    // For loop to cycle through all elements in array
    for(int i=0; i<arrSize; i++) {
        // Checking if it is the last element in array for formatting and switch with index 0
        if(i == arrSize-1) {
            printf("[%d] = %d ", 0, numArr[0]);
        // Checking if it is the first element in the array and switch with last index
        } else if(i == 0) {
            printf("[%d] = %d, ", arrSize-1, numArr[arrSize-1]);
        // Every other element is printed normally
        } else {
            printf("[%d] = %d, ", i, numArr[i]);
        }
    }
    
    // New line for spacing
    printf("\n");
}


// MAIN METHOD:
int main()
{

    // Variables
    int arrSize;
    int bytes;

    // User input
    printf("Please enter the number of integers to process: ");
    scanf("%d", &arrSize);

    // Creating the array using user inputted size
    int numArr[arrSize];

    // Converting int -> byte
    bytes = sizeof(numArr);

    // Output
    printf("    There is enough room in your array for %d integers (%d bytes)", arrSize, bytes);

    // Saving user input using for loop
    printf("\n");
    printf("\nPlease enter your integers separated by spaces: ");
    for(int i=0; i<arrSize; i++) {
        // Scans for a space in front of a number and saves the number
        scanf(" %d", &numArr[i]);
    }

    // Method calling
    // Part 1
    printArr(arrSize, numArr);
    // Part 2
    reverseArr(arrSize, numArr);
    // Part 3
    even(arrSize, numArr);
    // Part 4
    sum(arrSize, numArr);
    // Part 5
    sort(arrSize, numArr);
    // Part 6
    swap(arrSize, numArr);
}
