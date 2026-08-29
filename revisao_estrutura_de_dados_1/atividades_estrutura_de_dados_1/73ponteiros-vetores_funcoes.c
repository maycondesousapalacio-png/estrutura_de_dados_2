#include <stdio.h>

int somarVetor(int vetor[], const int n){
    int soma=0;
    int *ponteiro = vetor;
    int *const finalVetor = vetor + n;

    for(ponteiro; ponteiro < finalVetor; ++ponteiro){
        soma+= *ponteiro;
    }
    return soma;
}

int main(){

    int somarVetor(int vetor[], const int n);
    int vetor[10] = {5,5,5,5,5,5,5,5,5,5};

    printf("A soma dos membros do vetor e %i", somarVetor(vetor, 10));

    getchar();
    return 0;
}
