#include <stdio.h>
#include <stdlib.h>

int main() {
    int *vetor = malloc(5 * sizeof(int));
    if (vetor == NULL) return 1;

    int i;
    for (i = 0; i < 5; i++) vetor[i] = i;

    // Redimensiona para 10 inteiros
    int *temp = realloc(vetor, 10 * sizeof(int));
    if (temp == NULL) {
        // Falha: vetor original ainda está alocado
        free(vetor);
        return 1;
    }
    vetor = temp;  // atualiza ponteiro

    // Agora vetor tem espaço para 10 inteiros
    // Os primeiros 5 valores permanecem 0,1,2,3,4
    for (i = 5; i < 10; i++) vetor[i] = i;

    free(vetor);
    return 0;
}
