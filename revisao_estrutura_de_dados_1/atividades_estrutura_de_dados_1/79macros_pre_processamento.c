#include <stdio.h>

#define MAIOR(x, y) x > y ? x : y
#define E_MINUSCULO(char) char >= 'a' && char <= 'z'

int main(){

    char x = 'A';

    if(E_MINUSCULO(x)){
        printf("E uma letra minuscula...\n");
    }else {
        printf("Nao e uma letra minuscula...\n");
    }

    printf("%i\n", MAIOR(10, 50));

    system("pause");
    return 0;
}
