#include <stdio.h>
#include <stdlib.h>

int main(){  //malloc(10* sizeof(int)) outra opção
    int *p = calloc(10, sizeof(int));  //O PRIMEIRO ARGUMENTO É A QUANTIDADE DE ELEMENTOS A SEREM ALOCADOS E POR PADRÃO O VALOR É ZERO
    if(*p == NULL){                    // DIFEERENTE DO MALLOC QUE O VALOR PADRÃO ARMAZENADO É LIXO DA MEMÓRIA
        printf("Memoria insuficiente para o malloc");
    }

    *p = 1000;

    printf("%i", *p);

    free(p);


    return 0;
}
