#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

/*
Name: Sudoku Puzzle Verifier
Description: A program that takes a 9x9 Sudoku puzzle and verifies if it is correct.
Author: Raymond Xie
Student No: 251275727
*/ 

// Global Variables
// 2D array that will store the 9x9 sudoku grid
int sudoku_grid[9][9];
// Array of numbers that will store the result of each thread
// Defaults it all to 0 (which means that the result was false) to begin with
int thread_results[27] = {0};


// loadFile: Method used to load the sudoku puzzle into the sudoku_grid array
void loadFile(char *filename)
{
    // Opening and reading the file passed as a parameter
    FILE *file = fopen(filename, "r");

    // Nested for loop to read every row and column and save each number into the array
    for(int i=0; i<9; i++) {
        for(int j=0; j<9; j++) {
            // Scanning the file for integers and saving them
            fscanf(file, "%d", &sudoku_grid[i][j]);
        }
    }

    // Closing the file at the end
    fclose(file);
}


// uniqueInt: Method that checks if numbers in a row, column or 3x3 subsection are all unique
int uniqueInt(int numbers[])
{
    // Nested loop to compare each number to every other number in the array
    // This checks for duplicate numbers
    for(int i=0; i<9; i++) {
        for(int j=0; j<9; j++) {
            // If a duplicate number is found AND j is not in the current index i is at
            if(numbers[i] == numbers[j] && j != i) {
                // Returns 0 (false) since it found a duplicate
                return 0;
            }
        }
    }

    // Returns 1 (true) if no duplicate was found
    return 1;
}


// checkSection: Method used by threads to check their section of the sudoku puzzle
void *checkSection(void *data)
{
    // Changing the parameter array back into an int array from void
    int *thread_data = (int *)data;

    // Checking the index of whatever row/column/subsection this thread needs to check
    int index = thread_data[0];
    // Checking what the thread is checking: 1 - row, 2 - column, 3 - subsection
    int type = thread_data[1];
    // Free the allocated memory
    free(data);

    // Array to store all the integers in the thread's section to be passed into uniqueInt to check for duplicate numbers
    int thread_num[9];

    // If statements for each type
    // If the type is 1, then the thread is checking a row
    if(type == 1) {
        // For loop will cycle through the row
        for(int i=0; i<9; i++) {
            // index = row number, i = each item in the row from left to right
            thread_num[i] = sudoku_grid[index][i];
        }
    
    // If the type is 2, then the thread is checking a column
    } else if(type == 2) {
        // For loop will cycle through the column
        for(int i=0; i<9; i++) {
            // index = column number, i = each item in the column from up to down
            thread_num[i] = sudoku_grid[i][index];
        }

    // If the type is 3, then the thread is checking a 3x3 subsection
    } else if(type == 3) {
        // Both of these values represent the top left number of the 3x3 section
        int row = (index / 3) * 3;
        int col = (index % 3) * 3;
        // Counter variable that counts to 9 to store the numbers into thread_num
        int counter = 0;

        // Nested for loop to cycle through the 3x3 grid
        for(int i=0; i<3; i++) {
            for(int j=0; j<3; j++) {
                // Saves each number in the grid into the array
                thread_num[counter++] = sudoku_grid[row + i][col + j];
            }
        }
    }

    // Checking if the numbers are all unique in the row/column/subsection
    int result = uniqueInt(thread_num);
    // Stores the result of the thread into the thread_results array
    thread_results[index + ((type-1)*9)] = result;
    
    // If the result was 1, then all numbers were unique
    if(result == 1) {
        // For row
        if(type == 1) {
            printf("Thread # %d (row %d) is valid\n", index + ((type-1)*9) + 1, index + 1);

        // For column
        } else if(type == 2) {
            printf("Thread # %d (column %d) is valid\n", index + ((type-1)*9) + 1, index + 1);

        // For subsection
        } else if(type == 3) {
            printf("Thread # %d (subgrid %d) is valid\n", index + ((type-1)*9) + 1, index + 1);
        }
    
    // If the result was 0, then there was a duplicate number
    } else {
        // For row
        if(type == 1) {
            printf("Thread # %d (row %d) is INVALID\n", index + ((type-1)*9) + 1, index + 1);

        // For column
        } else if(type == 2) {
            printf("Thread # %d (column %d) is INVALID\n", index + ((type-1)*9) + 1, index + 1);

        // For subsection
        } else if(type == 3) {
            printf("Thread # %d (subgrid %d) is INVALID\n", index + ((type-1)*9) + 1, index + 1);
        }
    }

    // Terminates the thread
    pthread_exit(NULL);
}


// Main method
int main(int argc, char *argv[]) 
{
    // If the user did not follow the correct format (./assignment-3 textfile.txt) in the command line prompt
    if(argc != 2) {
        // Tells the user that the format is invalid
        perror("Error: Format entered is incorrect (./assignment-3 textfile.txt is correct)\n");
        // Exits out of the process
        exit(0);
    }

    // Calls on file reader method to read the file name inputted by the user
    loadFile(argv[1]);
    // Creates an array of threads (27 threads)
    pthread_t threads[27];
    // Counter variable to keep track of how many threads have been assigned
    int counter = 0;

    // For loop to divide the rows between the first 9 threads
    for(int i=0; i<9; i++) {
        // row[0]: Saves the row number that the thread will check, row[1]: Saves the number 1, so the thread method knows that this thread checks a row
        // Allocates memory to make sure each thread doesn't interfere with each other's variables
        int *row = malloc(2 * sizeof(int));
        row[0] = i;
        row[1] = 1;

        // Creates a thread and calls on checkSection
        pthread_create(&threads[counter++], NULL, checkSection, row);
    }

    // For loop to divide the columns between the next 9 threads
    for(int j=0; j<9; j++) {
        // col[0]: Saves the column number that the thread will check, col[1]: Saves the number 2, so the thread method knows that this thread checks a column
        // Allocates memory to make sure each thread doesn't interfere with each other's variables
        int *col = malloc(2 * sizeof(int));
        col[0] = j;
        col[1] = 2;

        // Creates a thread and calls on checkSection
        pthread_create(&threads[counter++], NULL, checkSection, col);
    }

    // For loop to divide the subsections between the last 9 threads
    for(int k=0; k<9; k++) {
        // subsec[0]: Saves the subsection number that the thread will check, subsec[1]: Saves the number 3, so the thread method knows that this thread checks a subsection
        // Allocates memory to make sure each thread doesn't interfere with each other's variables
        int *subsec = malloc(2 * sizeof(int));
        subsec[0] = k;
        subsec[1] = 3;

        // Creates a thread and calls on checkSection
        pthread_create(&threads[counter++], NULL, checkSection, subsec);
    }

    // Loop to wait for all threads to finish running
    for(int l=0; l<27; l++) {
        pthread_join(threads[l], NULL);
    }

    // Loops through the thread results array to check the results of all of them
    for(int m=0; m<27; m++) {
        // If it finds that one of the results found a duplicate number
        if(thread_results[m] == 0) {
            // Lets the user know
            printf("%s contains an INVALID solution\n", argv[1]);
            // Exits the process
            exit(0);
        }
    }

    // If a duplicate number was not found
    printf("%s contains a valid solution\n", argv[1]);
    // Exits the process
    exit(0);
}