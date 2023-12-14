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
        heap[i] = INT_MAX;
    
    return heap;
}

void heap(int array[], int sz, int i){ // heapify down
    int min, right, left;
    
    min = i;
    left = 2 * i + 1;
    right = 2 * i + 2;
    if(left < sz && array[left] < array[min])
        min = left;
    if(right < sz && array[right] < array[min])
        min = right;
    if(min != i){
        swap(&array[i], &array[min]);
        heap(array, sz, min);
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
        if(array[i] < array[dad]){
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
        if((float)(*heapsz) / *sz > 0.7)
            resize(array, sz);
        heapu(*array, *heapsz - 1);;
        }
    }

void remove_min(int* array, int* sz, int* heapsz) { // remove can be implemented for any valid idx, you just have to change the 0 idx for i
    int i;
    if (*heapsz == 0) {
        return;
    } else {
        int min = array[0];

        swap(&array[0], &array[*heapsz - 1]);
        //array[*heapsz - 1] = INT_MAX;
        (*heapsz)--;

        heap(array, *sz, 0);
    }
}

void print(int array[], int heapsz){
    int i;
    for(i = 0; i < heapsz; i++){
        if(array[i] != INT_MAX && array[i] != INT_MAX - 1)
            printf("%d ",array[i]);
    }
    printf("\n");
}

void print_kth_greatest(int* array, int sz, int k){
    for(int i = sz / 2 - 1; i >= 0; i--){
        heap(array, sz, i);
    }
    int counter = sz;
    while(k < counter){
        remove_min(array, &sz, &sz); // supposing array sz == heap sz
        counter--;
    }
    for(int i = 0; i < k; i++) 
        printf("%d ", array[i]);
    printf("\n");
}

// Soring an array in decreasing order
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
 
        // call min heapify on the reduced heap
        heap(arr, i, 0);
    }
}

void printSmallerThan(int arr[], int heapsz, int idx,int x){
    int left = 2*idx + 1;
    int right = 2*idx + 2;

    if(idx >= heapsz)
        return;
    if(arr[idx] >= x)
        return;
    printf("%d ", arr[idx]);
    printSmallerThan(arr, heapsz, left, x);
    printSmallerThan(arr, heapsz, right, x);
}

int main(){
    int sz = 3;
    int* heap = initialize(sz);
    int heapsz = 0;
    int array[12] = {11, 3, 2, 1, 15, 5, 4, 45, 88, 96, 50, 45};
    insert(&heap, &sz, &heapsz, 7);
    insert(&heap, &sz, &heapsz, 6);
    insert(&heap, &sz, &heapsz, 5);
    insert(&heap, &sz, &heapsz, 4);
    remove_min(heap, &sz, &heapsz);
    //print(heap, heapsz);
    heapSort(array, 12);
    print(array, 12);
    print_kth_greatest(array, 12, 3);
}