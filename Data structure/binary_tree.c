#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* r;
    struct node* l;
}node;

typedef struct tree{
    node* root;
}tree;

tree* create(){
    tree* tree = malloc(sizeof(tree));
    tree->root = NULL;
    return tree;
}

void insertRight(node* n, int num);

void insertLeft(node* n, int num){

    if(!n->l){
        node* p = malloc(sizeof(node));
        p->data = num;
        p->l = NULL;
        p->r = NULL;
        n->l = p;
    } else {
        if(num < n->l->data){
            insertLeft(n->l, num);
        } if(num > n->l->data)
            insertRight(n->l, num);
    }

}

void insertRight(node* n, int num){

    if(!n->r){
        node* p = malloc(sizeof(node));
        p->data = num;
        p->l = NULL;
        p->r = NULL;
        n->r = p;
    } else {
        if(num < n->r->data){
            insertLeft(n->r, num);
        } if(num > n->r->data)
            insertRight(n->r, num);
    }

}

void insert(tree* t, int n){

    if(!t->root){
        node* p = malloc(sizeof(node));
        p->data = n;
        p->l = NULL;
        p->r = NULL;
        t->root = p;
    } else {
        node* q = t->root;
        if(t->root->data > n)
            insertLeft(t->root, n);
        if(t->root->data < n)
            insertRight(t->root, n);
    }
}

int size(node* root){
    if (!root)
        return 0;
    else
        return 1 + size(root->l) + size(root->r);
}

void print(node* root){
    if(root){
        print(root->l);
        printf("%d ", root->data);
        print(root->r);
    }
}

int search(node* n, int key){
    if(!n)
        return 0;
    else {
        if(n->data == key)
            return 1;
        else {
            if(n->data > key)
                search(n->l, key);
            else
                search(n->r, key);
        }
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
            return root;
        }
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

int compare(node* root1, node* root2){
    if(!root1 && !root2)
        return 1;
    if(!root1 || !root2)
        return 0;
    if(root1->data != root2->data)
        return 0;
    return(compare(root1->l, root2->l) && compare(root1->r, root2->r));
}

node* max(node* root){
    node* max = root;
    while(max->r)
        max = max->r;
    return max;
}

node* min(node* root){
    node* min = root;
    while(min->l)
        min = min->l;
    return min;
}

int sec_max(node* root){
    if(!root || !root->l && !root->r){
        printf("Erro, não há pelo menos dois valores na árvore.");
        return 0;
    }
    if(root->l && !root->r)
        return max(root->l)->data;
    if(root->r && !root->r->r && !root->r->l)
        return root->data;
    return sec_max(root->r);
}

node* tree_to_list(node* root){
    if(!root)
        return NULL;

    if(root && !root->l && !root->r)
        return root;

    if(root && root->l && !root->l->l){
        node* min = root->l;
        root->l->r = root;
        root->l = NULL;
        return min;
    }

    if(root && !root->l){
        return root;
    }

    if(root && root->l && root->r){
        node* min = root->l;
        node* aux = root->l->r;
        while(aux->r)
            aux = aux->r;
        aux->r = root;
        root->l = NULL;
        return min;
    } 

}

node* tree_to_list_correc(node* root){
    node* head = tree_to_list(root);
    node *aux = head, *prev = NULL; 
    while(aux->l){
        prev = aux;
        aux = aux->l;
    }
    if(prev){
        aux->r = prev;
        prev->l = NULL;
    }
    return aux;
}

int main(){
    tree* tree1 = create();
    tree* tree2 = create();
    insert(tree1, 4);
    insert(tree1, 5);
    //node* head = tree_to_list(tree1->root);
    node* head = tree_to_list_correc(tree1->root);
    //printf("\n%d", sec_max(tree1->root));
    print(head);
}
