#include <stdio.h>
#include <stdlib.h>

typedef struct graph{
    int numnodes;
    int **edges;
}graph;

graph* create_graph(int num){
    graph* g = malloc(sizeof(*g));
    if(!g)
        return NULL;
    g->numnodes = num;
    g->edges = calloc(sizeof(int*), g->numnodes);
    if(!g->edges){
        free(g);
        return NULL;
    }
    for(int i = 0; i < num; i++){
        g->edges[i] = calloc(sizeof(int), g->numnodes);
        if(!g->edges[i]){
            destroy_graph(g);
            return NULL;
        }
    }
    return g;
}

void destroy_graph(graph* g){
    if(!g->edges){
        free(g);
        return;
    }
    for(int i = 0; i < g->numnodes; i++){
        if(g->edges[i])
            free(g->edges[i]);
    }
    free(g->edges);
    free(g);
}

void print_graph(graph *g){
    for(int from = 0; from < g->numnodes; from++){
        for(int to = 0; to < g->numnodes; to++){
            if(g->edges[from][to]){
                printf("%d -> %d\n", from, to);
            }
        }
    }
}

int add_edge(graph* g, unsigned int from_node, unsigned int to_node){

    if(has_edge(g, from_node, to_node))
        return 0;
    
    g->edges[from_node][to_node] = 1;
    return 1;
}

int remove_edge(graph* g, unsigned int from_node, unsigned int to_node){
    if(!g)
        return -1;
    if(from_node >= g->numnodes)
        return -1;
    if(to_node >= g->numnodes)
        return -1;

    if(has_edge(g, from_node, to_node) == 0)
        return 0;
    
    g->edges[from_node][to_node] = 0;
    return 1;
}

int has_edge(graph* g, unsigned int from_node, unsigned int to_node){
    if(!g)
        return -1;
    if(from_node >= g->numnodes)
        return -1;
    if(to_node >= g->numnodes)
        return -1;

    return g->edges[from_node][to_node];
}