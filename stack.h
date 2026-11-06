#ifndef STACK_H
#define STACK_H

#define MAX_SIZE 100 

typedef struct 
{
    int x;
    int y;
} Position;

typedef struct 
{
    Position data[MAX_SIZE];
    int top;
} Stack;

void initStack(Stack* s);
int isEmpty(Stack* s);
int isFull(Stack* s);
void push(Stack* s, Position pos);
Position pop(Stack* s);
Position peek(Stack* s);
void clear(Stack* s);

#endif