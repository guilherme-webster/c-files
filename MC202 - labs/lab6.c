#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
Como todos sabem, o Campeonato Brasileiro, a Copa do Brasil, a Copa do Mundo e mesmo os torneios regionais têm muitos times. Não é fácil acompanhar a classificação com tantos times e jogos.

Escreva um programa que recebe o nome do torneio, nomes dos times e jogos disputados e produz a classificação do torneio até o momento.

Um time vence um jogo se marcar mais gols que seu adversário. Quando ambos marcam o mesmo número de gols, é empate. Um time ganha 3 pontos por cada vitória, 1 ponto por cada empate e 0 ponto por cada derrota.

Os times são classificadas de acordo com as seguintes regras (nesta ordem):

Maior número de pontos
Maior número de vitórias
Maior saldo de gols (ou seja, gols marcados menos gols sofridos)
Mais gols marcados
Menos jogos disputados
Ordem lexicográfica
 */

typedef struct Team
{
    char name[31];
    char name_prov[31];
    int score;
    int goals_scr; // gols marcados
    int goals_suf; // gols sofridos
    int games_pl; // jogos disputados
    int vic;
    int def;
    int ties;
    int goal_balance;
}Team;


void results(struct Team teams[], int t, int g)
{
     for (int i = 0; i < g; i++) {
        char nm_team1[31];
        char nm_team2[31];
        int g1, g2;

        scanf("%30[^#]#%d@%d#%30[^\n]", nm_team1, &g1, &g2, nm_team2);
        getchar();
        nm_team1[strlen(nm_team1)] = '\0';
        nm_team2[strlen(nm_team2)] = '\0';

        // Atualizar as estatísticas dos times
        for (int j = 0; j < t; j++) {
            if (strcmp(teams[j].name, nm_team1) == 0) {
                teams[j].goals_scr += g1;
                teams[j].goals_suf += g2;
                teams[j].goal_balance += g1 - g2;
                teams[j].games_pl += 1;
                if (g1 > g2)
                {
                    teams[j].score += 3;
                    teams[j].vic += 1;
                }
                if (g1 == g2)
                {
                    teams[j].score += 1;
                    teams[j].ties += 1;
                }
                if (g1 < g2)
                    teams[j].def += 1;
            } else if (strcmp(teams[j].name, nm_team2) == 0) {
                teams[j].goals_scr += g2;
                teams[j].goals_suf += g1;
                teams[j].goal_balance += g2 - g1;
                teams[j].games_pl += 1;
                if (g2 > g1)
                {
                    teams[j].score += 3;
                    teams[j].vic += 1;
                }
                if (g1 == g2)
                {
                    teams[j].score += 1;
                    teams[j].ties += 1;
                }
                if (g2 < g1)
                    teams[j].def += 1;
            }
        }
    }
}

int compare(const void* a, const void* b)
{
    // Fazemos as comparaçoes do sort na precedencia pedida
    if ( ((Team*)a)->score > ((Team*)b)->score )
            return -1; 
    else if ( ((Team*)a)->score == ((Team*)b)->score )
    {
        if ( ((Team*)a)->vic > ((Team*)b)->vic)
            return -1;
        else if ( ((Team*)a)->vic == ((Team*)b)->vic)
            {
                if ( ((Team*)a)->goal_balance > ((Team*)b)->goal_balance)
                    return -1;
                else if ( ((Team*)a)->goal_balance == ((Team*)b)->goal_balance)
                    {
                        if ( ((Team*)a)->goals_scr > ((Team*)b)->goals_scr)
                            return -1;
                        else if ( ((Team*)a)->goals_scr == ((Team*)b)->goals_scr)
                            {
                                if ( ((Team*)a)->games_pl < ((Team*)b)->games_pl) 
                                    return -1;
                                else if ( ((Team*)a)->games_pl == ((Team*)b)->games_pl)
                                    {
                                        return ( strcmp(((Team*)a)->name_prov, ((Team*)b)->name_prov));
                                    }
                                else
                                    return 1;
                            }
                        else
                            return 1;
                    }
                else
                    return 1;
            }
        else
            return 1;
    }
    else
        return 1;

}

int main(){
    int n;
    char tour_nm[100];

    scanf("%d", &n);
    getchar();
    for(int i = 0; i < n; i++)
    {
        fgets(tour_nm, 100, stdin);
        tour_nm[strlen(tour_nm) - 1] = '\0';

        int t, g, strsz;

        scanf("%d", &t);
        getchar();
        struct Team teams[t]; 
        
        for (int j = 0; j < t; j++)
        {
            fgets(teams[j].name, 31, stdin);
            strsz = strlen(teams[j].name);
            if (strsz == 30)
            {
                teams[j].name[strsz] = '\0';
                getchar();
            }
            else
                teams[j].name[strsz - 1] = '\0';
            for (int o = 0; o <= strsz; o++)
            {
                if(teams[j].name[o] >= 'a' && teams[j].name[o] <= 'z') {
                   teams[j].name_prov[o] = teams[j].name[o] - 32;
                }   else
                     teams[j].name_prov[o] = teams[j].name[o]; // passamos para upper a fim de comparar os nomes no sort
            }
            teams[j].goals_scr = 0;
            teams[j].goals_suf = 0;
            teams[j].score = 0;
            teams[j].games_pl = 0;
            teams[j].vic = 0;
            teams[j].def = 0;
            teams[j].ties = 0;
            teams[j].goal_balance = 0;
        }
        
        scanf("%d", &g); // g <= 1000
        getchar();

        results(teams, t, g);
        qsort(teams, t, sizeof(Team), compare);

        printf("%s\n", tour_nm);
        for (int j = 0; j < t; j++) {
            printf("%d) %s, %dp, %dj (%d-%d-%d), %ds (%d-%d)\n", j + 1, teams[j].name, teams[j].score, teams[j].games_pl, teams[j].vic, teams[j].ties, teams[j].def, teams[j].goal_balance, teams[j].goals_scr, teams[j].goals_suf);
    }
        if (i != n - 1)
            printf("\n");
}
}
