// Declarations
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include other files
#include "movieTheaterDB_actor.h"

// HELPER METHODS
// Function that handles actor code
int actorCode(void) {
    // Temp variable
    int code;
    // User input for actor code
    printf("\n[m-i] Enter actor code: ");
    scanf("%d", &code);
            
    // Checks if the number the user entered is negative
    if(code < 0) {
        // Clearing the scanner
        char c;
        scanf("%c", &c);
        // Returns -1 if actor code was negative
        return -1;

    // If not negative, returns the code    
    } else {
        // Clearing the scanner
        char c;
        scanf("%c", &c);

        // Returns actor code
        return code;
    }
}


// Function that creates actor structure and assigns the 4 components into it
struct actor actorMaker(int code) {
    // Creates new actor structure to store all 4 components inside
    struct actor a;

    // ------------------------
    // ACTOR CODE SECTION:
    // ------------------------

    // Saves code into a.code
    a.code = code;
    
    // ------------------------
    // ACTOR NAME SECTION:
    // ------------------------

    // Temp variable
    char tempName[50];

    // User input for actor name
    printf("[a-i] Enter actor name: ");
    gets(tempName);

    // Checking if string exceeds 50 characters
    if(strlen(tempName) >= 50) {
        // Allocating memory in the char array to store chars
        a.name = malloc(50*sizeof(char));

        // Saves as many characters into actor name string as possible, then outputs that the actor name is too long
        for(int i=0; i<49; i++) {
            a.name[i] = tempName[i];
        }

        // Assigning null variable to the last index in the char array
        a.name[49] = '\0';
        // Tells the user the name was too long and the character limit
        printf("[a-i] Error: Actor name was too long. (50 character limit)\n");
                    
    // If there are no length problems
    } else {
        // Allocating memory in the char array to store chars
        a.name = malloc(strlen(tempName)*sizeof(char));

        // Saves the string into the structure
        for(int i=0; i<=strlen(tempName); i++) {
            // Checks if index i is on the last index of the input
            if(i == strlen(tempName)) {
                // Assigning null variable to the last index in the char array
                a.name[i] = '\0';
            } else {
                // Assigning each char into each index of the char array
                a.name[i] = tempName[i];
            }    
        }
    }

    // ------------------------
    // ACTOR PROFILE SECTION:
    // ------------------------

    // Temp variable
    char tempProfile[50];

    // User input for actor profile
    printf("[a-i] Enter actor profile: ");
    gets(tempProfile);

    // Checking if string exceeds 50 characters
    if(strlen(tempProfile) >= 50) {
        // Allocating memory in the char array to store chars
        a.profile = malloc(50*sizeof(char));

        // Saves as many characters into movie name string as possible, then outputs that the movie name is too long
        for(int i=0; i<49; i++) {
            a.profile[i] = tempProfile[i];
        }

        // Assigning null variable to the last index in the char array
        a.profile[49] = '\0';
        // Tells the user the genre was too long and the character limit
        printf("[a-i] Error: Actor profile was too long. (50 character limit)\n");
                    
    // If there are no length problems
    } else {
        // Allocating memory in the char array to store chars
        a.profile = malloc(strlen(tempProfile)*sizeof(char));

        // Saves the string into the structure
        for(int i=0; i<=strlen(tempProfile); i++) {
            // Checks if index i is on the last index of the input
            if(i == strlen(tempProfile)) {
                // Assigning null variable to the last index in the char array
                a.profile[i] = '\0';
            } else {
                // Assigning each char into each index of the char array
                a.profile[i] = tempProfile[i];
            } 
        }
    }

    // ------------------------
    // ACTOR AGE SECTION:
    // ------------------------

    // Temp variable
    int tempAge;

    // User input for actor age
    printf("[a-i] Enter actor age: ");
    scanf("%d", &tempAge);

    // Locks user in a loop if age is not between 0 and 120
    if(tempAge < 0 || tempAge > 120) {
        while(tempAge < 0 || tempAge > 120) {
            printf("[a-i] Error: Actor age must be between 0 and 120 to be valid.");
            printf("\n[a-i] Enter movie rating: ");
            scanf("%d", &tempAge);
        }
    }

    // Saves tempAge into structure afterwards
    a.age = tempAge;
                
    // Returns the actor struct at the end
    return a;
}