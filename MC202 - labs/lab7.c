#include <stdio.h>
#include <stdlib.h>

/*
 Uma empresa de pesquisa geológica assinou um contrato para detecção de depósitos subterrâneos de petróleo.

Ela trabalha com uma grande região retangular de terreno por vez e cria uma grade que divide o terreno em vários lotes quadrados. Em seguida, analisa cada lote separadamente usando equipamentos de detecção para determinar se o lote contém petróleo. Se dois lotes com petróleo forem adjacentes horizontal, vertical ou diagonalmente então eles fazem parte do mesmo depósito.

Escreva um programa para determnar quantos depósitos de petróleo diferentes estão contidos em uma região.
 */

void dfs(int m_r, int m_c, char **grid, int r, int c) { // fazemos uma busca em profundidade para todas as direções possiveis
    int dir[8][2] = {{0, 1}, {1, 0}, {1, 1}, {-1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, -1}}; // direções possiveis
    grid[r][c] = '.'; // marca o ponto atual como visitado

    for (int i = 0; i < 8; i++) {
        int nr = r + dir[i][0];
        int nc = c + dir[i][1];

        if (nr >= 0 && nr < m_r && nc >= 0 && nc < m_c && grid[nr][nc] == '@') { // se pontos adjacentes tiverem petróleo, devemos realizar busca neles
            dfs(m_r, m_c, grid, nr, nc);
        }
    }
}

int countDeposits(int r, int c, char **grid) {
    int count = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (grid[i][j] == '@') { // se temos um começo de região com petróleo, exploramos
                dfs(r, c, grid, i, j);
                count++;
            }
        }
    }
    return count;
}

int main() {
    int n, m = 1;
    while (m != 0) {
        scanf("%d %d ", &n, &m);

        char **grid;

        grid = (char **)malloc(n * sizeof(char *));

        if (grid == NULL) // testamos o retorno da alocação
            exit(1);

        for (int i = 0; i < n; i++) {
            grid[i] = (char *)malloc((m + 1) * sizeof(char)); // m+1 pois temos m caracteres e mais um para \0
            scanf("%s", grid[i]);
            if (grid[i] == NULL) // testamos o retorno da alocação 
                exit(1);
        }

        if (m != 0) // testamos se m é zero para ver se devemos fazer a busca, ou encerrar o programa
        {
            int numDeposits = countDeposits(n, m, grid);
            printf("%d\n", numDeposits);
        }
        for (int i = 0; i < n; i++) { // liberamos a memória
                free(grid[i]);
            }
            free(grid);
    }
    return 0;
}
