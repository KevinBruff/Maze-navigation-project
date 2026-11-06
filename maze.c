#include "maze.h"
#include <stdio.h>
#include <stdlib.h>

char maze [11][10] = 
{
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'E', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'P', '#'},
    {'#', ' ', '#', '#', '#', '#', '#', '#', ' ', '#'},
    {'#', ' ', '#', 'B', ' ', ' ', ' ', '#', ' ', '#'},
    {'#', ' ', '#', ' ', '#', '#', ' ', '#', ' ', '#'},
    {'#', ' ', '#', ' ', '#', 'B', ' ', '#', ' ', '#'},
    {'#', ' ', '#', ' ', '#', '#', ' ', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
    {'#', ' ', '#', '#', ' ', '#', '#', '#', ' ', '#'},
    {'#', ' ', 'P', ' ', ' ', '#', '#', '#', ' ', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', 'S', '#'}
};

void loadMaze(Maze *m, const char *filename)
{
    (*m).row = 11; // Set the number of rows in the maze
    (*m).col = 10; // Set the number of columns in the maze
    // FILE *file = fopen(filename, "r");
    // if (!file)
    // {

    //     fprintf(stderr, "Error opening file: %s\n", filename);
    //     exit(1);
    // }

    // fscanf(file, "%d %d", &(*m).row, &(*m).col);
    for (int i = 0; i < (*m).row; i++)
    {
        for (int j = 0; j < (*m).col; j++)
        {
            // fscanf(file, " %c", &(*m).grid[i][j]);
            (*m).grid[i][j] = maze[i][j]; // Load the maze from the predefined array
            
            if ((*m).grid[i][j] == TILE_START)
            {
                (*m).start_x = i;
                (*m).start_y = j;
            }
        }
    }
    // fclose(file);
}

int isWall(Maze *m, int x, int y)
{
    return (*m).grid[x][y] == TILE_WALL;
}

int isBook(Maze *m, int x, int y)
{
    return (*m).grid[x][y] == TILE_BOOK;
}

int isPuzzle(Maze *m, int x, int y)
{
    return (*m).grid[x][y] == TILE_PUZZLE;
}

int isEnd(Maze *m, int x, int y)
{
    return (*m).grid[x][y] == TILE_END;
}

int hasPheromone(Maze *m, int x, int y)
{
    return (*m).grid[x][y] == TILE_PHEROMONE;
}

void markPheromone(Maze *m, int x, int y)
{
    char current_tile = (*m).grid[x][y];

    if (current_tile == TILE_EMPTY/*(*m).grid[x][y] == TILE_EMPTY || (*m).grid[x][y] == TILE_PUZZLE || (*m).grid[x][y] == TILE_BOOK || (*m).grid[x][y] == TILE_START*/) // Mark pheromone only on walkable tiles
    {
        (*m).grid[x][y] = TILE_PHEROMONE;
    }
}

void printMaze(Maze *m, FILE *out, int ant_x, int ant_y)
{
    for (int i = 0; i < m->row; i++)
    {
        for (int j = 0; j < m->col; j++)
        {
            if (i == ant_x && j == ant_y)
            {
                fputc('A', out);
            }
            else
            {
                fputc(m->grid[i][j], out);
            }
        }
        fputc('\n', out);
    }
    fputc('\n', out);
    fflush(out);
}