// Declarations
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include other files
#include "movieTheaterDB.h"
#include "movieTheaterDB_movie.h"
#include "movieTheaterDB_actor.h"

/*
* Name: Raymond Xie
* Student No: 251275727
*/

// HELPER METHODS
// ------------------------
// MOVIE SECTION:
// ------------------------

// addMovie: Adds a movie into the linked list
struct movieNode *addMovie(struct movieNode *movieList, struct movie movie)
{
    // New node to store values
    struct movieNode *n;

    // Allocating memory in the linked list to store the new node
    n = malloc(sizeof(struct movieNode));
    // If the curr node in the list is null
    if (n == NULL) {
        printf("\nError: malloc failed in addMovie");
        exit(0); // Exits out and returns 0
    }

    // Saving the value into the node, then the node into the list
    n->movie = movie;
    n->next = movieList;

    // Returns the node
    return n;
}

// searchMovie: Finds a movie code in the linked list
struct movieNode *searchMovie(struct movieNode *movieList, int code) 
{
    // New node to store values
    struct movieNode *p;

    // Searches through the linked list
    for(p = movieList; p != NULL; p = p->next) {
        // If code entered is equal to a code already in the database
        if(p->movie.code == code) {
            // Returns the node at which the movie is stored in
            return p;
        }
    }

    // If nothing is found, return null
    return NULL;
}

// deleteMovie: Finds a movie using movie code and deletes it from the linked list
struct movieNode *deleteMovie(struct movieNode *movieList, int code) 
{
    // New movie nodes to represent node to be deleted and previous node
    struct movieNode *curr, *prev;

    // Removing a node when the movie code in the node is equal to the code inputted
    for (curr = movieList, prev = NULL; curr != NULL && curr->movie.code != code; prev = curr, curr = curr->next);

    // If curr is null, then it means the node has been removed, so returns the list
    if(curr == NULL) {
        return movieList;
    }

    // If prev is null, then set the list head to the next node
    if(prev == NULL) {
        movieList = movieList->next;

    // If prev is not null, then set the next of prev as the next of curr (since curr was deleted)    
    } else {
        prev->next = curr->next;
    }

    // Freeing up the memory inside of curr
    free(curr);
    // Returns the list
    return movieList;
}

// ------------------------
// ACTOR SECTION:
// ------------------------

// addActor: Adds an actor into the linked list
struct actorNode *addActor(struct actorNode *actorList, struct actor actor)
{
    // New node to store values
    struct actorNode *n;

    // Allocating memory in the linked list to store the new node
    n = malloc(sizeof(struct actorNode));
    // If the curr node in the list is null
    if (n == NULL) {
        printf("\nError: malloc failed in addActor");
        exit(0); // Exits out and returns 0
    }

    // Saving the value into the node, then the node into the list
    n->actor = actor;
    n->next = actorList;

    // Returns the node
    return n;
}

// searchActor: Finds an actor code in the linked list
struct actorNode *searchActor(struct actorNode *actorList, int code) 
{
    // New node to store values
    struct actorNode *p;

    // Searches through the linked list
    for(p = actorList; p != NULL; p = p->next) {
        // If code entered is equal to a code already in the database
        if(p->actor.code == code) {
            // Returns the node at which the actor is stored in
            return p;
        }
    }

    // If nothing is found, return null
    return NULL;
}

// deleteActor: Finds an actor using actor code and deletes it from the linked list
struct actorNode *deleteActor(struct actorNode *actorList, int code) 
{
    // New actor nodes to represent node to be deleted and previous node
    struct actorNode *curr, *prev;

    // Removing a node when the actor code in the node is equal to the code inputted
    for (curr = actorList, prev = NULL; curr != NULL && curr->actor.code != code; prev = curr, curr = curr->next);

    // If curr is null, then it means the node has been removed, so returns the list
    if(curr == NULL) {
        return actorList;
    }

    // If prev is null, then set the list head to the next node
    if(prev == NULL) {
        actorList = actorList->next;

    // If prev is not null, then set the next of prev as the next of curr (since curr was deleted)    
    } else {
        prev->next = curr->next;
    }

    // Freeing up the memory inside of curr
    free(curr);
    // Returns the list
    return actorList;
}


// ------------------------
// MAIN METHOD:
// ------------------------

