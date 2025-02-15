#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_LEN 20

int main(void)
{
    char *words[50];
    char temp[STR_LEN + 1];
    int counter = 0;

    // Infinite loop to get words from user
    for(;;) { 
        printf("Enter word: ");
        gets(temp);

        // Break loop if user enters empty word
        if(temp[0] == '\0') {
            break;
        }

        // Allocate memory to store new word in the array
        words[counter] = malloc(strlen(temp) + 1);
        if(words[counter] == NULL) {
            printf("Out of memory");
            return 1;
        }

        strcpy(words[counter], temp); // Copy new word into allocated memory
        counter++;
    }

    // Print out biggest and smallest word
    char *first = words[0];
    char *last = words[0];

    // For loop to cycle through the array
    for(int i = 0; i < counter; i++) {
        // Checks if first is still smaller than word at index i
        if(strcmp(words[i], first) < 0) {
            first = words[i];
        }

        // Checks if last is still bigger than word at index i
        if(strcmp(words[i], last) > 0) {
            last = words[i];
        }
    }

    // Print out first and last
    printf("\nFirst: %s", first);
    printf("\nLast: %s", last);


    // Sort the words in array lexiographically
    for(int i = 0; i < counter; i++) {
        for(int j = i + 1; j < counter; j++) {
            if(strcmp(words[i], words[j]) > 0) {
                // Swaps the positions of word at index i and j
                char *temp = words[i];
                words[i] = words[j];
                words[j] = temp;
            }
        }
    }

    // Print out sorted words
    printf("\nIn sorted order:");
    // For loop to cycle through array
    for(int i = 0; i < counter; i++) {
        printf(" %s", words[i]);
    }
}