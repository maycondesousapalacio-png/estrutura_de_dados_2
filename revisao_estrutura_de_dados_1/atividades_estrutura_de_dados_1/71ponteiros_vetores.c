#include <stdio.h>

int main(){

    int vetor[3]={1,2,3};
    int *ponteiro = vetor;   // OU PODERIA SER FEITO COM &vetor[0]; ESPECIFICANDO O ÍNDICE DO ELEMENTO.

    printf("%d", ++*ponteiro);


    getchar();
    return 0;
}
