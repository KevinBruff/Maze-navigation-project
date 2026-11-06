#include "ant.h"
#include "maze.h"
#include <stdio.h>

static void resetItches(Ant *a)
{
    a->itch_left = 0;
    a->itch_right = 0;
    a->itch_forward = 0;
    a->itch_back = 0;
    a->last_checked_direction = DIR_NONE;
}

void initAnt(Ant *a, Maze *m, Stack *s)
{
    (*a).maze = m; 
    (*a).memory = s;

    (*a).x = (*m).start_x;
    (*a).y = (*m).start_y;

    resetItches(a);

    (*a).steps = 0;
    (*a).max_steps = MAX_NUMBER_OF_STEPS; // Set a maximum number of steps to prevent infinite loops

    (*a).books = 0;
    (*a).puzzles_solved = 0;
    (*a).total_points = 0;
}

// Movement functions

static int canMoveTo(Ant *a, int new_x, int new_y)
{
    // Check if the new position is within bounds and not a wall
    //return new_x >= 0 && new_x < MAX_COLS && new_y >= 0 && new_y < MAX_ROWS && !isWall((*a).maze, new_x, new_y);
    if (new_x < 0 || new_y < 0 || new_x >= a->maze->row || new_y >= a->maze->col)
        return 0;

    return !isWall(a->maze, new_x, new_y);
}

void moveF(Ant *a)
{
    if((*a).steps >= (*a).max_steps)
    {
        printf("Maximum steps reached. Cannot move forward.\n");
        return;
    }

    // Implement the logic to move the ant forward
    int new_x = (*a).x - 1; // Assuming forward is to the right
    int new_y = (*a).y;

    if (canMoveTo(a, new_x, new_y))
    {
        (*a).x = new_x;
        (*a).y = new_y;
        checkForItems(a);
        checkForExit(a);
    }
    resetItches(a);
    (*a).steps++;
}

void moveB(Ant *a)
{
    if((*a).steps >= (*a).max_steps)
    {
        printf("Maximum steps reached. Cannot move backward.\n");
        return;
    }

    // Implement the logic to move the ant backward
    int new_x = (*a).x + 1; // Assuming backward is to the left
    int new_y = (*a).y;

    if (canMoveTo(a, new_x, new_y))
    {
        (*a).x = new_x;
        (*a).y = new_y;
        checkForItems(a);
        checkForExit(a);
    }
    resetItches(a);
    (*a).steps++;
}

void moveL(Ant *a)
{
    if((*a).steps >= (*a).max_steps)
    {
        printf("Maximum steps reached. Cannot move left.\n");
        return;
    }

    // Implement the logic to move the ant left
    int new_x = (*a).x; // Assuming left is to the left
    int new_y = (*a).y - 1;

    if (canMoveTo(a, new_x, new_y))
    {
        (*a).x = new_x;
        (*a).y = new_y;
        checkForItems(a);
        checkForExit(a);
    }
    resetItches(a);
    (*a).steps++;
}

void moveR(Ant *a)
{
    if((*a).steps >= (*a).max_steps)
    {
        printf("Maximum steps reached. Cannot move right.\n");
        return;
    }

    // Implement the logic to move the ant right
    int new_x = (*a).x; // Assuming right is to the right
    int new_y = (*a).y + 1;

    if (canMoveTo(a, new_x, new_y))
    {
        (*a).x = new_x;
        (*a).y = new_y;
        checkForItems(a);
        checkForExit(a);
    }
    resetItches(a);
    (*a).steps++;
    
}

// Checking functions (CWL, CWR, etc functions)

static int CheckDirection(Ant *a, int dx, int dy)
{
    int count = 0;
    int new_x = (*a).x + dx;
    int new_y = (*a).y + dy;

    while (canMoveTo(a, new_x, new_y) && !hasPheromone((*a).maze, new_x, new_y))
    {
        count++;
        new_x += dx;
        new_y += dy;
    }
    return count;
}

void checkForItems(Ant *a)
{
    if (isBook((*a).maze, (*a).x, (*a).y))
    {
        (*a).books++;
        (*a).maze->grid[(*a).x][(*a).y] = TILE_EMPTY; // Remove the book from the maze
        printf("Book collected at (%d, %d)! Total books: %d\n", (*a).x, (*a).y, (*a).books);
    }

    if (isPuzzle((*a).maze, (*a).x, (*a).y))
    {
        if((*a).books > 0) // Check if the ant has a book to solve the puzzle
        {
            (*a).books--; // Use one book to solve the puzzle
            (*a).puzzles_solved++;
            (*a).maze->grid[(*a).x][(*a).y] = TILE_EMPTY; // Remove the puzzle from the maze
            (*a).total_points += 5; // Assuming each puzzle is worth 5 points
        }
        else
        {
            printf("Puzzle at (%d, %d) cannot be solved without a book!\n", (*a).x, (*a).y);
        }
    }
}

void checkForExit(Ant *a)
{
    if (isEnd((*a).maze, (*a).x, (*a).y))
    {
        printf("You've reached the exit at (%d, %d)!\n", (*a).x, (*a).y);
    }
}

