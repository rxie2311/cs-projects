#ifndef MOVIETHEATERDB_H
#define MOVIETHEATERDB_H

#include "movieTheaterDB_movie.h"
#include "movieTheaterDB_actor.h"

/*
* Name: Raymond Xie
* Student No: 251275727
*/

// Function declaration (MOVIES)
struct movieNode *addMovie(struct movieNode *movieList, struct movie movie);
struct movieNode *searchMovie(struct movieNode *movieList, int code);
struct movieNode *deleteMovie(struct movieNode *list, int code);

// Function declaration (ACTORS)
struct actorNode *addActor(struct actorNode *actorList, struct actor actor);
struct actorNode *searchActor(struct actorNode *actorList, int code);
struct actorNode *deleteActor(struct actorNode *actorList, int code);

// Structure declaration (MOVIES)
struct movieNode {
    // Variables in the structure
    // Data stored in the node
    struct movie movie;
    // Pointer to the next node
    struct movieNode *next;
};

// Structure declaration (ACTORS)
struct actorNode {
    // Variables in the structure
    // Data stored in the node
    struct actor actor;
    // Pointer to the next node
    struct actorNode *next;
};

#endif