#include <stdio.h>

int main(){

    int vetor[3]={1,2,3};
    int *ponteiro = vetor;   // OU PODERIA SER FEITO COM &vetor[0]; ESPECIFICANDO O ÍNDICE DO ELEMENTO.

    *(ponteiro +1) = 10;   // ENTRE PARÊNTESES ESTÁ O ENDEREÇO DE MEMÓRIA, FORA DELE O VALOR ARMAZENADO NELE.

    printf("%i", vetor[1]);


    getchar();
    return 0;
}
