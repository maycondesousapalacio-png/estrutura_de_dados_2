#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main(){
    setlocale(LC_ALL, "Portuguese");

    FILE *file;
    file = fopen("string.txt", "r");

    if(file == NULL){
            printf("Arquivo nao foi encontrado\n");
            getchar();
            return 0;
    }

    char frase[100];

    while(fgets(frase, 100, file) != NULL){
        printf("%s", frase);
    }

    fclose(file);

    printf("\n");
    system("pause");
    return 0;
}
