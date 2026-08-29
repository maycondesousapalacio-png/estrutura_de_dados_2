#include <stdio.h>

int main(){
    char x[100];

    printf("Digite: ");
    fgets(x, 100, stdin);   //X = ONDE É ARMZENADO... 100 = 99 CARACTERES + \0... STDIN = ENTRADA DE DADOS PELO TECLADO...
    printf("\n%s", x);

    freopen("teste.txt", "r", stdin);
    fgets(x, 100, stdin);
    printf("%s", x);


    return 0;
}
