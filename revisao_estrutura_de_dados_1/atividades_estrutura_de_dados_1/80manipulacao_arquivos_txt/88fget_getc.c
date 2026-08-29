#include <stdio.h>

int main(){
    char x[100];

    x[0] = getc(stdin);  // FGETC E GETC RETORNAM A MESMA COISA

    int i=0;
    while((x[i]=fgetc(stdin)) != '\n'){
        ++i;
    }

    x[++i]='\0';   //É DIFERENTE DE X[++I], NESSE CASO O CURSOR FICARIA UMA LINHA ABAIXO APÓS A EXECUÇÃO DO CÓDIGO
    printf("%s", x);

    return 0;
}
