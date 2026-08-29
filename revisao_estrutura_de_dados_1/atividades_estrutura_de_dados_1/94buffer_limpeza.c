#include <stdio.h>

int main(){
    void limparBuffer(void);

    char x,y,z;

    x=getchar();
    limparBuffer();
    y=getchar();
    limparBuffer();
    z=getchar();
    limparBuffer();

    putchar(x);
    putchar(y);
    putchar(z);

    return 0;
}

void limparBuffer(void){
    char c;
    while((c=getchar()) != '\n' && c != EOF){}
}
