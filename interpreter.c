#include "interpreter.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CMD_LENGTH 50
#define MAX_RP_CMDS 200

// Execute a single command for the ant

static void executeCommand(Ant *a, const char *cmd)

{
    if(strcmp(cmd, "MOVE_F") == 0) moveF(a), markPheromone(a->maze, a->x, a->y);
    else if(strcmp(cmd, "MOVE_B") == 0) moveB(a), markPheromone(a->maze, a->x, a->y);
    else if(strcmp(cmd, "MOVE_L") == 0) moveL(a), markPheromone(a->maze, a->x, a->y);
    else if(strcmp(cmd, "MOVE_R") == 0) moveR(a), markPheromone(a->maze, a->x, a->y);

    else if(strcmp(cmd, "CWL") == 0) checkLeft(a);
    else if(strcmp(cmd, "CWR") == 0) checkRight(a);
    else if(strcmp(cmd, "CWF") == 0) checkForward(a);
    else if(strcmp(cmd, "CWB") == 0) checkBack(a);

    else if(strcmp(cmd, "BJPI") == 0) BJPI(a), markPheromone(a->maze, a->x, a->y);
    else if(strcmp(cmd, "CJPI") == 0) CJPI(a), markPheromone(a->maze, a->x, a->y);

    else if(strcmp(cmd, "PUSH") == 0) antPush(a);
    else if(strcmp(cmd, "POP") == 0) antPop(a);
    else if(strcmp(cmd, "PEEK") == 0) antPeek(a);
    else if(strcmp(cmd, "CLEAR") == 0) clear(a->memory);

    else if(strcmp(cmd, "BACKTRACK") == 0) backtrack(a);

    //else if(strcmp(cmd, "MARK") == 0) markPheromone(a->maze, a->x, a->y);

    else
    {
        printf("Unknown command: %s\n", cmd);
    }
}

// Main function to run the ant's program from a file

void runProgram(Ant *a, const char *input, const char *output) 
{
    // Open the input file containing the ant's program
    FILE *in = fopen(input, "r");
    FILE *out = fopen(output, "w");

    if(!in)
    {
        fprintf(stderr, "Error opening input file: %s\n", input);
        exit(1);
    }
    if(!out)
    {
        fprintf(stderr, "Error opening output file: %s\n", output);
        exit(1);
    }

    char cmd[MAX_CMD_LENGTH];

    while(fscanf(in, "%s", cmd) != EOF)
    {
        executeCommand(a, cmd);
        printMaze(a->maze, out, a->x, a->y);
        //
        //Handle the RP command separately since it has a different format and requires multiple commands to be read
        //
        if(strcmp(cmd, "RP") == 0)
        {
            int n, t;
            fscanf(in, "%d %d", &n, &t); // Read the expected number of steps and points after executing the command

            char rpCmds[MAX_RP_CMDS][MAX_CMD_LENGTH];

            for(int i = 0; i < n; i++)
            {
                fscanf(in, "%s", rpCmds[i]); // Read the RP commands
            }
    

            for(int rep = 0; rep < t; rep++)
            {
                for(int i = 0; i < n; i++)
                {
                    executeCommand(a, rpCmds[i]); // Execute the RP commands
                    printMaze(a->maze, out, a->x, a->y);
                    fprintf(out, "After command: %s, Steps: %d, Points: %d, Position: (%d, %d)\n", rpCmds[i], a->steps, a->total_points, a->x, a->y);
                }
            }
            continue;
        }

        // Normal command execution for non-RP commands
        fprintf(out, "After command: %s, Steps: %d, Points: %d, Position: (%d, %d)\n", cmd, a->steps, a->total_points, a->x, a->y);
        printMaze(a->maze, out, a->x, a->y);
    }

    fclose(in);
    fclose(out);
}