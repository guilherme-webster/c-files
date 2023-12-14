#include <stdio.h>

/*Enunciado:
 Suponha que um novo sistema de calendários seja instituído em que a data muda a cada 12 horas de sol, independentemente do quanto demore.

Entrada
A entrada tem uma seqüência de linhas com data, horário do nascer do sol e horário do por do sol cada. As datas são consecutivas. Um horário igual a 99:99:99 indica que o sol não nasceu ou não se pôs.
Saída
A saída deve ter uma única linha, indicando que dia seria se o novo calendário entrasse em vigor no primeiro dia da entrada e todos os demais dias tivessem transcorrido.*/

int time_to_sec(int a, int b, int c){
    return (a*3600 + b*60 + c);
}

int is_leap_year(int year){
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

int get_days_in_month(int year, int month){
   int days_in_month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && is_leap_year(year)){
        return 29;
    }
    return days_in_month[month];
}

void determine_final_date(int year,int month,int day,int days_passed, int FD[100]){
    int days_in_current_month;

    while (days_passed > 0){
        days_in_current_month = get_days_in_month(year, month);
        if (days_passed >= days_in_current_month - day + 1){ // checamos os dias que passaram o fim do mês atual
            days_passed -= days_in_current_month - day + 1;
            month += 1; // atualizamos o mês atual
            if (month > 12){ // chechamos se passamos do ano atual
                month = 1;
                year += 1; // atualizamos o ano atual
            } day = 1;
        } else{
            day += days_passed; // se tivermos nos mantido no mesmo mês, basta somar os dias passados ao inicial
            days_passed = 0;
        }
    }
    FD[0] = day;
    FD[1] = month;
    FD[2] = year;
}


int main(){
    int day, month, year, hr1, min1, sec1, hr2, min2, sec2, days_passed;
    int first_day = 0, first_month = 0, first_year = 0;
    int sun_rise, sun_set, time_rs = 0, time_set = 0, is_sun_risen = 777;
    int final_date[100];
    double time_passed = 0;
    
        while(scanf("%d/%d/%d %d:%d:%d %d:%d:%d", &day, &month, &year, &hr1, &min1, &sec1, &hr2, &min2, &sec2) == 9){

            if (first_day == 0){
                first_day = day; // guarda o primeiro dia
                first_month = month; // guarda o primero mês
                first_year = year; // guarda o primeiro ano
            }

            if (hr1 != 99 && min1 != 99 && sec1 != 99){ 
                sun_rise = 1;
                time_rs = time_to_sec(hr1, min1, sec1);
                is_sun_risen = 1;
            } else {
                sun_rise = 0;
            }

            if (hr2 != 99 && min2 != 99 && sec2 != 99){
                sun_set = 1;
                time_set = time_to_sec(hr2, min2, sec2);
                is_sun_risen = 0;
            } else {
                sun_set = 0;
            }
        
            if (time_rs < time_set && sun_rise && sun_set){ // sol nasce e se pôe no mesmo dia
                time_passed += time_set - time_rs;
                is_sun_risen = 0; }
            if (time_set < time_rs && sun_rise && sun_set){ // sol nasce e se pôe so no dia seguinte
                time_passed += 24 * 3600 - time_rs + time_set;
                is_sun_risen = 0;}

            /*queremos o ultimo dia de sun_set, subtraído do ultimo dia de sun_rise, multiplicado por 24, depois checar se o horario do set é maior que o do rise
            se for o caso, somamos a diferença ao número multiplicado por 24, se não, subtraímos. (comentario para os dois if's acima)*/

            if (sun_rise == 0 && sun_set == 0){ // sol nao nasce e nao se poe (ou temos 24hrs de sol ou zero horas)
                if (is_sun_risen == 1){
                    time_passed += 24 * 3600; // se o sol estiver exposto, 24 hrs de sol
                } else {
                    if (is_sun_risen == 0){
                    time_passed += 0; // se não, 0 hrs de sol
                    }}
            }

            if (sun_rise != 0 && sun_set == 0){ // sol nasce no dia mas nao se poe
                time_passed += 24 * 3600 - time_rs;
                is_sun_risen = 1;}

            if (sun_rise == 0 && sun_set != 0){ //sol nao nasce mas se poe
                time_passed += 24 * 3600 + time_set;
                is_sun_risen = 0;}
            
        // fecha o if maior
    } // fecha o while

    days_passed = (int)(time_passed / (3600 * 12)); // passamos o tempo passado para dias, no novo calendario
    determine_final_date(first_year, first_month, first_day, days_passed, final_date);

    printf("%d/%d/%d\n", final_date[0], final_date[1], final_date[2]);
    return 0;
}
