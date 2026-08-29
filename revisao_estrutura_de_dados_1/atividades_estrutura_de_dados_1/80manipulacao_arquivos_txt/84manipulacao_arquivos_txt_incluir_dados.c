#include <stdio.h>
#include <stdlib.h>

int main(){

    FILE *file;
    file = fopen("string.txt", "a");

    if(file == NULL){
        printf("Arquivo nao pode ser encontrado...\n");
        getchar();
        exit(1);
    }

    fprintf(file, "\nPrimeira frase\n");

    char frase[]= "Segunda frase\n";
    fputs(frase, file);

    char caractere = '3';
    fputc(caractere, file);

    fclose(file);

    system("pause");
    return 0;
}
