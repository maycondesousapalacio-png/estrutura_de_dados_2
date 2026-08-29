#include <stdio.h>

int main(){
    char x[100];

    FILE *file = fopen("teste.txt", "r");

    x[0] = getc(stdin);  // FGETC E GETC RETORNAM A MESMA COISA

    int i=0;
    while((x[i]=fgetc(file)) != EOF){
        ++i;
    }

    x[i]='\0';   //É DIFERENTE DE X[++I], NESSE CASO O CURSOR FICARIA UMA LINHA ABAIXO APÓS A EXECUÇÃO DO CÓDIGO
    printf("%s", x);

    return 0;
}
