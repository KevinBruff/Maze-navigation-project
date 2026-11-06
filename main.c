#include <stdio.h>
#include "maze.h"
#include "stack.h"
#include "ant.h"
#include "interpreter.h"

int main()
{
    Maze maze;
    Stack memory;
    Ant michael;

    // Initalize the maze, stack, and ant
    initStack(&memory);
    loadMaze(&maze, "maze.txt");
    initAnt(&michael, &maze, &memory);

    // Run Michael's program from the input file and write output to the output file
    runProgram(&michael, "brain.txt", "output.txt");

    // Print final results

    printf("\n=== Simulation Complete ===\n");
    printf("Final Position: (%d, %d)\n", michael.x, michael.y);
    printf("Books Collected: %d\n", michael.books);
    printf("Puzzles Solved: %d\n", michael.puzzles_solved);
    printf("Total Points: %d\n", michael.total_points);
    printf("Total Steps: %d\n", michael.steps);

    return 0;
}