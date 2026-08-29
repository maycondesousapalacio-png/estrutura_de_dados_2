#include <stdio.h>

int main(){
    struct horario{
        int *p_hora;
        int *p_minuto;
        int *p_segundo;
    };

    struct horario hoje;
     int hora=200;
     int minuto=300;
     int segundo=400;

     hoje.p_hora = &hora;
     hoje.p_minuto = &minuto;
     hoje.p_segundo = &segundo;

     printf("Hora - %i\nMinuto - %d\nSegundo - %d\n", *hoje.p_hora, *hoje.p_minuto, *hoje.p_segundo);

     *hoje.p_segundo = 1000;
     printf("%d", *hoje.p_segundo);

     getchar();
     return 0;
}
