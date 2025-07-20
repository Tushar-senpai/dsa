#include<stdio.h>

struct Stack {
    int top;
    unsigned capacity;
    int* array;
};

int isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}
 void push(struct Stack* stack, int item) {
    if (isFull(stack)) {
        printf("Stack overflow\n");
        return;
    }
    stack->array[++stack->top] = item;
}
void pop(struct Stack* stack) {
    if (stack->top == -1) {
        printf("Stack underflow\n");
        return;
    }
    stack->top--;
}

int peek(struct Stack* stack) {
    if (stack->top == -1) {
        printf("Stack is empty\n");
        return -1; // Return an invalid value or handle error appropriately
    }
    return stack->array[stack->top];
}

int main() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = 100;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));

    push(stack, 10);
    push(stack, 20);
    printf("Top element is %d\n", peek(stack));
    pop(stack);
    printf("Top element after pop is %d\n", peek(stack));

    free(stack->array);
    free(stack);
    return 0;
}
