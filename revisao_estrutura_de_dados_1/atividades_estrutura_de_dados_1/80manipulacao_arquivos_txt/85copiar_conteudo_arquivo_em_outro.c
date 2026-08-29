#include <stdio.h>
#include <stdlib.h>

int main(){

    void copiarConteudo(FILE *file1, FILE *file2);

    FILE *file1 = fopen("string.txt", "r");
    if(file1 == NULL){
        printf("Arquivo nao foi encontrado");
        return 1;
    }

    FILE *file2 = fopen("copia_string.txt", "w");
    copiarConteudo(file1, file2);

    fclose(file1);
    fclose(file2);

    return 0;
}

void copiarConteudo(FILE *file1, FILE *file2){
    char leitor [1000];
    while (fgets(leitor, 1000, file1) != NULL){
        fputs(leitor, file2);
    }

}