int checkLeft(Ant *a)
{
    // Reset stale checks and evaluate the left direction
    resetItches(a);
    int free = CheckDirection(a, 0, -1); // Check left direction
    a->itch_left = free;
    a->last_checked_direction = free > 0 ? DIR_LEFT : DIR_NONE;
    return free;
}

int checkRight(Ant *a)
{
    // Reset stale checks and evaluate the right direction
    resetItches(a);
    int free = CheckDirection(a, 0, +1); // Check right direction
    a->itch_right = free;
    a->last_checked_direction = free > 0 ? DIR_RIGHT : DIR_NONE;
    return free;
}

int checkForward(Ant *a)
{
    // Reset stale checks and evaluate the forward direction
    resetItches(a);
    int free = CheckDirection(a, -1, 0); // Check forward direction
    a->itch_forward = free;
    a->last_checked_direction = free > 0 ? DIR_FORWARD : DIR_NONE;
    return free;
}

int checkBack(Ant *a)
{
    // Reset stale checks and evaluate the back direction
    resetItches(a);
    int free = CheckDirection(a, +1, 0); // Check back direction
    a->itch_back = free;
    a->last_checked_direction = free > 0 ? DIR_BACK : DIR_NONE;
    return free;
}

// Jumping functions (BJPI and CJPI)

void BJPI(Ant *a)
{
    // Implement the logic for the BJPI command
    int dx = 0, dy = 0;
    int distance = 0;

    switch (a->last_checked_direction)
    {
        case DIR_LEFT:
            dx = 0;
            dy = -1;
            distance = a->itch_left;
            break;
        case DIR_RIGHT:
            dx = 0;
            dy = +1;
            distance = a->itch_right;
            break;
        case DIR_FORWARD:
            dx = -1;
            dy = 0;
            distance = a->itch_forward;
            break;
        case DIR_BACK:
            dx = +1;
            dy = 0;
            distance = a->itch_back;
            break;
        default:
            printf("No valid direction checked. Cannot jump.\n");
            return;
    }

    if (distance <= 0)
    {
        printf("Checked direction is not valid. Cannot jump.\n");
        resetItches(a);
        return;
    }

    // Attempt to jump in the determined direction and distance
    for(int i = 0; i < distance; i++)
    {
        if((*a).steps >= (*a).max_steps)
        {
            printf("Maximum steps reached. Cannot jump.\n");
            resetItches(a);
            return;
        }

        int new_x = (*a).x + dx;
        int new_y = (*a).y + dy;

        if (canMoveTo(a, new_x, new_y))
        {
            (*a).x = new_x;
            (*a).y = new_y;
            checkForItems(a);
            checkForExit(a);
            markPheromone(a->maze, a->x, a->y);
            (*a).steps++;
        }
        else
        {
            printf("Jump direction is blocked. Stopping jump.\n");
            break; // Stop jumping if we hit a wall or boundary
        }
    }
    resetItches(a);
}

void CJPI(Ant *a)
{
    if((*a).steps >= (*a).max_steps)
    {
        printf("Maximum steps reached. Cannot jump.\n");
        return;
    }

    // Implement the logic for the CJPI command
    int dx = 0, dy = 0;

    switch (a->last_checked_direction)
    {
        case DIR_LEFT:
            dx = 0;
            dy = -1;
            break;
        case DIR_RIGHT:
            dx = 0;
            dy = +1;
            break;
        case DIR_FORWARD:
            dx = -1;
            dy = 0;
            break;
        case DIR_BACK:
            dx = +1;
            dy = 0;
            break;
        default:
            printf("No valid direction checked. Cannot jump.\n");
            return;
    }

    int new_x = (*a).x + dx;
    int new_y = (*a).y + dy;

    if (canMoveTo(a, new_x, new_y))
    {
        (*a).x = new_x;
        (*a).y = new_y;
        checkForItems(a);
        checkForExit(a);
    }
    else
    {
        printf("Jump direction is blocked. Cannot jump.\n");
    }

    resetItches(a);
    // Regardless of whether the move was successful, we increment the steps
    (*a).steps++;
}

// Memory functions (PUSH, POP, PEEK)

void antPush(Ant *a)
{
    // Implement the logic to push the current position onto the stack
    Position pos = {(*a).x, (*a).y};
    push((*a).memory, pos); 
}

void antPop(Ant *a)
{
    // Implement the logic to pop a position from the stack and move the ant there
    /*Position pos =*/ pop((*a).memory);
    // Pop only retrieves the position; Backtracking to that position is handled in the backtrack function
}

void antPeek(Ant *a)
{
    // Implement the logic to peek at the top position of the stack without moving the ant
    /*Position pos =*/ peek((*a).memory);
    // Peeking only retrieves the position; Backtracking to that position is handled in the backtrack function
}

// Backtracking function

void backtrack(Ant *a)
{
    if((*a).steps >= (*a).max_steps)
    {
        printf("Maximum steps reached. Cannot jump.\n");
        return;
    }

    // Implement the logic to backtrack the ant to the previous position
    Position pos = pop((*a).memory);

    if (pos.x == -1 && pos.y == -1) // Check if the stack was empty
    {
        printf("Backtrack failed: stack is empty.\n");
        return; // Empty stack, cannot backtrack
    }
    (*a).x = pos.x;
    (*a).y = pos.y;
    resetItches(a);
    (*a).steps++;
}