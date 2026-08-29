#include <stdio.h>

int main(){
    struct horario{
        int hora;
        int minuto;
        int segundo;
    };

    struct horario agora, *depois;
    depois = &agora;

    (*depois).hora=20;
    depois->minuto=80;
    depois->segundo=50;

    int somatorio=100;

    struct horario antes;

    antes.hora = somatorio + depois->segundo;
    antes.minuto = agora.hora + depois->minuto;

    printf("%d:%d:%d\n", agora.hora,agora.minuto,agora.segundo);
    printf("%d:%d:%d\n", antes.hora,antes.minuto,antes.segundo);

    getchar();
    return 0;
}
