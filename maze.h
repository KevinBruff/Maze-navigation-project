#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>

#define MAX_ROWS 100
#define MAX_COLS 100

//Tile types
#define TILE_WALL '#'
#define TILE_START 'S'
#define TILE_END 'E'
#define TILE_BOOK 'B'
#define TILE_PUZZLE 'P'
#define TILE_EMPTY ' '
#define TILE_PHEROMONE 'F' // New tile type for pheromones

typedef struct 
{
    char grid[MAX_ROWS][MAX_COLS];
    int row;
    int col;
    int start_x;
    int start_y;
} Maze;

void loadMaze(Maze *m, const char *filename);
int isWall(Maze *m, int x, int y);
int isBook(Maze *m, int x, int y);
int isPuzzle(Maze *m, int x, int y);
int isEnd(Maze *m, int x, int y);
int hasPheromone(Maze *m, int x, int y);
void markPheromone(Maze *m, int x, int y);
void printMaze(Maze *m, FILE *out, int ant_x, int ant_y);

#endif