#ifndef LIBERAR_MEMORIA_H_INCLUDED
#define LIBERAR_MEMORIA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

void liberar_fila(struct FilaPendentes *fila){
    struct No *atual = fila->inicio_fila;
    while(atual != NULL){
        struct No *prox = atual->proximo;
        free(atual);
        atual = prox;
    }
    fila->inicio_fila = NULL;
    fila->final_fila = NULL;
}

void liberar_lista(struct No *cabeca){
    struct No *atual = cabeca;
    while(atual != NULL){
        struct No *prox = atual->proximo;
        free(atual);
        atual = prox;
    }
}

#endif // LIBERAR_MEMORIA_H_INCLUDED
