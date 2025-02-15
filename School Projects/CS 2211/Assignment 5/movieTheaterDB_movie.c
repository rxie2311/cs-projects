// Declarations
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include other files
#include "movieTheaterDB_movie.h"

/*
* Name: Raymond Xie
* Student No: 251275727
*/

// HELPER METHODS
// Function that handles movie code
int movieCode(void) {
    // Temp variable
    int code;
    // User input for movie code
    printf("\n[m-i] Enter movie code: ");
    scanf("%d", &code);
            
    // Checks if the number the user entered is negative
    if(code < 0) {
        // Clearing the scanner
        char c;
        scanf("%c", &c);
        // Returns -1 if movie code was negative
        return -1;

    // If not negative, returns the code    
    } else {
        // Clearing the scanner
        char c;
        scanf("%c", &c);

        // Returns movie code
        return code;
    }
}


// Function that creates movie structure and assigns the 4 components into it
struct movie movieMaker(int code) {
    // Creates new movie structure to store all 4 components inside
    struct movie m;

    // ------------------------
    // MOVIE CODE SECTION:
    // ------------------------

    // Saves code into m.code
    m.code = code;
    
    // ------------------------
    // MOVIE NAME SECTION:
    // ------------------------

    // Temp variable
    char tempName[100];

    // User input for movie name
    printf("[m-i] Enter movie name: ");
    gets(tempName);

    // Checking if string exceeds 100 characters
    if(strlen(tempName) >= 100) {
        // Allocating memory in the char array to store chars
        m.name = malloc(100*sizeof(char));

        // Saves as many characters into movie name string as possible, then outputs that the movie name is too long
        for(int i=0; i<99; i++) {
            m.name[i] = tempName[i];
        }

        // Assigning null variable to the last index in the char array
        m.name[99] = '\0';
        // Tells the user the name was too long and the character limit
        printf("[m-i] Error: Movie name was too long. (100 character limit)\n");
                    
    // If there are no length problems
    } else {
        // Allocating memory in the char array to store chars
        m.name = malloc(strlen(tempName)*sizeof(char));

        // Saves the string into the structure
        for(int i=0; i<=strlen(tempName); i++) {
            // Checks if index i is on the last index of the input
            if(i == strlen(tempName)) {
                // Assigning null variable to the last index in the char array
                m.name[i] = '\0';
            } else {
                // Assigning each char into each index of the char array
                m.name[i] = tempName[i];
            }    
        }
    }

    // ------------------------
    // MOVIE GENRE SECTION:
    // ------------------------

    // Temp variable
    char tempGenre[25];

    // User input for movie genre
    printf("[m-i] Enter movie genre: ");
    gets(tempGenre);

    // Checking if string exceeds 25 characters
    if(strlen(tempGenre) >= 25) {
        // Allocating memory in the char array to store chars
        m.genre = malloc(25*sizeof(char));

        // Saves as many characters into movie name string as possible, then outputs that the movie name is too long
        for(int i=0; i<24; i++) {
            m.genre[i] = tempGenre[i];
        }

        // Assigning null variable to the last index in the char array
        m.genre[24] = '\0';
        // Tells the user the genre was too long and the character limit
        printf("[m-i] Error: Movie genre was too long. (25 character limit)\n");
                    
    // If there are no length problems
    } else {
        // Allocating memory in the char array to store chars
        m.genre = malloc(strlen(tempGenre)*sizeof(char));

        // Saves the string into the structure
        for(int i=0; i<=strlen(tempGenre); i++) {
            // Checks if index i is on the last index of the input
            if(i == strlen(tempGenre)) {
                // Assigning null variable to the last index in the char array
                m.genre[i] = '\0';
            } else {
                // Assigning each char into each index of the char array
                m.genre[i] = tempGenre[i];
            } 
        }
    }

    // ------------------------
    // MOVIE RATING SECTION:
    // ------------------------

    // Temp variable
    float tempRate;

    // User input for movie genre
    printf("[m-i] Enter movie rating: ");
    scanf("%f", &tempRate);

    // Locks user in a loop if rating is not between 0.0 and 10.0
    if(tempRate < 0.0 || tempRate > 10.0) {
        while(tempRate < 0.0 || tempRate > 10.0) {
            printf("[m-i] Error: Movie rating must be between 0.0 and 10.0 to be valid.");
            printf("\n[m-i] Enter movie rating: ");
            scanf("%f", &tempRate);
        }
    }

    // Saves tempRate into structure afterwards
    m.rating = tempRate;
                
    // Returns the movie struct at the end
    return m;
}