#include <stdio.h>

int main(){
    char x[100];

    FILE *file = fopen("teste.txt", "r");
    fgets(x, 100, file);
    printf("%s\n", x);

    freopen("teste2.txt", "r", file);
    fgets(x, 100, file);
    printf("%s", x);


    return 0;
}
