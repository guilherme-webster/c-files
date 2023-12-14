#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// the heap is stored in an array and if the root has index i, it's children will be in the 2i+1 and 2i+2 positions of the array
// max heap

int sz = 0; // array sz
int heapsz = 0;

void swap(int *x, int *y){
    int aux = *y;
    *y = *x;
    *x = aux;
}

int* initialize(int sz){
    int* heap = malloc(sizeof(int) * sz);
    if(!heap)
        return NULL;
    for(int i = 0; i < sz; i++)
        heap[i] = INT_MIN;
    
    return heap;
}

void heap(int array[], int sz, int i){ // heapify down
    int max, right, left;
    
    max = i;
    left = 2 * i + 1;
    right = 2 * i + 2;
    if(left < sz && array[left] > array[max])
        max = left;
    if(right < sz && array[right] > array[max])
        max = right;
    if(max != i){
        swap(&array[i], &array[max]);
        heap(array, sz, max);
    }
}

void heapu(int array[], int i){ // heapify up
    int dad;
    if(i == 0){ // if i is the root index, just return
        return;
    }
    else{
        if(i % 2 == 0)
            dad = i / 2 - 1;
        else
            dad = i / 2;
        if(array[i] > array[dad]){
            swap(&array[i], &array[dad]);
            heapu(array, dad);
        }
    }
}


void resize(int** array, int* sz){
    int* newheap = initialize(2 * *sz);
    if(!newheap)
        return;
    
    for(int i =0; i < *sz; i++){
        if((*array)[i] != INT_MIN && (*array)[i] != INT_MIN + 1)
            newheap[i] = (*array)[i];
    }

    *sz = 2 * *sz;
    free(*array);
    *array = newheap;
}

void insert(int** array, int* sz, int* heapsz, int new) {
    int i;
    if (*heapsz == 0) {
        (*array)[0] = new;
        (*heapsz)++;
    } else {
        (*array)[*heapsz] = new;
        (*heapsz)++;
        if ((float)(*heapsz) / *sz > 0.7)
            resize(array, sz);
        heapu(*array, *heapsz - 1);
        }
    }

void remove_max(int* array, int* sz, int* heapsz) {
    int i;
    if (*heapsz == 0) {
        return;
    } else {
        int max = array[0];

        swap(&array[0], &array[*heapsz - 1]);
        (*heapsz)--;

        heap(array, *sz, 0);
    }
}


void print(int array[], int sz){
    int i;
    for(i = 0; i < sz; i++){
        if(array[i] != INT_MIN && array[i] != INT_MIN + 1)
            printf("%d ",array[i]);
    }
    printf("\n");
}

void increase(int array[], int i, int k){
    array[i] = k;
    heapu(array, i);
}

// Soring an array in increasing order
void heapSort(int arr[], int N)
{
 
    // Build heap (rearrange array)
    for (int i = N / 2 - 1; i >= 0; i--)
        heap(arr, N, i);
 
    // One by one extract an element
    // from heap
    for (int i = N - 1; i > 0; i--) {
 
        // Move current root to end
        swap(&arr[0], &arr[i]);
 
        // call max heapify on the reduced heap
        heap(arr, i, 0);
    }
}

// Soring an k sorted array in increasing order
void heapKSort(int arr[], int N, int k)
{
 
    // Build heap (rearrange array) (k + 1 sized)
    for (int i = k; i >= 0; i--)
        heap(arr, N, i);
 
    // One by one extract an element
    // from heap
    for (int i = N - 1; i > 0; i--) {
 
        // Move current root to end
        swap(&arr[0], &arr[i]);
 
        // call max heapify on the reduced heap
        heap(arr, i, 0);
    }
}

int main(){
    int sz = 3;
    int* heap1 = initialize(sz);
    int heapsz = 0;
    int array[6] = {1, 2, 3, 4, 5, 6};
    int array2[7] = {6, 5, 3, 2, 8, 10, 9};
    insert(&heap1, &sz, &heapsz, 4);
    insert(&heap1, &sz, &heapsz, 5);
    insert(&heap1, &sz, &heapsz, 6);
    insert(&heap1, &sz, &heapsz, 7);
    //remove_max(heap, &sz, &heapsz);
    //increase(heap1, 1, 10);
    //print(array, 6);
    //heapSort(array, 6);
    //print(array, 6);
    heapKSort(array2, 7, 3);
    print(array2, 7);
}