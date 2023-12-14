#include <stdio.h>
#include <stdlib.h>

/*
 Uma empresa está projetando uma nova rede de fibras ópticas entre seus pontos-de-venda (PDVs). A comunicação entre dois PDVs conectados por uma fibra óptica é bidirecional. Um pacote de dados pode ser transmitido entre quaisquer PDVs na rede, mas a conexão não precisa ser direta, o pacote de dados pode passar por outros PDVs.

Quando falta energia elétrica em um PDV, aquele PDV fica incomunicável. Também pode ser o caso que quando um PDV X deixa de funcionar, outros PDVs ficam sem comunicação entre si. Quando isso acontece, X é chamado de "PDV crítico".

Escreva um programa para determinar quantos PDVs críticos há na rede que foi projetada.

Entrada
A entrada é formada por blocos de linhas. Cada bloco descreve uma rede. A primeira linha de cada bloco tem o número de PDVs, n. Em seguida há no máximo n linhas que descrevem a rede. Os PDVs na rede estão numerados entre 1 e n. Cada linha começa com o númeo de um PDV seguido por outros números de PDVs, indicando que o primeiro tem uma conexão direta com cada um dos demais. Cada bloco termina com uma linha que contém apenas um zero.
O último bloco tem apenas uma linha indicando n=0.

Saída
Para cada bloco exceto o último seu programa deve imprimir o número de PDVs críticos, em uma linha.
 */

typedef struct graph {
    int numnodes;
    int **edges;
    int *degrees;  // Array para armazenar os graus dos vértices
} graph;

void destroy_graph(graph* g);
int has_edge(graph* g, int from_node, int to_node);

graph* create_graph(int num) {
    graph* g = malloc(sizeof(*g));
    if (!g)
        return NULL;

    g->numnodes = num;

    g->degrees = calloc(sizeof(int), g->numnodes);
    if (!g->degrees) {
        free(g);
        return NULL;
    }

    g->edges = calloc(sizeof(int*), g->numnodes);
    if (!g->edges) {
        free(g->degrees);
        free(g);
        return NULL;
    }

    for (int i = 0; i < num; i++) {
        g->edges[i] = calloc(sizeof(int), g->numnodes);
        if (!g->edges[i]) {
            destroy_graph(g);
            return NULL;
        }
    }

    return g;
}

void destroy_graph(graph* g) {
    if (!g->edges) {
        free(g->degrees);
        free(g);
        return;
    }

    for (int i = 0; i < g->numnodes; i++) {
        if (g->edges[i])
            free(g->edges[i]);
    }

    free(g->edges);
    free(g->degrees);
    free(g);
}

void print_graph(graph* g) {
    for (int from = 0; from < g->numnodes; from++) {
        for (int to = 0; to < g->numnodes; to++) {
            if (g->edges[from][to]) {
                printf("%d -> %d\n", from, to);
            }
        }
    }
}

int add_edge(graph* g, int from_node, int to_node) {
    if (has_edge(g, from_node, to_node) || has_edge(g, to_node, from_node))
        return 0;

    g->edges[from_node][to_node] = 1;
    g->edges[to_node][from_node] = 1;

    g->degrees[from_node]++;
    g->degrees[to_node]++;

    return 1;
}

int remove_edge(graph* g, int from_node, int to_node) {
    if (!g)
        return -1;
    if (from_node > g->numnodes || to_node > g->numnodes)
        return -1;

    if (has_edge(g, from_node, to_node) == 0)
        return 0;

    g->edges[from_node][to_node] = 0;
    g->edges[to_node][from_node] = 0;

    g->degrees[from_node]--;
    g->degrees[to_node]--;

    return 1;
}

int has_edge(graph* g, int from_node, int to_node) {
    if (!g)
        return -1;
    if (from_node > g->numnodes || to_node > g->numnodes)
        return -1;

    return g->edges[from_node][to_node];
}

void bfs(graph* g, int start_node, int* visited) {
    // cria a fila
    int* queue = malloc(sizeof(int) * g->numnodes);
    if (!queue) {
        return;
    }

    int front = 0;
    int rear = 0;

    visited[start_node] = 1;
    queue[rear++] = start_node;
    //
    while (front < rear) {
        int current_node = queue[front++]; // dequeue
        
        for (int i = 0; i < g->numnodes; i++) {
            if (g->edges[current_node][i] && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i; // enqueue
            }
        }
    }

    free(queue);
}

int is_critical_pdv(graph* g, int pdv, int *visited) {

    if (pdv < 0 || pdv > g->numnodes) {
        return 0;
    }

    int* removed = (int *)calloc((g->numnodes + 1), sizeof(int));
    visited[pdv] = 1;
    for (int i = 0; i < g->numnodes; i++) {
        if (i != pdv && !visited[i]) {

            if(remove_edge(g, pdv, i))
               removed[i] = 1;
            if(remove_edge(g, i, pdv))
                removed[i] = 1;

        }
    }

    // Realizar BFS com o PDV removido 
    if(pdv != g->numnodes - 1)
        bfs(g, pdv + 1, visited); // Realizar BFS a partir do vértice seguinte (na matriz) ao removido, se ele não for o último.
    else
        bfs(g, 0, visited); // Se o pdv for o último, realizar BFS a partir do primeiro PDV (da matriz)

    // Verificar se algum nó não foi alcançado após a remoção do PDV
    for (int j = 0; j < g->numnodes; j++) {
        if(!visited[j]){
          for(int i = 0; i < g->numnodes; i++)
          {
            if(removed[i] == 1)
                add_edge(g, pdv, i);
          } 
            return 1;  // PDV é crítico
        }
    }
    
    for(int i = 0; i < g->numnodes; i++)
        {
          if(removed[i] == 1)
            add_edge(g, pdv, i);
        }

    return 0;  // PDV não é crítico
}

int find_critical_pdvs(graph* g) {
    int count = 0;
    for (int i = 0; i < g->numnodes; i++) {
        int *visited = (int *)calloc((g->numnodes + 1), sizeof(int));

        if (is_critical_pdv(g, i, visited) > 0) {
            count++;
        }

        free(visited);
    }
    return count;
}

int main() {
    int n;
    while (1) {
        scanf("%d", &n);
        if (n == 0) {
            break;
        }

        graph* g = create_graph(n);
        int pdv, connected = -1;
        while(1){
            scanf("%d", &pdv);

            if (pdv == 0) {
                break;
            }
            while (1) {
                scanf("%d", &connected);
                if (connected == 0) {
                    break;
                }
                 add_edge(g, pdv - 1, connected - 1);
                if(getchar() == '\n')
                    break;
            }
        }
        int critical_pdvs = find_critical_pdvs(g);
        printf("%d\n", critical_pdvs);

        destroy_graph(g);
    }

    return 0;
}
