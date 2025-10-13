#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure Definitions
typedef struct StackNode {
    int data;
    struct StackNode* next;
} StackNode;

typedef struct Stack {
    StackNode* top;
} Stack;

// Function Prototypes
Stack* createStack();
bool isEmpty(Stack* stack);
void push(Stack* stack, int data);
int takeout(Stack* stack);
int peek(Stack* stack);
void freeStack(Stack* stack);
void display(Stack* stack);

#endif // STACK_H