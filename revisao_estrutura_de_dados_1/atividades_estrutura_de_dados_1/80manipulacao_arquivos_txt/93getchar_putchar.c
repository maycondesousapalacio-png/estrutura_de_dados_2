#include <stdio.h>

int main(){

    char x[10];

    int i=0;
    while((x[i]=getchar()) =! '\n' && i < 8){
        ++i;
    }
    x[++i] = '\0';
    puts(x);

    char y;
    while((x=getchar()) != '\n'){
        putchar(x);
    }

    return 0;
}
