#ifndef METODOS_ORDENACAO_H_INCLUDED
#define METODOS_ORDENACAO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listar_transacoes.h"

// FUNÇÕES PARA O MÉTODO BUBLLE SORT


void ordenacao_bubble_sort(struct No *lista_transacoes){
    struct No *atual;
    struct No *fim = NULL;
    int houve_troca;

    do{
        atual = lista_transacoes;
        houve_troca = 0;

        while(atual->proximo != fim){
            if(atual->tra.valor > atual->proximo->tra.valor  ||  (atual->tra.dataInt > atual->proximo->tra.dataInt && atual->tra.valor == atual->proximo->tra.valor)){
                struct Transacao gancho = atual->tra;
                atual->tra = atual->proximo->tra;
                atual->proximo->tra = gancho;

                houve_troca=1;
            }
            atual = atual->proximo;
        }
    fim = atual;     //OTIMIZA O CÓDIGO AO NÃO COMPARAR OS ARQUIVOS JÁ ORDENADOS
    } while(houve_troca);
}

void criar_arquivo_ordenado_bubblesort(struct No *lista_transacoes){

    struct No *gancho_escrita = lista_transacoes;
    FILE *arquivoBin_ordenado_bubblesort = fopen("transacoes_ordenadas_bubblesort.dat", "wb");

    if(arquivoBin_ordenado_bubblesort == NULL){
        printf("Erro ao criar o arquivo 'transacoes_ordenadas_bubblesort.dat'");
        return;
    }

        while(gancho_escrita != NULL){
            fwrite(&gancho_escrita->tra, sizeof(gancho_escrita->tra), 1, arquivoBin_ordenado_bubblesort);
            gancho_escrita = gancho_escrita->proximo;
        }
    fclose(arquivoBin_ordenado_bubblesort);
}


// FUNÇÕES PARA O MÉTODO QUICK SORT


struct No *ordenacao_quicksort(struct No *primeiro_registro, struct No *gancho_ultimo_registro){
    struct No *pivo = primeiro_registro;
    struct No *i = pivo;
    struct No *atual = primeiro_registro->proximo;


    while(atual != NULL && atual != gancho_ultimo_registro->proximo){
        if(atual->tra.valor < pivo->tra.valor || (atual->tra.valor == pivo->tra.valor &&
                                                               atual->tra.dataInt < pivo->tra.dataInt)){
            i = i->proximo;
            //TROCA DOS REGISTROS COM AJUDA DE UMA STRUCT AUXILIAR--------------------
            struct Transacao auxiliar;
            auxiliar = atual->tra;
            atual->tra = i->tra;
            i->tra = auxiliar;
//------------------------------------------------------------------------------------
        }
    atual=atual->proximo;
    }

    struct Transacao auxiliar2;
    auxiliar2 = pivo->tra;
    pivo->tra = i->tra;
    i->tra = auxiliar2;

    return i;
}

struct No *ultimo_registro(struct No *lista_transacoes2, int *contador, int *pcontadorVisa, int *pcontadorMaster){
    struct No* gancho_ultimo_registro = lista_transacoes2;    //ESSE BLOCO ENCONTRA O ÚLTIMO REGISTRO DA LISTA ENCADEADA E CONTA QUANTOS REGISTROS EXISTEM
    while(gancho_ultimo_registro->proximo != NULL){
        contador_bandeira(pcontadorVisa, pcontadorMaster, gancho_ultimo_registro);
        (*contador)++;
        gancho_ultimo_registro = gancho_ultimo_registro->proximo;
    }
    contador_bandeira(pcontadorVisa, pcontadorMaster, gancho_ultimo_registro);
    return gancho_ultimo_registro;
}

void contador_bandeira(int *pcontadorVisa, int *pcontadorMaster, struct No *gancho_ultimo_registro){
    if(strcmp(gancho_ultimo_registro->tra.bandeira, "Visa") == 0){
        (*pcontadorVisa)++;
    } else if(strcmp(gancho_ultimo_registro->tra.bandeira, "MasterCard") == 0){
        (*pcontadorMaster)++;
    }
}

void quicksort_iterativo(struct No *lista_transacoes2,struct No *gancho_ultimo_registro, int tamanho_lista, int *pcontadorVisa, int *pcontadorMaster){
//-------------------------------------------------------------------------------------------

    struct No **pilha_inicio =(struct No**) malloc(tamanho_lista*sizeof(struct No*));
    struct No **pilha_fim = (struct No**) malloc(tamanho_lista*sizeof (struct No*));
    int topoPilha = -1;

    if(pilha_inicio == NULL || pilha_fim == NULL){
    printf("Erro de alocacao\n");
    return;
    }

    topoPilha++;
    pilha_inicio[topoPilha] = lista_transacoes2;
    pilha_fim[topoPilha] = gancho_ultimo_registro;

    while(topoPilha >= 0){
        struct No *esquerda = pilha_inicio[topoPilha];
        struct No *direita = pilha_fim[topoPilha];

        topoPilha--;

        struct No *pivo_atual = ordenacao_quicksort(esquerda, direita);

        if(pivo_atual != NULL && esquerda != pivo_atual && esquerda->proximo != pivo_atual){
            struct No *anterior = esquerda;
            while(anterior != NULL && anterior->proximo != pivo_atual){
                anterior = anterior->proximo;
            }
        if(anterior != NULL){
            topoPilha++;
            pilha_inicio[topoPilha] = esquerda;
            pilha_fim[topoPilha] = anterior;
        }
        }

        if(pivo_atual != NULL && pivo_atual->proximo != NULL && pivo_atual != direita){
            topoPilha++;
            pilha_inicio[topoPilha] = pivo_atual->proximo;
            pilha_fim[topoPilha] = direita;
        }
    }
    free(pilha_inicio);
    free(pilha_fim);
}


void criar_arquivo_ordenado_quicksort(struct No *lista_transacoes){

    struct No *gancho_escrita = lista_transacoes;
    FILE *arquivoBin_ordenado_quicksort = fopen("transacoes_ordenadas_quicksort.dat", "wb");

    if(arquivoBin_ordenado_quicksort == NULL){
        printf("Erro ao criar o arquivo 'transacoes_ordenadas_bubblesort.dat'");
        return;
    }

        while(gancho_escrita != NULL){
            fwrite(&gancho_escrita->tra, sizeof(gancho_escrita->tra), 1, arquivoBin_ordenado_quicksort);
            gancho_escrita = gancho_escrita->proximo;
        }
    fclose(arquivoBin_ordenado_quicksort);
}

#endif // METODOS_ORDENACAO_H_INCLUDED
