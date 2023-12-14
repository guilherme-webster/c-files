#include <stdio.h>
#include <stdlib.h>

// hash table implemented with an array of linked lists

// 2 * 15 = 30 -> 31 (15 is the number of data inserted)
#define SZ 31

typedef struct node{

    int key;
    struct node* next;

}node;

typedef struct list
{
    node* head;
    int sz;

}list;

void initializeList(list* l){
    l->head = NULL;
    l->sz = 0;
}

void insertList(list* l, int value){
    node* new = malloc(sizeof(node));
    if(!new)
        printf("Error allocating memory!");
    else{
        new->key = value;
        new->next = l->head;
        l->head = new;
        l->sz++;
    }
}

int listSearch(list* l, int data){
    node* aux = l->head;
    while(aux && aux->key != data)
        aux = aux->next;
    if(aux){
        return aux->key;
    } else
        return 0; // suppose 0 won't be an element of the table/list
}

void printList(list* l){
    node* aux = l->head;
    printf("SZ: %d: ", l->sz);
    while(aux){
        printf("%d ", aux->key);
        aux = aux->next;
    }
}

void initializeTable(list t[]){
    int i;

    for(i = 0; i < SZ; i++){
        initializeList(&t[i]); // suppose zero won't be a value
    }
}

int hash(int k){
    return k % SZ;
}

void insert(list t[], int value){
    int id = hash(value);
    insertList(&t[id], value);
}

int search(list t[], int key){
    int id = hash(key);
    return listSearch(&t[id], key);
}

void print(list t[]){
    int i;
    for(i = 0; i < SZ; i++){
        printf("%2d = ", i);
       printList(&t[i]);
       printf("\n");
    }
}

int main(){
    list table[SZ];
    initializeTable(table);

    insert(table, 4);
    insert(table, 5);
    insert(table, 6);
    print(table);
}