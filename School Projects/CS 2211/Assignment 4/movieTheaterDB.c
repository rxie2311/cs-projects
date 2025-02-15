#include <stdio.h>
// Additional C Libraries (Allowed for use)
#include <string.h>

/*
* Name: Raymond Xie
* Student No: 251275727
* Program Name: movieTheaterDB
* Description: Has multiple modes that allows users to save movies as structures, search for movies in the database, update movies in the database
* and print out a list of all the movies in the database.
*/

// STRUCTURE
// Movie structure that saves movie code (positive int), name (99 characters max), genre (24 characters max) and rating (0.0-10.0)
struct movie
{
    // Variables in the structure
    // Movie code
    int code;
    // Movie name
    char name[100];
    // Movie genre
    char genre[25];
    // Movie rating
    float rating;
};


// MAIN METHOD
int main()
{
    // Variables
    int exit = 0;
    int counter = 0;
    // Array of structures to store all movies (100 max)
    struct movie m[100];


    // While loop that will keep looping until user decides to exit
    while(exit == 0) {
        // Variables
        char choice;
        // User input
        printf("\nEnter operation code: ");
        scanf("%c", &choice);

        // IF STATEMENTS
        // q: Exits out of the program
        if(choice == 'q') {
            // Exits out by breaking out of the loop
            break;
        
        // i: Inserts a new movie
        } else if(choice == 'i') {
            // Temp variable
            int tempCode;
            // User input for movie code
            printf("  Enter movie code: ");
            scanf("%d", &tempCode);

            // Checks if the structure is full
            if(counter == 99) {
                printf("The database is full. (100 movie limit)");
                // Print out new line for formatting
                printf("\n");
            
            // Checks if the number the user entered is negative
            } else if(tempCode < 0) {
                printf("Movie code cannot be negative.");
                // Print out new line for formatting
                printf("\n");
                // Clearing the scanner
                char c;
                scanf("%c", &c);

            // Checks the structure array for duplicate movie codes 
            } else {
                // Dupe variable
                int dupe = 0;
                // Checks if this is the first movie so user can enter 0 as a movie code
                if(counter != 0) {
                    // For loop to check the array structure
                    for(int i=0; i<counter+1; i++) {
                    // Prints out movie already exists if there are duplicate movie codes
                    if(tempCode == m[i].code) {
                        printf("Movie already exists.");
                        // Sets dupe to 1
                        dupe = 1;
                        // Print out new line for formatting
                        printf("\n");
                        // Clearing the scanner
                        char c;
                        scanf("%c", &c);
                        // Breaks out of the loop
                        break;
                        }
                    }
                }
                
                // Checks if there was a dupe
                if(dupe != 1) {
                    // Continues on if there is no dupe movie code
                    m[counter].code = tempCode;


                    // Temp variable
                    char tempStr[100];
                    // Clearing the scanner
                    char c;
                    scanf("%c", &c);

                    // User input for movie name
                    printf("  Enter movie name: ");
                    gets(tempStr);
                    // Checking if string exceeds 100 characters
                    if(strlen(tempStr) > 100) {
                        // Saves as many characters into movie name string as possible, then outputs that the movie name is too long
                        for(int i=0; i<99; i++) {
                            m[counter].name[i] = tempStr[i];
                        }
                        // Tells the user the name was too long and the character limit
                        printf("Movie name was too long. (100 character limit)\n");
                    
                    // If there are no length problems
                    } else {
                        // Saves the string into the structure
                        for(int i=0; i<strlen(tempStr); i++) {
                            m[counter].name[i] = tempStr[i];
                        }
                    }


                    // Temp variable
                    char tempGenre[25];
                    // User input for movie genre
                    printf("  Enter movie genre: ");
                    gets(tempGenre);
                    // Checking if string exceeds 25 characters
                    if(strlen(tempGenre) >= 25) {
                        // Saves as many characters into movie name string as possible, then outputs that the movie name is too long
                        for(int i=0; i<24; i++) {
                            m[counter].genre[i] = tempGenre[i];
                        }
                        // Tells the user the genre was too long and the character limit
                        printf("Movie genre was too long. (25 character limit)\n");
                    
                    // If there are no length problems
                    } else {
                        // Saves the string into the structure
                        for(int i=0; i<strlen(tempGenre); i++) {
                            m[counter].genre[i] = tempGenre[i];
                        }
                    }


                    // Temp variable
                    float tempRate;
                    // User input for movie genre
                    printf("  Enter movie rating: ");
                    scanf("%f", &tempRate);
                    // Locks user in a loop if rating is not between 0.0 and 10.0
                    if(tempRate < 0.0 || tempRate > 10.0) {
                        while(tempRate < 0.0 || tempRate > 10.0) {
                            printf("Movie rating must be between 0.0 and 10.0 to be valid.");
                            printf("\n  Enter movie rating: ");
                            scanf("%f", &tempRate);
                        }
                    }

                    // Saves tempRate into structure afterwards
                    m[counter].rating = tempRate;


                    // Updates counter
                    counter++;

                    // Clearing the scanner
                    scanf("%c", &c);
                }
            }
        
        // s: Searches for a movie using movie code in the database
        } else if(choice == 's') {
            // Temp variables
            int tempCode;
            int found = 0;
            // Asks user for the code they want to search for
            printf("  Enter movie code: ");
            scanf("%d", &tempCode);

            // If the code that is entered is less than 0
            if(tempCode < 0) {
                printf("The movie code you have entered does not exist.");
                // Print out new line for formatting
                printf("\n");

            } else {
                // Loops through the structure array for the code
                for(int i=0; i<counter+1; i++) {
                    // If a code is found, prints out the movie stats
                    if(tempCode == m[i].code) {
                        printf("Movie Code: %d, Movie Name: %s, Movie Genre: %s, Movie Rating: %.1f", m[i].code, m[i].name, m[i].genre, m[i].rating);
                        found = 1;
                    }
                }
                // If found still equals 0, it means the movie code entered does not exist
                if(found == 0) {
                    printf("The movie code you have entered does not exist.");
                    // Print out new line for formatting
                    printf("\n");
                }
            }

            // Print out new line for formatting
            printf("\n");

            // Clearing the scanner
            char c;
            scanf("%c", &c);
        
        // u: Updates the movie stats
        } else if(choice == 'u') {
            // Temp variables
            int tempCode;
            int upCode;
            int index;
            int found = 0;
            // Asks user for the code they want to search for
            printf("  Enter movie code: ");
            scanf("%d", &tempCode);

            // Clearing the scanner
            char c;
            scanf("%c", &c);

            // If the code that is entered is less than 0
            if(tempCode < 0) {
                printf("The movie code you have entered does not exist.");
                // Print out new line for formatting
                printf("\n");
            } else {
                // Loops through the structure array for the code
                for(int i=0; i<counter+1; i++) {
                    // If a code is found, updates variable
                    if(tempCode == m[i].code) {
                        found = 1;
                        // Save the index into i for future reference
                        index = i;
                        // Breaks out after finding
                        break;
                    }
                }
            }

            // If found still equals 0, it means the movie code entered does not exist
            if(found == 0) {
                printf("The movie code you have entered does not exist.");
                // Print out new line for formatting
                printf("\n");

            // If found equals 1, then the movie has been found
            } else if(found == 1) {
                // User input for movie code
                printf("  Enter updated movie code: ");
                scanf("%d", &upCode);
                
                // Checks if the number the user entered is negative
                if(upCode < 0) {
                    printf("Updated movie code cannot be negative.");
                    // Print out new line for formatting
                    printf("\n");

                // Checks the structure array for duplicate movie codes 
                } else {
                    // Dupe variable
                    int dupe = 0;
                    // For loop to check the array structure
                    for(int i=0; i<counter+1; i++) {
                        // Prints out movie already exists if there are duplicate movie codes
                        if(upCode == m[i].code) {
                            printf("Movie already exists.");
                            // Print out new line for formatting
                            printf("\n");
                            // Sets dupe to 1
                            dupe = 1;
                            // Clearing the scanner
                            char c;
                            scanf("%c", &c);
                            // Breaks out of the loop
                            break;
                        }
                    }

                    // Checks if there was a dupe
                    if(dupe != 1) {
                        // Continues on if there is no dupe movie code
                        m[index].code = upCode;


                        // Temp variable
                        char tempStr[100];
                        // Clearing the scanner
                        char c;
                        scanf("%c", &c);

                        // User input for movie name
                        printf("  Enter updated movie name: ");
                        gets(tempStr);
                        // Clears the name array
                        memset(m[index].name, '\0', sizeof(m[index].name));
                        // Checking if string exceeds 100 characters
                        if(strlen(tempStr) >= 100) {
                            // Saves as many characters into movie name string as possible, then outputs that the movie name is too long
                            for(int i=0; i<99; i++) {
                                m[index].name[i] = tempStr[i];
                            }
                            // Tells the user the name was too long and the character limit
                            printf("Movie name was too long. (100 character limit)\n");
                        
                        // If there are no length problems
                        } else {
                            // Saves the string into the structure
                            for(int i=0; i<strlen(tempStr); i++) {
                                m[index].name[i] = tempStr[i];
                            }
                        }


                        // Temp variable
                        char tempGenre[25];
                        // User input for movie genre
                        printf("  Enter updated movie genre: ");
                        gets(tempGenre);
                        // Clears the genre array
                        memset(m[index].genre, '\0', sizeof(m[index].genre));
                        // Checking if string exceeds 25 characters
                        if(strlen(tempGenre) >= 25) {
                            // Saves as many characters into movie name string as possible, then outputs that the movie name is too long
                            for(int i=0; i<24; i++) {
                                m[index].genre[i] = tempGenre[i];
                            }
                            // Tells the user the genre was too long and the character limit
                            printf("Movie genre was too long. (25 character limit)\n");
                        
                        // If there are no length problems
                        } else {
                            // Saves the string into the structure
                            for(int i=0; i<strlen(tempGenre); i++) {
                                m[index].genre[i] = tempGenre[i];
                            }
                        }


                        // Temp variable
                        float tempRate;
                        // User input for movie genre
                        printf("  Enter updated movie rating: ");
                        scanf("%f", &tempRate);
                        // Locks user in a loop if rating is not between 0.0 and 10.0
                        if(tempRate < 0.0 || tempRate > 10.0) {
                            while(tempRate < 0.0 || tempRate > 10.0) {
                                printf("Movie rating must be between 0.0 and 10.0 to be valid.");
                                printf("\n  Enter movie rating: ");
                                scanf("%f", &tempRate);
                            }
                        }

                        // Saves tempRate into structure afterwards
                        m[index].rating = tempRate;

                        // Clearing the scanner
                        scanf("%c", &c);
                    }
                }
            }

        // p: Prints out a list of all movies in the database
        } else if(choice == 'p') {
            // For loop to loop through all the movies
            for(int i=0; i<counter; i++) {
                printf("    Movie Code: %d, Movie Name: %s, Movie Genre: %s, Movie Rating: %.1f\n", m[i].code, m[i].name, m[i].genre, m[i].rating);
            }

            // Clearing the scanner
            char c;
            scanf("%c", &c);

            // Print out new line for formatting
            printf("\n");
        }
    }
}