#include <stdio.h>
#include <stdlib.h>

typedef struct queue {
    int front;
    int rear;
    int* arr;
} queue;

queue* initialize_queue(int sz){
    queue* q = malloc(sizeof(queue));
    q->arr = calloc(sizeof(int), sz);
    q->front = 0;
    q->rear = 0;
}

int enqueue(queue* q, int x){
    q->arr[q->rear++] = x;
}

int dequeue(queue* q){
    return q->arr[q->front++];
}

int main(){
    queue* queue1 = initialize_queue(10);
    enqueue(queue1, 4);
    enqueue(queue1, 5);
    printf("%d\n", dequeue(queue1));
    printf("%d\n", dequeue(queue1));
}