#ifndef ANT_H
#define ANT_H

#include "maze.h"
#include "stack.h"

#define MAX_NUMBER_OF_STEPS 100 // Define a maximum number of steps to prevent infinite loops

typedef enum
{
    DIR_NONE = 0,
    DIR_LEFT,
    DIR_RIGHT,
    DIR_FORWARD,
    DIR_BACK
} Direction;

typedef struct
{
    int x, y;
    int itch_left;
    int itch_right;
    int itch_forward;
    int itch_back;
    Direction last_checked_direction;
    int steps;
    int books;
    int puzzles_solved;
    int total_points;
    int max_steps;
    Maze *maze; 
    Stack *memory;
} Ant;

void initAnt(Ant *a, Maze *m, Stack *s);

// Movement functions
void moveF(Ant *a);
void moveB(Ant *a);
void moveL(Ant *a);
void moveR(Ant *a);

// Checking (CWL, CWR, etc functions)
int checkLeft(Ant *a);
int checkRight(Ant *a);
int checkForward(Ant *a);
int checkBack(Ant *a);
void checkForItems(Ant *a); // Check for books or puzzles at the current position and update the ant's state accordingly
void checkForExit(Ant *a); // Check if the ant has reached the exit

// Jumping functions
void BJPI(Ant *a);
void CJPI(Ant *a);

//Memory functions
void antPush(Ant *a);
void antPop(Ant *a);
void antPeek(Ant *a);

//Backtracking functions
void backtrack(Ant *a);

#endif
