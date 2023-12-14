#include <stdio.h>
#include <stdlib.h>

typedef struct stack {
    int rear;
    int* arr;
} stack;

stack* initialize_stack(int sz){
    stack* q = malloc(sizeof(stack));
    q->arr = calloc(sizeof(int), sz);
    q->rear = 0;
}

int stackup(stack* q, int x){
    q->arr[q->rear++] = x;
}

int unstack(stack* q){
    return q->arr[--q->rear];
}

int main(){
    stack* stack1 = initialize_stack(10);
    stackup(stack1, 4);
    stackup(stack1, 5);
    printf("%d\n", unstack(stack1));
    printf("%d\n", unstack(stack1));
}