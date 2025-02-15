#ifndef MOVIETHEATERDB_ACTOR_H
#define MOVIETHEATERDB_ACTOR_H

/*
* Name: Raymond Xie
* Student No: 251275727
*/

// Function declaration
int actorCode(void);
struct actor actorMaker(int code);

// Structure declaration
struct actor {
    // Variables in the structure
    int code;
    char *name;
    char *profile;
    int age;
};

#endif