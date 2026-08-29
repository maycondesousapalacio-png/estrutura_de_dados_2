#include <stdio.h>

#define NUMERO_MAXIMO_ALUNOS 1000

void umaFuncao(void){
    printf("%i\n", NUMERO_MAXIMO_ALUNOS);
}

void umaOutraFuncao(void){
    printf("%d\n", NUMERO_MAXIMO_ALUNOS);
}

int main(){
    void umaFuncao(void);
    void umaOutraFuncao(void);

    printf("%i\n", NUMERO_MAXIMO_ALUNOS);
    umaFuncao();
    umaOutraFuncao();

    system("pause");
    return 0;

}
