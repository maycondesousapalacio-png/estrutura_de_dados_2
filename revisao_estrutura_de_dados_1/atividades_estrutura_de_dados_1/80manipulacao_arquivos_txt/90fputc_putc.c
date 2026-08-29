#include <stdio.h>
#include <locale.h>

int main(){
    setlocale(LC_ALL, "Portuguese");

    char x[] = "coxinha";
    FILE *file = fopen("teste3.txt", "w");

    putc('a', stdout);   //STDIN PARA ENTRADA DE DADOS E STDOUT PARA SAIDA DE DADOS

    int i=0;
    while(x[i] != '\0'){
        putc(x[i], file);
        i++;
    }


    return 0;
}
