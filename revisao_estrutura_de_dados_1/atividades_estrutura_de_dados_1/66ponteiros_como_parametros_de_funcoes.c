#include <stdio.h>

int main(){
    void testeVarialvel(int x);
    void testePonteiro(int *pX);    // A FUNÇÃO PEDE UM ENDEREÇO DE MEMÓRIA, NÃO O VALOR QUE ESTÁ NO ENDEREÇO

    int teste =1;
    int *p_teste = &teste;

    printf("%i\n", teste);

    testeVariavel(teste);

    printf("%i\n", teste);

    testePonteiro(p_teste);    ////É SEM O ASTERÍSCO

    printf("%i\n", teste);

    getchar();
    return 0;
}

void testeVariavel (int x){   // A VARIÁVEL PASSADA É UMA CÓPIA DA QUE ESTÁ NO ESCOPO GLOBAL, POR ISSO NÃO É ALTERADO
    ++x;
    printf("Variavel da funcao - %i\n", x);     //PRESTA ATENÇÃO NISSO AQUI, A CÓPIA RECEBE O VALOR E VIRA 2, MAS A GLOBAL NÃO
}

void testePonteiro(int *pX){
    ++*pX;
}
