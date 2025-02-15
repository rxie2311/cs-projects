#ifndef MOVIETHEATERDB_MOVIE_H
#define MOVIETHEATERDB_MOVIE_H

/*
* Name: Raymond Xie
* Student No: 251275727
*/

// Function declaration
int movieCode(void);
struct movie movieMaker(int code);

// Structure declaration
struct movie {
    // Variables in the structure
    int code;
    char *name;
    char *genre;
    float rating;
};

#endif