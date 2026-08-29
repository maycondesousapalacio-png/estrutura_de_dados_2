#include <stdio.h>
#include <stdlib.h>

int main(){

    int *p = (int *) malloc(sizeof(int));

    if(*p == NULL){
        printf("Malloc nao funcionou por falta de memoria disponivel no computador...");

    }
    return 0;
}
