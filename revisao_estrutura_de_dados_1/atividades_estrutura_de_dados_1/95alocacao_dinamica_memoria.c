#include <stdio.h>
#include <stdlib.h>   //NECESSÁRIA PARA AS FUNÇÕES DA ALOCAÇÃO DE MEMÓRIA

struct z {
    int a;
    int b;
    int c;
};

int main(){

    struct z estrutura;

    int x;
    double y;
    int vetor[10];

    printf("%li", sizeof(x));
    printf("\n%i", sizeof(vetor));
    printf("\n%i", sizeof(estrutura));

    return 0;
}
