#include "Stack.h"

// Function to create a new stack
Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) {
        printf("Memory allocation failed for stack.\n");
        return NULL;
    }
    stack->top = NULL;
    return stack;
}

// Function to check if the stack is empty
bool isEmpty(Stack* stack) {
    if (stack->top == NULL) {
        return true;
    }
    return false;
}

// Function to push an element onto the stack
void push(Stack* stack, int data) {
    if (stack == NULL) {
        printf("Stack is not initialized.\n");
        return;
    }
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (newNode == NULL) {
        printf("Memory allocation failed for new node.\n");
        return;
    }
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

// Function to pop an element from the stack 
int takeout(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty. Cannot pop.\n");
        return -1; // Indicating that the stack is empty
    }
    StackNode* temp = stack->top;
    int poppedValue = temp->data;
    stack->top = stack->top->next;
    free(temp);
    return poppedValue;
}

// Function to peek at the top element of the stack without removing it
int peek(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty. Cannot peek.\n");
        return -1; // Indicating that the stack is empty
    }
    return stack->top->data;
}

// Function to free the stack
void freeStack(Stack* stack) {
    if (stack == NULL) {
        return;
    }
    StackNode* current = stack->top;
    StackNode* nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    free(stack);
}

// Function to display the stack (for debugging purposes)
void display(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
        return;
    }
    StackNode* temp = stack->top;
    printf("Stack (top to bottom): ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}
