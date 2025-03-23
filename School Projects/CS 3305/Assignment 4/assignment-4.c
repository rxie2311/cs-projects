#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*
Name: CPU Scheduling Algorithms
Description: A program that allows the user to simulate CPU scheduling algorithms.
Author: Raymond Xie
Student No: 251275727
*/ 

// Global variables
// Global variable for process array size
int pArrSize = 0;

// Structure for each process to group all related variables (process name, process burst time, wait time, ect.) together
struct Process 
{
    // Process name
    char pName[1024];
    // Process burst time
    int pBurstTime;
    // Process' remaining burst time
    int pRemainingTime;
    // Process arrival time
    int pArrivalTime;
    // Process wait time
    int pWaitTime;
    // Process turnaround time
    int pTurnaround;
    // Process execution time (how much time the process has ran for)
    int pExecutionTime;
    // Integer flag to determine if the process has arrived or not (1 for arrived, 0 for not arrived)
    int arrivedFlag;
    // Integer flag to determine if the process has finished running or not (1 for finished, 0 for not finished)
    int finishedFlag;
};


// fcfs: Method used to simulate the First Come First Served CPU algorithm
void fcfs(struct Process *pArray)
{
    // Storing the process array length
    int len = pArrSize;

    // ticks: Counter variable to count the ticks
    int ticks = 0;
    // waitTime: Used by the program during output that displays the current wait time of the process
    int waitTime = 0;
    // elapsedTime: Used by the program to figure out how long a process has been waiting in queue
    int elapsedTime = 0;
    // turnaroundTime: Used by the program during output that displays the current turnaround time of the process
    int turnaroundTime = 0;

    // Print out the CPU algo name
    printf("First Come First Served\n");

    // For loop to cycle through the process array and output burst time, wait time, turnaround time
    for(int i=0; i<len; i++) {
        // Sets the current burst time to the total burst time of the process
        int currBurst = pArray[i].pBurstTime;

        // While loop that counts down the burst time, each loop counts down the burst time by 1
        while(currBurst > 0) {
            // Simulating that 1 burst time has gone by
            printf("T%d : P%d  - Burst left  %d, Wait time  %d, Turnaround time  %d\n", ticks, i, currBurst, waitTime, turnaroundTime);
            // Adds 1 tick
            ticks++;
            // Subtracts 1 from the current burst time
            currBurst--;

            // If the current tick number is greater than the process number and the current burst time is not 0
            if(ticks >= i && currBurst != 0) {
                // Adds to elapsed time so that the wait time of the next process can be updated to elapsed time
                elapsedTime++;
                // Adds to turnaround time, since this makes it so turnaround time is not updated when the process first enters
                turnaroundTime++;
            }
        }

        // Updates the current process' waiting time and turnaround time
        pArray[i].pWaitTime = waitTime;
        pArray[i].pTurnaround = turnaroundTime + 1;
        // Sets the new current waiting time as the elapsed time
        waitTime = elapsedTime;
    }

    // Newline for formatting
    printf("\n");

    // Variables to store the total sum of all wait and turnaround times
    float totalAvgWait = 0;
    float totalAvgTurn = 0;

    // For loop to cycle through the process array and display each process' wait and turnaround times
    for(int i=0; i<len; i++) {
        // Printing out process number
        printf("P%d\n", i);

        // Printing out process waiting and turnaround time
        printf("        Waiting time: %d\n", pArray[i].pWaitTime);
        printf("        Turnaround time: %d\n\n", pArray[i].pTurnaround);

        // Adding the process wait time and turnaround time to two variables to calculate average later
        totalAvgWait += pArray[i].pWaitTime;
        totalAvgTurn += pArray[i].pTurnaround;
    }

    // Calculating total average waiting and turnaround time
    totalAvgWait = (float)totalAvgWait / (float)len;
    totalAvgTurn = (float)totalAvgTurn / (float)len;

    // Printing the two averages out
    printf("\nTotal average waiting time: %0.1f\n", totalAvgWait);
    printf("Total average turnaround time: %0.1f\n", totalAvgTurn);
}


