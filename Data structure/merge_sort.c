#include <stdio.h>

void merge(int arr[], int l, int m, int r){
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    int i, j, k;

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while(i < n1 && j < n2){
        if(L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        } else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while(i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }
    while(j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }

}

void mergeSort(int arr[]){
    int n, l, r, m, currsz;
    n = 2 * sizeof(arr) / sizeof(int);
   
    for(currsz = 1; currsz < n; currsz *= 2){
        for(l = 0; l < n - 1; l += currsz * 2){
            m = l + currsz - 1;
            r = l + 2 * currsz - 1;

            if(r >= n)
                r = n - 1;
            merge(arr, l, m, r);
        }
    }
}

int main(){
    int array[] = {7,2,8,1};
    mergeSort(array);
    for(int i = 0; i < 4; i++)
        printf("%d ", array[i]);
    printf("\n");
}