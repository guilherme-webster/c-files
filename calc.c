#include <stdio.h>

int main() {
    int num_operacoes;
    int i;
    float operando1, operando2;
    float resultado;
    char operador;

    printf("Qual o número de operações? ");
    scanf("%d", &num_operacoes);
    
    for (i = 0; i < num_operacoes; i++) {

        scanf("%f %c %f", &operando1, &operador, &operando2);

        if (operador == '/') {
            resultado = operando1 / operando2;
            printf("%f\n", resultado);
        } else if (operador == '+') {
            resultado = operando1 + operando2;
            printf("%f\n", resultado);
        } else if (operador == '-') {
            resultado = operando1 - operando2;
            printf("%f\n", resultado);
        } else if (operador == '*') {
            resultado = operando1 * operando2;
            printf("%f\n", resultado);
        } else {
            printf("Erro, comando não encontrado.");
        }
}
}