int main(void)
{
    // Variables
    int exit = 0;

    // Linked list pointer (MOVIES)
    struct movieNode *movieList = NULL;
    // Nodes (MOVIES)
    struct movieNode *movieFirst = NULL;
    struct movieNode *newMovieNode = malloc(sizeof(struct movieNode));
    // Pointing nodes at each other (MOVIES)
    newMovieNode->next = movieFirst;
    movieFirst = newMovieNode;

    // Linked list pointer (ACTORS)
    struct actorNode *actorList = NULL;
    // Nodes (ACTORS)
    struct actorNode *actorFirst = NULL;
    struct actorNode *newActorNode = malloc(sizeof(struct actorNode));
    // Pointing nodes at each other (ACTORS)
    newActorNode->next = actorFirst;
    actorFirst = newActorNode;
    
    // While loop that will keep looping until user decides to exit
    while(exit == 0) {
        // Variables
        char choice;
        // User input
        printf("\n[HOME] Enter operation code: ");
        scanf("%c", &choice);

        // IF STATEMENTS
        // q: Exits out of the program
        if(choice == 'q') {
            // Exits out by breaking out of the loop
            break;

        // ------------------------
        // MOVIE SECTION:
        // ------------------------

        // m: Controls movies
        } else if(choice == 'm') {
            // Clearing the scanner
            char c;
            scanf("%c", &c);

            // User input
            printf("\n[m] Enter operation code: ");
            scanf("%c", &choice);

            // i: Inserts a new movie into the database
            if(choice == 'i') {
                // Variables for movie struct and movie code
                int code;
                struct movie m;

                // Assigns code to the output of movieCode
                code = movieCode();
                // Calling on movie code function to get user input for new movie code
                if(code == -1) {
                    // Prints out a statement to tell the user that movie code cannot be negative
                    printf("[m-i] Error: Movie code cannot be negative.\n");

                // Program continues if movie code is positive    
                } else {
                    if(searchMovie(movieList, code) == NULL) {
                        // Creates a new movie struct using helper method
                        m = movieMaker(code);
                        // Tells the user the movie they have entered into the database
                        printf("[m-i] You entered into the database: Movie Code: %d, Movie Name: %s, Movie Genre: %s, Movie Rating: %.1f", m.code, m.name, m.genre, m.rating);
                        // Adds movie to movieList
                        movieList = addMovie(movieList, m);
                        // Formatting
                        printf("\n");

                    } else {
                        // Prints an error message
                        printf("\n[m-i] Error: Movie code already exists in the database. (Press enter to continue)");
                    }
                }

                // Clearing the scanner
                char c;
                scanf("%c", &c);

            // s: Searches for a movie using movie code              
            } else if(choice == 's') {
                int tempCode;
                // User input
                printf("\n[m-s] Enter movie code: ");
                scanf("%d", &tempCode);

                struct movieNode *n = searchMovie(movieList, tempCode);
                if(n == NULL) {
                    // Prints out an error
                    printf("\n[m-s] Error: Movie does not exist in the database.");
                    // Clearing the scanner
                    char c;
                    scanf("%c", &c);

                } else {
                    // Prints out movie
                    printf("[m-s] Movie found: ");
                    printf("Movie Code: %d, Movie Name: %s, Movie Genre: %s, Movie Rating: %.1f\n", n->movie.code, n->movie.name, n->movie.genre, n->movie.rating);
                    // Clearing the scanner
                    char c;
                    scanf("%c", &c);
                }

            // u: Updates a movie inside the database              
            } else if(choice == 'u') {
                // Variables for movie struct and movie code
                int update;
                int code;
                struct movie m;

                // Clearing the scanner
                char c;
                scanf("%c", &c);

                // User input
                printf("\n[m-u] Please enter the movie code you wish to update: ");
                scanf("%d", &update);

                // Assigns code to the output of movieCode
                code = movieCode();
                // Calling on movie code function to get user input for new movie code
                if(code == -1) {
                    // Prints out a statement to tell the user that movie code cannot be negative
                    printf("[m-u] Error: Movie code cannot be negative.\n");

                // Program continues if movie code is positive    
                } else {
                    if(searchMovie(movieList, code) == NULL) {
                        // Creates a new movie struct using helper method
                        m = movieMaker(code);
                        
                        // Makes a new node to store the old node
                        struct movieNode *curr;
                        // Runs the search command to find the old movie code and return the node with it
                        curr = searchMovie(movieList, update);

                        // If the search function returns a node
                        if(curr != NULL) {
                            // Updates the node completely
                            curr->movie.code = m.code;
                            curr->movie.name = m.name;
                            curr->movie.genre = m.genre;
                            curr->movie.rating = m.rating;
                            // Lets the user know the movie was updated successfully
                            printf("\n[m-u] Successfully updated movie.");

                        // If the search function does not return a node    
                        } else {
                            // Prints out an error message
                            printf("\n[m-u] Error: Movie was not found in the database.");
                        }

                    } else {
                        // Prints an error message if new code already exists in database
                        printf("\n[m-u] Error: Movie code already exists in the database. (Press enter to continue)");
                    }
                }

                // Clearing the scanner
                scanf("%c", &c);

            // p: Lists all of the movies in the database
            } else if(choice == 'p') {
                // Print statement
                printf("[m-p] ALL MOVIES IN DATABANK:\n");

                // New curr node to cycle through the list
                struct movieNode *curr;

                // For loop to loop through the entire linked list
                for(curr = movieList; curr != NULL; curr = curr->next) {
                    // Prints out all movies
                    printf("Movie Code: %d, Movie Name: %s, Movie Genre: %s, Movie Rating: %.1f\n", curr->movie.code, curr->movie.name, curr->movie.genre, curr->movie.rating);
                }

                // Clearing the scanner
                char c;
                scanf("%c", &c);

            // e: Deletes a movie from the database
            } else if(choice == 'e') {
                // Temp variable
                int code;

                // User input
                printf("\n[m-e] Please enter the movie code you wish to delete: ");
                scanf("%d", &code);

                // Quick search to find if the movie code entered exists or not
                struct movieNode *n = searchMovie(movieList, code);
                // If movie code does not exist
                if(n == NULL) {
                    // Prints out an error
                    printf("[m-e] Error: Movie does not exist in the database.");
                    // Clearing the scanner
                    char c;
                    scanf("%c", &c);

                // If movie code does exist
                } else {
                    // Calls helper function to delete the node
                    movieList = deleteMovie(movieList, code);
                    // Tells the user that the movie has been deleted
                    printf("[m-e] Successfully deleted movie.");
                    // Clearing the scanner
                    char c;
                    scanf("%c", &c);
                }

            // If the user enters an invalid command
            } else {
                printf("[m] Error: Invalid command");
                // Newline for formatting
                printf("\n");
                // Clearing the scanner
                char c;
                scanf("%c", &c);
            }

        // ------------------------
        // ACTOR SECTION:
        // ------------------------

        // a: Controls actors    
        } else if(choice == 'a') {
            // Clearing the scanner
            char c;
            scanf("%c", &c);

            // User input
            printf("\n[a] Enter operation code: ");
            scanf("%c", &choice);

            // i: Inserts a new actor into the database
            if(choice == 'i') {
                // Variables for actor struct and actor code
                int code;
                struct actor a;

                // Assigns code to the output of actorCode
                code = actorCode();
                // Calling on actor code function to get user input for new actor code
                if(code == -1) {
                    // Prints out a statement to tell the user that actor code cannot be negative
                    printf("[a-i] Error: Movie actor cannot be negative.\n");

                // Program continues if actor code is positive    
                } else {
                    if(searchActor(actorList, code) == NULL) {
                        // Creates a new actor struct using helper method
                        a = actorMaker(code);
                        // Tells the user the actor they have entered into the database
                        printf("[a-i] You entered into the database: Actor Code: %d, Actor Name: %s, Actor Profile: %s, Actor Age: %d", a.code, a.name, a.profile, a.age);
                        // Adds actor to actorList
                        actorList = addActor(actorList, a);
                        // Formatting
                        printf("\n");

                    } else {
                        // Prints an error message
                        printf("\n[a-i] Error: Actor code already exists in the database. (Press enter to continue)");
                    }
                }

                // Clearing the scanner
                char c;
                scanf("%c", &c);

            // s: Searches for an actor using actor code              
            } else if(choice == 's') {
                int tempCode;
                // User input
                printf("\n[a-s] Enter actor code: ");
                scanf("%d", &tempCode);

                struct actorNode *n = searchActor(actorList, tempCode);
                if(n == NULL) {
                    // Prints out an error
                    printf("\n[a-s] Error: Actor does not exist in the database.");
                    // Clearing the scanner
                    char c;
                    scanf("%c", &c);

                } else {
                    // Prints out actor
                    printf("[a-s] Actor found: ");
                    printf("Actor Code: %d, Actor Name: %s, Actor Profile: %s, Actor Age: %d\n", n->actor.code, n->actor.name, n->actor.profile, n->actor.age);
                    // Clearing the scanner
                    char c;
                    scanf("%c", &c);
                }

            // u: Updates an actor inside the database              
            } else if(choice == 'u') {
                // Variables for actor struct and actor code
                int update;
                int code;
                struct actor a;

                // Clearing the scanner
                char c;
                scanf("%c", &c);

                // User input
                printf("\n[a-u] Please enter the actor code you wish to update: ");
                scanf("%d", &update);

                // Assigns code to the output of actorCode
                code = actorCode();
                // Calling on actor code function to get user input for new actor code
                if(code == -1) {
                    // Prints out a statement to tell the user that actor code cannot be negative
                    printf("[a-u] Error: Actor code cannot be negative.\n");

                // Program continues if actor code is positive    
                } else {
                    if(searchActor(actorList, code) == NULL) {
                        // Creates a new actor struct using helper method
                        a = actorMaker(code);
                        
                        // Makes a new node to store the old node
                        struct actorNode *curr;
                        // Runs the search command to find the old actor code and return the node with it
                        curr = searchActor(actorList, update);

                        // If the search function returns a node
                        if(curr != NULL) {
                            // Updates the node completely
                            curr->actor.code = a.code;
                            curr->actor.name = a.name;
                            curr->actor.profile = a.profile;
                            curr->actor.age = a.age;
                            // Lets the user know the actor was updated successfully
                            printf("\n[a-u] Successfully updated actor.");

                        // If the search function does not return a node    
                        } else {
                            // Prints out an error message
                            printf("\n[a-u] Error: Actor was not found in the database.");
                        }

                    } else {
                        // Prints an error message if new code already exists in database
                        printf("\n[a-u] Error: Actor code already exists in the database. (Press enter to continue)");
                    }
                }

                // Clearing the scanner
                scanf("%c", &c);

            // p: Lists all of the actors in the database
            } else if(choice == 'p') {
                // Print statement
                printf("[a-p] ALL ACTORS IN DATABANK:\n");

                // New curr node to cycle through the list
                struct actorNode *curr;

                // For loop to loop through the entire linked list
                for(curr = actorList; curr != NULL; curr = curr->next) {
                    // Prints out all movies
                    printf("Actor Code: %d, Actor Name: %s, Actor Profile: %s, Actor Age: %d\n", curr->actor.code, curr->actor.name, curr->actor.profile, curr->actor.age);
                }

                // Clearing the scanner
                char c;
                scanf("%c", &c);

            // e: Deletes an actor from the database
            } else if(choice == 'e') {
                // Temp variable
                int code;

                // User input
                printf("\n[a-e] Please enter the actor code you wish to delete: ");
                scanf("%d", &code);

                // Quick search to find if the actor code entered exists or not
                struct actorNode *n = searchActor(actorList, code);
                // If actor code does not exist
                if(n == NULL) {
                    // Prints out an error
                    printf("[a-e] Error: Actor does not exist in the database.");
                    // Clearing the scanner
                    char c;
                    scanf("%c", &c);

                // If actor code does exist
                } else {
                    // Calls helper function to delete the node
                    actorList = deleteActor(actorList, code);
                    // Tells the user that the actor has been deleted
                    printf("[a-e] Successfully deleted actor.");
                    // Clearing the scanner
                    char c;
                    scanf("%c", &c);
                }

            // If the user enters an invalid command
            } else {
                printf("[a] Error: Invalid command");
                // Newline for formatting
                printf("\n");
                // Clearing the scanner
                char c;
                scanf("%c", &c);
            }


        // h: Lists out a list of commands    
        } else if(choice == 'h') {
            // Prints out a list of valid commands
            printf("\n[VER 2.0] LIST OF VALID COMMANDS:");
            printf("\n----------------------------------------------------");
            // Explain q
            printf("\nq - Exits out of the program.");
            printf("\n----------------------------------------------------");
            // Explain m and all the subcommands under m
            printf("\nm - Allows the user to control movies in the database.");
            printf("\n----------------------------------------------------");
            // Subcommands of m
            printf("\n  i - Inserts a new movie into the database.");
            printf("\n  s - Searches for a movie using movie code in the database.");
            printf("\n  u - Updates an existing movie in the database.");
            printf("\n  p - Prints out a list of all movies currently in the database.");
            printf("\n  e - Erases a movie from the database.");
            printf("\n----------------------------------------------------");
            // Explain a and all the subcommands under a
            printf("\na - Allows the user to control actors in the database.");
            printf("\n----------------------------------------------------");
            // Subcommands of a
            printf("\n  i - Inserts a new actor into the database.");
            printf("\n  s - Searches for an actor using actor code in the database.");
            printf("\n  u - Updates an existing actor in the database.");
            printf("\n  p - Prints out a list of all actors currently in the database.");
            printf("\n  e - Erases an actor from the database.");
            printf("\n----------------------------------------------------");
            // Explain h
            printf("\nh - Prints out a list of all valid commands.");
            printf("\n----------------------------------------------------");
            // Newline for formatting
            printf("\n");
            // Clearing the scanner
            char c;
            scanf("%c", &c);


        // If the user enters an invalid input    
        } else {
            printf("[HOME] Error: Invalid command");
            // Newline for formatting
            printf("\n");
            // Clearing the scanner
            char c;
            scanf("%c", &c);
        }
    }
}