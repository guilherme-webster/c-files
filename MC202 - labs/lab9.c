#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "dequef.h"

/**
   Create an empty deque of floats.

   capacity is both the initial and minimum capacity.
   factor is the resizing factor, larger than 1.0.

   On success it returns the address of a new dequef.
   On failure it returns NULL.
**/
dequef* df_alloc(long capacity, double factor) {
   dequef* D;

   D = (dequef *)malloc(sizeof(dequef));
   D->cap = capacity;
   D->first = 0;
   D->factor = factor;
   D->data = (float *)malloc(sizeof(float) * capacity + 1) ;
   D->size = 0;
   D->mincap = capacity;
   return D;
}

/**
  Release a dequef and its data.
**/
void df_free(dequef* D) {
   free(D->data); // liberamos o array
   free(D); // e depois a estrutura
}

/**
   The size of the deque.
**/
long df_size(dequef* D) {
   return D->size;
}

float* resize(dequef* D){
   float* new = NULL;
   long newcap = 0;
   // Checamos em qual caso de redimensionamento estamos, daí vemos qual a nova capacidade do array
   if (D->size == D->cap){
    newcap =  D->cap * D->factor;
   } else if (D->size == (D->cap / (D->factor * D->factor))) {
      if ((D->cap / D->factor) < D->mincap)
       newcap = D->mincap;
      else
       newcap = (D->cap / D->factor);
   }  
   
   if (newcap) // se a capacidade deve ser atualizada, devemos também mudar o array
      new = (float *)malloc(newcap * sizeof(float)); // alocamos dinamicamente a memória

   if (!new)
      return NULL; // retornamos nulo se a alocação falhar, ou não entrarmos em nenhum caso de redimensionamento

   for (long i = 0; i < D->size; i++){
         long idx = (D->first + i) % D->cap; // aproveitamos a cópia, para colocar o first no índice zero, etc.
         new[i] = D->data[idx];
      }

   free(D->data);
   D->data = new; // atualizamos os dados do array
   D->first = 0;
   D->cap = newcap;
   return new;
}

/**
   Add x to the end of D.

   If the array is full, it first tries to increase the array size to
   capacity*factor.

   On success it returns 1.
   If attempting to resize the array fails then it returns 0 and D remains unchanged.
**/
int df_push(dequef* D, float x) {
   if (D->size < D->cap){
      D->data[(D->size + D->first) % D->cap] = x;
      D->size++;
      return 1;
   } else { // estouramos a capacidade do array
      float* new = resize(D);
      if (new == NULL)
         return 0;
      else {
         D->data[(D->size + D->first) % D->cap] = x;
         D->size++;
         return 1;
      }

   }
}

/**
   Remove a float from the end of D.

   If the deque has capacity/(factor^2) it tries to reduce the array size to
   capacity/factor.  If capacity/factor is smaller than the minimum capacity,
   the minimum capacity is used instead.  If it is not possible to resize, then
   the array size remains unchanged.

   This function returns the float removed from D.
   If D was empty prior to invocation, it returns 0.0 and D remains unchanged.
**/
float df_pop(dequef* D) {
   float* new = NULL;
   int did_fail = 0;

   if (D->size == 0)
      return 0;

   if (D->size == (D->cap / (D->factor * D->factor))) { // muitos elementos não ocupados
     new = resize(D);
     if (!new)
      did_fail = 1;
   }

   if (!did_fail) // did_fail serve para sabermos se devemos decrementar ou não o size
      D->size--;
   return D->data[D->size];
}

/**
   Add x to the beginning of D.

   If the array is full, it first tries to increase the array size to
   capacity*factor.

   On success it returns 1.
   If attempting to resize the array fails then it returns 0 and D remains unchanged.
**/
int df_inject(dequef* D, float x) { // nao funciona (coloca no final) e buga a funcao pop (?)

   if (D->size < D->cap){
    if (D->size > 0)
        D->first = ((D->first + D->cap - 1) % D->cap);
    D->data[D->first] = x;
    D->size++;
    return 1;
   } else { // estouramos a capacidade do array
      float* new = resize(D);
      if (new == NULL)
         return 0;
      else {
        D->first = ((D->first + D->cap - 1) % D->cap);
        D->data[D->first] = x;
        D->size++;
        return 1;
      }

   }
}

/**
   Remove a float from the beginning of D.

   If the deque has capacity/(factor^2) elements, this function tries to reduce
   the array size to capacity/factor.  If capacity/factor is smaller than the
   minimum capacity, the minimum capacity is used instead.

   If it is not possible to resize, then the array size remains unchanged.

   This function returns the float removed from D.
   If D was empty prior to invocation, it returns 0.0 and D remains unchanged.
**/
float df_eject(dequef* D) {
   float* new;
   int did_fail = 0;

   if (D->size == (D->cap / (D->factor * D->factor))) {
     new = resize(D); // control reaches end of non-void function
     if (!new)
      did_fail = 1;
   }
   
   if (D->size > 0){
    D->first = (D->first + 1) % D->cap;
    if (!did_fail) // did_fail serve para checarmos se devemos decrementar o size do array
       D->size--;
    return D->data[D->first];
   } else
      return 0;
}

/**
   Set D[i] to x.

   If i is not in [0,|D|-1]] then D remains unchanged.
**/
void df_set(dequef* D, long i, float x) {
    if (i == 0 || (i > 0 && i < D->size))
        D->data[(D->first + i) % D->cap] = x;
}

/**
   Return D[i].

   If i is not in [0,|D|-1]] it returns 0.0.
**/
float df_get(dequef* D, long i) {
    if (i == 0 || (i > 0 && i < D->size))
       return D->data[(D->first + i) % D->cap];
    else
        return 0;
}

/**
   Print the elements of D in a line.
**/
void df_print(dequef* D) {
   printf("deque (%ld):", D->size);
   for (long i = 0; i < D->size; i++){
      printf(" %.1f", D->data[(i + D->first) % D->cap]);
   }
   printf(" \n");
}