// sjf: Method to simulate the Shortest Job First CPU algorithm
void sjf(struct Process *pArray) 
{
    // Storing the process array length
    int len = pArrSize;

    // ticks: Counter variable to count the ticks
    int ticks = 0;
    // finished: Counter to keep track of how many processes have finished running
    int finished = 0;
    // currProcess: Keeps track of the process number of the currently running process
    int currProcess = 0;

    // Print out the CPU algo name
    printf("Shortest Job First\n");

    // While loop will keep running until all processes finish running
    while(finished < len) {
        // Checks if the current tick is less than the total length of the process array
        if(ticks < len) {
            // If it is, then check if the current tick that matches the current process number has arrived
            if(pArray[ticks].arrivedFlag != 1) {
                // If it hasn't arrived, then set it as arrived
                pArray[ticks].arrivedFlag = 1;
            }
        }

        // For loop to check if there are any other arrived processes that have a shorter burst time than the current process
        for(int i=0; i<len; i++) {
            // If the process at index i has arrived, is not finished, and if current process is finished, or if the process at index i has a lower burst time than the current process
            if(pArray[i].arrivedFlag == 1 && pArray[i].finishedFlag != 1 && (pArray[currProcess].finishedFlag == 1 || (pArray[i].pBurstTime > 0 && pArray[i].pBurstTime < pArray[currProcess].pBurstTime))) {
                // Sets the process at index i as the current process since it has a shorter burst time
                currProcess = i;
            }

            // If the process at i has arrived and has not finished, then add 1 to the process' turnaround time
            if(pArray[i].arrivedFlag == 1 && pArray[i].finishedFlag != 1) {
                pArray[i].pTurnaround++;
            }
        }

        // Subtracting the current tick by the amount of time the process has already ran for by the arrival time of the process to get the waiting time
        pArray[currProcess].pWaitTime = ticks - pArray[currProcess].pExecutionTime - pArray[currProcess].pArrivalTime;
        // Sets the initial turnaround time as the current ticks subtracted by the arrival time of the current process
        pArray[currProcess].pTurnaround = ticks - pArray[currProcess].pArrivalTime;

        // Simulating that 1 burst time has gone by
        printf("T%d : %s  - Burst left  %d, Wait time  %d, Turnaround time  %d\n", ticks, pArray[currProcess].pName, pArray[currProcess].pBurstTime, pArray[currProcess].pWaitTime, pArray[currProcess].pTurnaround);

        // Subtract 1 from burst time since 1 tick has gone by
        pArray[currProcess].pBurstTime--;
        // Adds 1 to process execution time since it has ran for 1 additional tick
        pArray[currProcess].pExecutionTime++;

        // Checks if the current process burst time is at 0
        if(pArray[currProcess].pBurstTime <= 0) {
            // If it is, then adds 1 to the finished counter to signify a process finishing running
            finished++;
            // Sets the current process' finished flag to 1
            pArray[currProcess].finishedFlag = 1;
        }

        // Adds 1 to ticks
        ticks++;
    }

    // Newline for formatting
    printf("\n");

    // Variables to store the total sum of all wait and turnaround times
    float totalAvgWait = 0;
    float totalAvgTurn = 0;

    // For loop to cycle through the process array and display each process' wait and turnaround times
    for(int i=0; i<len; i++) {
        // Printing out process number
        printf("P%d\n", i);

        // Printing out process waiting and turnaround time
        printf("        Waiting time: %d\n", pArray[i].pWaitTime);
        printf("        Turnaround time: %d\n\n", pArray[i].pTurnaround + 1);

        // Adding the process wait time and turnaround time to two variables to calculate average later
        totalAvgWait += pArray[i].pWaitTime;
        totalAvgTurn = totalAvgTurn + pArray[i].pTurnaround + 1;
    }

    // Calculating total average waiting and turnaround time
    totalAvgWait = (float)totalAvgWait / (float)len;
    totalAvgTurn = (float)totalAvgTurn / (float)len;

    // Printing the two averages out
    printf("\nTotal average waiting time: %0.1f\n", totalAvgWait);
    printf("Total average turnaround time: %0.1f\n", totalAvgTurn);
}


