#include <stdio.h>

// Defining LEN as 2
#define LEN 2

// Part 1
int sum_array(const int a[], int size)
{
    // Pointer
    int* ptr;
    // Pointing to the first element in the array
    ptr = a;
    // Variables
    int sum = 0;

    // Traversing array using a for loop and a pointer
    for(int i = 0; i < size; i++) {
        sum += ptr[0];
        ptr++;
    }

    // Returning the sum
    return sum;
}

// Part 2
int sum_two_dimensional_array(const int a[][LEN], int size)
{
    // Pointer
    int* ptr;
    // Pointing to the first element in the array
    ptr = a;
    // Variables
    int sum = 0;

    for (int i = 0; i < LEN * size; i++) {
        sum += *ptr;
        ptr++;
    }

    // Returning the sum
    return sum;
}

// MAIN METHOD
int main() 
{
    // Array
    const int arr[] = {10,10,10,10,10};
    // Part 1
    int sum = sum_array(arr, 5);
    printf("Part 1: %d", sum);

    // 2D array
    const int arr2[][LEN] = {{5,5}, {5,5}, {5,5}};
    // Part 2
    int x = sum_two_dimensional_array(arr2, 3);
    printf("\nPart 2: %d", x);
}