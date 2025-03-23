#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>

/*
Name: Mutex Locks
Description: A program that uses mutex locks to simulate bank account transactions.
Author: Raymond Xie
Student No: 251275727
*/ 

// Structure for each bank account to track account number and balance
struct Account
{
    // Account number
    int accountNo;
    // Account balance
    int accountBal;
};


// Structure for each transaction to track affected account and amount
struct Transaction
{
    // Account to be withdrawn from/deposited into
    int account;
    // Amount to be withdrawn/deposited
    int amount;
};


// Structure for each thread to track thread id and store a list of transactions that the thread must handle
struct Thread
{
    // Thread id
    int threadID;
    // Array to store all of the transactions this thread needs to handle
    struct Transaction* tList;
    // Counter variable to track number of transactions in the list
    int tCount;
};


// Global Variables
// Global list for storing 4 accounts
struct Account accounts[4];
// Lock required to enter critical section
pthread_mutex_t lock;


// runTransaction: Method used by the threads to perform the transaction
void *runTransaction(void *data)
{
    // Moving passed in data into a Thread structure
    struct Thread *thread = (struct Thread *)data;

    // For loop to perform the transactions that the thread needs to perform
    for(int i=0; i<thread->tCount; i++) {
        // Thread tries to obtain the lock for each transaction, if it cannot, it will be blocked until it can
        pthread_mutex_lock(&lock);

        // Variables to store the transaction details
        int account = thread->tList[i].account - 1;
        int amount = thread->tList[i].amount;

        // Withdraw: If the account does not have enough money for the withdraw
        if(amount < 0 && accounts[account].accountBal < (amount * (-1))) {
            // Lets the user know the withdraw failed
            printf("Thread %d: Withdraw $%d from Account %d - INSUFFICIENT FUNDS\n", thread->threadID, amount*(-1), accounts[account].accountNo);
        
        // Withdraw: If the account has enough money for the withdraw
        } else if(amount < 0 && accounts[account].accountBal > (amount * (-1))) {
            // Subtracts the amount from the account (amount is negative so we add it to the balance to subtract)
            accounts[account].accountBal = accounts[account].accountBal + amount;

            // Lets the user know the withdraw worked
            printf("Thread %d: Withdraw $%d from Account %d\n", thread->threadID, amount*(-1), accounts[account].accountNo);
        
        // Deposit: If the account needs to be deposited into
        } else {
            // Adds the amount to the account
            accounts[account].accountBal = accounts[account].accountBal + amount;

            // Lets the user know the deposit worked
            printf("Thread %d: Deposit $%d into Account %d\n", thread->threadID, amount, accounts[account].accountNo);
        }

        // Gives up the lock after each transaction
        pthread_mutex_unlock(&lock);
    }

    // Terminates the thread after the transactions are done
    pthread_exit(NULL);
}


// Main method
int main(int argc, char *argv[])
{
    // If the user did not follow the correct format (./assignment-5 <file name>.txt) in the command line prompt
    if(argc != 2) {
        // Tells the user that the format is invalid
        perror("Error: Format entered is incorrect (./assignment-5 <file name>.txt is correct)\n");
        // Exits out of the process
        exit(0);
    }

    // Calls on file reader method to read the file name inputted by the user
    FILE *file = fopen(argv[1], "r");

    // Line variable to store the line
    char line[256];
    // Skips the header line
    fgets(line, sizeof(line), file);

    // For loop to cycle through the first 4 lines of the file and store account details
    for(int i=0; i<4; i++) {
        if(fgets(line, sizeof(line), file)) {
            sscanf(line, "-,%d,%d", &accounts[i].accountNo, &accounts[i].accountBal);
        }
    }

    // Printing out accounts and balances
    printf("Balance\n");

    for(int i=0; i<4; i++) {
        // Print out account number and balance
        printf("Account %d: $%d\n", accounts[i].accountNo, accounts[i].accountBal);
    }

    // Newline for formatting
    printf("\n");

    // Creates an array of threads (4 threads)
    pthread_t threads[4];
    // Creates an array of Thread structures to store thread data
    struct Thread tData[4];

    // Initializes the mutex lock
    pthread_mutex_init(&lock, NULL);

    // Initializing each index of tData
    for(int i=0; i<4; i++) {
        // Storing the thread id
        tData[i].threadID = i + 1;
        // Storing the amount of transactions this thread currently has
        tData[i].tCount = 0;
        // Initializing the transaction list
        tData[i].tList = NULL;
    }

    // Storing each transaction into each thread data in tData
    while(fgets(line, sizeof(line), file)) {
        // Variables to store each part of the transaction
        int threadid;
        int accountno;
        int tamount;

        // Storing the 3 ints on the line into each variable
        sscanf(line, "%d,%d,%d", &threadid, &accountno, &tamount);
        // Finding out which thread this transaction belongs to
        struct Thread *temp = &tData[threadid - 1];

        // Allocating space in the transaction list in that thread structure
        temp->tList = realloc(temp->tList, (temp->tCount + 1) * sizeof(struct Transaction));

        // Storing the transaction details
        temp->tList[temp->tCount].account = accountno;
        temp->tList[temp->tCount].amount = tamount;

        // Increasing the transaction list amount
        temp->tCount++;
    }

    // Once all the file reading is done, close the file
    fclose(file);

    // Calling on each thread to run transactions simultaneously
    for(int i=0; i<4; i++) {
        pthread_create(&threads[i], NULL, runTransaction, &tData[i]);
    }

    // Waiting for all threads to finish and terminate
    for(int i=0; i<4; i++) {
        pthread_join(threads[i], NULL);
    }

    // Freeing up the allocated memory once the threads are finished
    for(int i=0; i<4; i++) {
        free(tData[i].tList);
    }

    // Destroying the lock
    pthread_mutex_destroy(&lock);

    // Printing out the final account balances
    printf("\n");
    printf("Balance\n");

    for(int i=0; i<4; i++) {
        // Print out account number and balance
        printf("Account %d: $%d\n", accounts[i].accountNo, accounts[i].accountBal);
    }
}