// roundrobin: Method to simulate the Round Robin CPU algorithm
void roundrobin(struct Process *pArray, int quantum) 
{
    // Storing the process array length
    int len = pArrSize;

    // ticks: Counter variable to count the ticks
    int ticks = 0;
    // finished: Counter to keep track of how many processes have finished running
    int finished = 0;
    // currProcess: Keeps track of the process number of the currently running process
    int currProcess = 0;
    // runtime: Keeps track of how long the current process has been running for
    int runtime = 0;
    // justEntered: A int flag that keeps track of if a process just started running (1 for yes, 0 for no)
    int justEntered = 1;
    // turnaround: A tracking variable that tracks the last turnaround time of a process that was swapped out
    int turnaround = 0;

    // Print out the CPU algo name
    printf("Round Robin with Quantum %d\n", quantum);

    // While loop will keep running until all processes finish running
    while(finished < len) {
        // Handling the wrap around when the array reaches the end
        // Also gatekeeps processes that are at burst time 0 from rentering
        if (currProcess >= len || pArray[currProcess].pBurstTime <= 0) {
            // Cycling through the process array for unfinished processes
            for(int i=0; i<len; i++) {
                // Calculating the next process
                int nextProcess = (currProcess + i) % (len-1);
                // If a process has a burst time of larger than 0 and is unfinished
                if(pArray[nextProcess].pBurstTime > 0) {
                    // Sets i as the current process
                    currProcess = nextProcess;
                    // Sets the justEntered flag to 1
                    justEntered = 1;
                    // Breaks out of the loop
                    break;
                }
            }
        }

        // If a process has newly entered running
        if(justEntered == 1) {
            // Subtracting the current tick by the amount of time the process has already ran for by the arrival time of the process to get the waiting time
            pArray[currProcess].pWaitTime = ticks - pArray[currProcess].pExecutionTime - pArray[currProcess].pArrivalTime;
            // Sets the process turnaround time
            pArray[currProcess].pTurnaround = turnaround;
            // Sets the justEntered flag to 0
            justEntered = 0;
        
        // If the process has ran last tick already
        } else {
            // Sets the process turnaround time
            pArray[currProcess].pTurnaround = ticks - pArray[currProcess].pArrivalTime;
            turnaround = pArray[currProcess].pTurnaround;
        }
        
        // Simulating that 1 burst time has gone by
        printf("T%d : %s  - Burst left  %d, Wait time  %d, Turnaround time  %d\n", ticks, pArray[currProcess].pName, pArray[currProcess].pBurstTime, pArray[currProcess].pWaitTime, pArray[currProcess].pTurnaround);

        // Subtract 1 from burst time since 1 tick has gone by
        pArray[currProcess].pBurstTime--;
        // Adds 1 to process execution time since it has ran for 1 additional tick
        pArray[currProcess].pExecutionTime++;
        // Adds 1 to runtime
        runtime++;

        // If the process is finished running
        if(pArray[currProcess].pBurstTime <= 0) {
            // Checks if the finished flag of current process is set to 0
            if(pArray[currProcess].finishedFlag != 1) {
                // Current process is marked as finished
                pArray[currProcess].finishedFlag = 1;
                // Add 1 to the finished process counter
                finished++;
                // Moves to the next process in the list
                currProcess++;
                // Sets the justEntered flag to 1
                justEntered = 1;
                // Runtime is reset down to 0
                runtime = 0;
            }
        }

        // If the process has ran for as long as it is allowed to
        if(runtime == quantum) {
            // Moves to the next process in the list
            currProcess++;
            // Sets the justEntered flag to 1
            justEntered = 1;
            // Runtime is reset down to 0
            runtime = 0;
        }

        // Adds 1 to ticks
        ticks++;
    }

    // Newline for formatting
    printf("\n");

    // Variables to store the total sum of all wait and turnaround times
    float totalAvgWait = 0;
    float totalAvgTurn = 0;

    // For loop to cycle through the process array and display each process' wait and turnaround times
    for(int i=0; i<len; i++) {
        // Printing out process number
        printf("P%d\n", i);

        // Printing out process waiting and turnaround time
        printf("        Waiting time: %d\n", pArray[i].pWaitTime);
        printf("        Turnaround time: %d\n\n", pArray[i].pTurnaround);

        // Adding the process wait time and turnaround time to two variables to calculate average later
        totalAvgWait += pArray[i].pWaitTime;
        totalAvgTurn = totalAvgTurn + pArray[i].pTurnaround + 1;
    }

    // Calculating total average waiting and turnaround time
    totalAvgWait = (float)totalAvgWait / (float)len;
    totalAvgTurn = (float)totalAvgTurn / (float)len;

    // Printing the two averages out
    printf("\nTotal average waiting time: %0.1f\n", totalAvgWait);
    printf("Total average turnaround time: %0.1f\n", totalAvgTurn);
}


