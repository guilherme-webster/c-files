#include <stdio.h>
#include <math.h>

/*Truque para acelarar o acesso em um array*/

void atualiza(int V[], int R[], int a, int x, int r){
    int i = a / r; // achamos onde o indice pedido foi contido no vetor R
    R[i] += x - V[a]; // atualizamos o que deveria ser somado neste indice em R
    V[a] = x; // atualizamos o valor em V
}

int soma(int V[], int R[],int i, int j, int r){
    int sum = 0;
    // somamos os elementos que não estão totalmente contidos nos blocos a serem somados, por estarem "antes" deles no array (no exemplo do site, o S[3] e o S[4])
    while (i < j && i % r != 0 && i != 0){
        sum += V[i];
        i++;
    }
    // somamos os blocos completos e atualizamos os índice de modo a passar para os blocos seguintes
    while (i + r <= j){
        sum += R[i/r];
        i += r;
    }
    // somamos os elementos que não estão totalmente contidos nos blocos a serem somados, por estarem "depois" deles no array (no exemplo do site, o S[20])
    while (i <= j){
        sum += V[i];
        i++;
    }
    return sum;
}

int main(){
    int n_element, w, y, i, j, sum, r;
    char op;
    scanf("%d", &n_element);
    r = ceil(sqrt(n_element));
    int V[n_element], R[r]; // criamos V e R

    for (w = 0; w < n_element; w++){
        scanf("%d ", &V[w]); // atualizamos os valores de V
    }

    for (w = 0; w < r; w++){
        sum = 0;
        for (y = w * r; y <= (w + 1) * r - 1; y++){ // Atualizamos os valores de R
            if (y < n_element){
                sum += V[y]; 
            } else
                break;
        }
        R[w] = sum;
    }

    while(scanf("%c %d %d\n", &op, &i, &j) == 3){ // lemos a operação e os seus respectivos dados

        if (op == 's'){
            printf("%d\n", soma(V, R, i, j, r)); // computamos a soma e printamos
        } else{
            if (op == 'a'){
                atualiza(V, R, i, j, r); // atualizamos ambos os vetores
            }
        }
    }
}
