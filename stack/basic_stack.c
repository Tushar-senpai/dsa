#include<stdio.h>

struct Stack {
    int top;
    unsigned capacity;
    int* array;
};

int isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}
