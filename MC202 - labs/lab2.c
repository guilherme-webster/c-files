#include <stdio.h>
#include <math.h>

/*Enunciado: Em um grande campo viviam coelhos e raposas. Raposas querem jantar coelhos, enquanto coelhos querer fugir das raposas por um dos muitos buracos do campo.

Quando um coelho que está pastando alegremente vê uma raposa ele escolhe um buraco e segue em direção a ele em linha reta e com velocidade constante. A raposa, que é muito boa em leitura de linguagem corporal, segue imediatamente em direção ao mesmo buraco escolhido pelo coelho, em linha reta e a uma velocidade constante igual ao dobro da velocidade do coelho. Se a raposa alcança o buraco primeiro, ela devora o coelho, senão, o coelho escapa. Seu programa deve determinar se há um buraco pelo qual o coelho possa escapar.*/


#define v_coelho 1
#define v_raposa 2

int main(){
    int i,buracos;
    double xc, yc, xr, yr;
    scanf("%d %lf %lf %lf %lf", &buracos, &xc, &yc, &xr, &yr); // lemos o num de buracos e as posicoes do coelho e da raposa
    for (i=0 ; i < buracos; i++){
        double xb, yb, tc, tr;
        scanf("%lf %lf", &xb, &yb); // lemos as coord. do respectivo buraco
        tc = sqrt((xc - xb) * (xc - xb) + (yc - yb) * (yc - yb)) / v_coelho; // fazemos a conta tempo = distancia / velocidade para o coelho e para a raposa
        tr = sqrt((xr - xb) * (xr - xb) + (yr - yb) * (yr - yb)) / v_raposa;
        if (tc < tr){
            printf("O coelho pode escapar pelo buraco (%.3lf,%.3lf).\n", xb, yb); // se o coelho levar menos tempo, ele escapa
            return 0;
        }
    }
    printf("O coelho nao pode escapar.\n"); // se a raposa levar menos tempo, ela pega o coelho
    return 0;
}