// Main method
int main(int argc, char *argv[]) 
{
    // If the user did not follow the correct format (./assignment-4 -f|-s|-r <quantum> assignment-4-input.csv) in the command line prompt
    if(argc != 3 && argc != 4) {
        // Tells the user that the format is invalid
        perror("Error: Format entered is incorrect (./assignment-4 -f|-s|-r <quantum> assignment-4-input.csv is correct)\n");
        // Exits out of the process
        exit(0);
    }

    // File variable
    FILE *file;

    // Reading the file name
    if(argc == 3) {
        // Reading the csv file
        file = fopen(argv[2], "r");
        
    } else if(argc == 4) {
        // Reading the csv file
        file = fopen(argv[3], "r");
    }

    // Temp variable to hold the current char in the file
    char c;
    // While loop to cycle through the file to count the number of processes
    while((c = fgetc(file)) != EOF) {
        // If c approaches a newline character
        if(c == '\n') {
            // Adds 1 to the global variable
            pArrSize++;
        }
    }

    // Creating a new array to store all of the processes in the file
    struct Process pArray[pArrSize];
    // Closing the current file reader
    fclose(file);

    // Reading the csv file, this time to store all of the names and burst times into the array
    file = fopen("assignment-4-input.csv", "r");

    // Variables used to cycle through the csv file
    char line[1024];
    // Token - Used to separate the line into two sections by the comma
    char *token;
    // Counter variable to keep track of arrival time and array index
    int count = 0;

    // While loop to cycle through the file and save everything until it reaches the last line
    while(fgets(line, 1024, file) != NULL) {
        // Splitting the line by the comma
        token = strtok(line, ",");
        // Saving the process name into the structure array
        strncpy(pArray[count].pName, token, 1024);

        // Saving the other half of the line split by the comma
        token = strtok(NULL, ",");
        // Saving the process burst time into the structure array
        pArray[count].pBurstTime = atoi(token);

        // Saving the current counter as the arrival time
        pArray[count].pArrivalTime = count;
        // Saving process wait and turnaround time as 0 for now
        pArray[count].pWaitTime = 0;
        pArray[count].pTurnaround = 0;
        // Saving process execution time as 0 for now
        pArray[count].pExecutionTime = 0;
        // Saving process arrived (used for SJF) as 0 for now
        pArray[count].arrivedFlag = 0;
        // Saving process finished (used for SJF) as 0 for now
        pArray[count].finishedFlag = 0;

        // Adding 1 to the counter
        count++;
    }

    // Closing the file afterwards when done
    fclose(file);

    // Determining which CPU algorithm to use
    // If there are only 3 arguments, it is either FCFS or SJF
    if(argc == 3) {
        // If "-f" was in the command
        if(strcmp(argv[1], "-f") == 0) {
            // Call on fcfs method to run FCFS
            fcfs(pArray);
        
        // If "-s" was in the command
        } else if(strcmp(argv[1], "-s") == 0) {
            // Call on sjf method to run SJF
            sjf(pArray);
        }
    
    // If there are 4 arguments, then it is RR
    } else if(argc == 4) {
        // Save the time quantum as a variable to be used in the method
        int quantum = atoi(argv[2]);
        // Call on the roundrobin method to run RR
        roundrobin(pArray, quantum);
    }
}