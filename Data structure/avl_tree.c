#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* r;
    struct node* l;
    int height;
}node;

typedef struct tree{
    node* root;
}tree;

node* createNode(int x){
    node* new = malloc(sizeof(node));

    if(new){
        new->data = x;
        new->l = NULL;
        new->r = NULL;
        new->height = 0;
    } else
        printf("\nError alocating new node");
    return new;
}

int greater(int a, int b){ // compara alturas de arvores
    return (a>b) ? a : b;
}

int nodeHeight(node* node){
    if(!node)
        return -1;
    else
        return node->height;
}

int balanceFactor(node* node){
    if(node)
        return(nodeHeight(node->l) - nodeHeight(node->r));
    else
        return 0;
}

tree* create(){
    tree* tree = malloc(sizeof(tree));
    tree->root = NULL;
    return tree;
}

node* rotateLeft(node* root){
    node *y, *f;

    y = root->r;
    f = y->l;

    y->l = root;
    root->r = f;

    root->height = greater(nodeHeight(root->r), nodeHeight(root->l)) + 1;
    y->height = greater(nodeHeight(y->r), nodeHeight(y->l)) + 1;

    return y;
}

node* rotateRight(node* root){
    node *y, *f;

    y = root->l;
    f = y->r;

    y->r = root;
    root->l = f;

    root->height = greater(nodeHeight(root->r), nodeHeight(root->l)) + 1;
    y->height = greater(nodeHeight(y->r), nodeHeight(y->l)) + 1;

    return y;
}

node* rotateRightLeft(node* root){
    root->r = rotateRight(root->r);
    return rotateLeft(root);
}

node* rotateLeftRight(node* root){
    root->l = rotateLeft(root->l);
    return rotateRight(root);
}

node* balanceTree(node* root){
    int bf = balanceFactor(root);

    if(bf < -1 && balanceFactor(root->r) <= 0)
        root = rotateLeft(root);

    else if(bf > 1 && balanceFactor(root->l) >= 0)
        root = rotateRight(root);

    else if(bf < -1 && balanceFactor(root->r) > 0)
        root = rotateRightLeft(root);

    else if(bf > 1 && balanceFactor(root->l) < 0)
        root = rotateLeftRight(root);

    return root;
}


node* insert(node* root, int n){

    if(!root){
        return(createNode(n));
    } else {
        if(root->data > n)
            root->l = insert(root->l, n);
        else if(root->data < n)
            root->r = insert(root->r, n);
    }

    root->height = greater(nodeHeight(root->l), nodeHeight(root->r)) + 1;

    root = balanceTree(root);

    return root;
}

int size(node* root){
    if (!root)
        return 0;
    else
        return 1 + size(root->l) + size(root->r);
}

void print(node* root, int level){
    int i;
    if(root){
        print(root->r, level + 1);
        printf("\n\n");

        for(i = 0; i < level; i++)
            printf("\t");

        printf("%d", root->data);
        print(root->l, level + 1);
    }
}

int search(node* n, int key){
    if(!n)
        return 0;
    else
        if(n->data == key)
            return 1;
        else {
            if(n->data > key)
                search(n->l, key);
            else
                search(n->r, key);
        }
}

node* removeNode(node* root, int key){

    if(root == NULL) {
        return NULL;
    }else{
        if(root->data == key){
            // remove folha (no sem filho)
            if(root->r == NULL && root->l == NULL){
                free(root);
                return NULL;
            } else{
                // remove nos com dois filhos
                if(root->l && root->r){
                    node *aux = root->l;
                    while(aux->r)
                        aux = aux->r;
                    root->data = aux->data;
                    aux->data = key;
                    root->l = removeNode(root->l, key);
                    return root;
                } else{
                //remove nos que tem apenas um filho.
                    node* aux;
                    if(root->l && !root->r)
                        aux = root->l;
                    else if(root->r && !root->l)
                        aux = root->r;
                    free(root);
                    return aux;
                }
            }

        }else{
            if(root->data > key)
                root->l = removeNode(root->l, key);
            else
                root->r = removeNode(root->r, key);
        }

        root->height = greater(nodeHeight(root->l), nodeHeight(root->r)) + 1;

        root  = balanceTree(root);
        
        return root;
    }
}

int height(node* root){
    if(!root)
        return -1;
    else{
        int lef = height(root->l);
        int rig = height(root->r);
        if(lef > rig)
            return lef + 1;
        else
            return rig + 1;
    }
}

int main(){
    tree* tree = create();
    tree->root = insert(tree->root, 25);
    tree->root = insert(tree->root, 26);
    tree->root = insert(tree->root, 8);
    tree->root = insert(tree->root, 71);
    tree->root = insert(tree->root, 32);
    tree->root = insert(tree->root, 55);
    tree->root = insert(tree->root, 48);
    tree->root = insert(tree->root, 36);
    tree->root = insert(tree->root, 80);
    tree->root = insert(tree->root, 11);
    tree->root = insert(tree->root, 96);
    tree->root = insert(tree->root, 21);
    tree->root = insert(tree->root, 93);
    print(tree->root, 1);
    printf("\n%d", height(tree->root));
}