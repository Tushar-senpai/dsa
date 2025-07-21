#include<stdio.h>
#include<stdlib.h>  

struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
};

int isFull(struct Queue* queue) {
    return queue->size == queue->capacity;
}   



void enqueue(struct Queue* queue, int item) {
    if (isFull(queue)) {
        printf("Queue overflow\n");
        return;
    }
    queue->array[queue->rear] = item;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->size++;
}


int isEmpty(struct Queue* queue) {
    return queue->size == 0;
}

void dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue underflow\n");
        return;
    }
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
}

void display(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue elements: ");
    for (int i = 0; i < queue->size; i++) {
        printf("%d ", queue->array[(queue->front + i) % queue->capacity]);
    }
    printf("\n");
}

void peek(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Front element is %d\n", queue->array[queue->front]);
}

int main() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = 100;
    queue->front = 0;
    queue->rear = 0;
    queue->size = 0;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));

    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    display(queue);
    
    peek(queue);
    
    dequeue(queue);
    display(queue);
    
    peek(queue);

    free(queue->array);
    free(queue);
    return 0;
}