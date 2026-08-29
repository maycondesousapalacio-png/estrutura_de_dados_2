#include <stdio.h>

int main(){

    char x[10];
    char y[10];

    gets(x); // NÃO USE ESSA FUNÇÃO, ELA NEM EXISTE NO C11 POR CAUSA DO BUG DA MEMÓRIA ENTÃO NÃO UTILIZE

    printf("%s", x);


    return 0;
}
