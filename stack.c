#include "stack.h"
#include <stdio.h>

void initStack(Stack *s)
{
    (*s).top = -1;
}

int isEmpty(Stack *s)
{
    return (*s).top == -1;
}

int isFull(Stack *s)
{
    return (*s).top == MAX_SIZE - 1;
}

void push(Stack *s, Position pos)
{
    if (!isFull(s))
    {
        (*s).data[++(*s).top] = pos;
    }
}

Position pop(Stack *s)
{
    if (!isEmpty(s))
    {
        return (*s).data[(*s).top--];
    }
    Position empty = {-1, -1}; // Return an invalid position if stack is empty
    return empty;
}

Position peek(Stack *s)
{
    if (!isEmpty(s))
    {
        return (*s).data[(*s).top];
    }
    Position empty = {-1, -1}; // Return an invalid position if stack is empty
    return empty;
}

void clear(Stack *s)
{
    (*s).top = -1;
}