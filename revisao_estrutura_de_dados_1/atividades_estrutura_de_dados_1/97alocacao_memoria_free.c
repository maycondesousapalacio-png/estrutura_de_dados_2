#include <stdio.h>
#include <stdlib.h>

int main(){
    int *p = malloc(sizeof(int));
    if(*p == NULL){
        printf("Memoria insuficiente para o malloc");
    }

    *p = 1000;

    printf("%i", *p);

    free(p);


    return 0;
}
