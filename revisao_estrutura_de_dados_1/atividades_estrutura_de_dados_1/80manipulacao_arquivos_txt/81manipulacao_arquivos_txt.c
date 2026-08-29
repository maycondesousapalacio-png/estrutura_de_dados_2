#include <stdio.h>

int main(){

    FILE *file;
    file = fopen("C:\\Users\\Maycon\\Documents\\c_ansi\\80manipulacao_arquivos_txt\\teste.txt", "w");
    fprintf(file, "Hellow World");

    fclose(file);

    return 0;
}
