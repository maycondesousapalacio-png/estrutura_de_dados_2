#include <stdio.h>

#define PI 3.14159
#define NULO 0

double areaCirculo(double raio){
    retunr raio * raio * PI;
}

int main(){

    double areaCirculo(double raio);
    double r;
    int i = 3;

    while(i != NULO){
        printf("Digite o raio do circulo: ");
        scanf("%1f", &r);
        printf("A area do circulo e: %1f", areaCirculo(r));
        --i;
    }

    system("pause");
    return 0;
}
