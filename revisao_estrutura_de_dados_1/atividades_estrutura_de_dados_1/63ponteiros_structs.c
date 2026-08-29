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
    depois->minuto=20;
    depois->segundo=59;

    printf("%d:%d:%d", agora.hora,agora.minuto,agora.segundo);

    getchar();
    return 0;
}
