#ifndef LISTAR_TRANSACOES_H_INCLUDED
#define LISTAR_TRANSACOES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "transacao.h"

struct No{                                  //ESSE BLOCO POSSUI AS FUNÇÕES RELACIONADAS A LISTA
        struct Transacao tra;
        struct No *proximo;
    };

struct No *inserirTransacao_inicio(struct No *listaTransacoes, struct Transacao t){
        struct No *novaTransacao = (struct No*) malloc(sizeof(struct No));
        if(novaTransacao == NULL){
            printf("Erro na alocação de memória");
            return listaTransacoes;
        }
        novaTransacao->tra = t;
        novaTransacao->proximo = listaTransacoes;

        return novaTransacao;
    }

void inserir_risco(struct No **lista_risco, struct Transacao t) {
        struct No *novo = (struct No*)malloc(sizeof(struct No));
        if (!novo) return;
        novo->tra = t;
        novo->proximo = *lista_risco;
        *lista_risco = novo;
}

//--------------------------------------------------------------------------------------------------

struct FilaPendentes{                      // ESSE BLOCO POSSUI AS FUNÇÕES RELACIONADAS A FILA
        struct No *inicio_fila;
        struct No *final_fila;
    };

void iniciar_fila(struct FilaPendentes *fila){
        fila->inicio_fila = NULL;
        fila->final_fila = NULL;
}


int fila_vazia(struct FilaPendentes *fila){
    return (fila->inicio_fila == NULL);
}

int inserir_fila(struct FilaPendentes *fila, struct Transacao transacao){
        struct No *transacao_pendente = (struct No*) malloc(sizeof(struct No));
        if(transacao_pendente == NULL){
            printf("Falha na alocação de memória...");
            return 0;
        }

        transacao_pendente->tra = transacao;
        transacao_pendente->proximo = NULL;

        if(fila->final_fila == NULL){
            fila->inicio_fila = transacao_pendente;
            fila->final_fila = transacao_pendente;
        } else {
            fila->final_fila->proximo = transacao_pendente;
            fila->final_fila = transacao_pendente;
        }
        return 1;
}

struct No *remover_fila(struct FilaPendentes *fila){
    if(fila_vazia(fila)) return NULL;

    struct No *removido = fila->inicio_fila;
    fila->inicio_fila = fila->inicio_fila->proximo;

    if(fila->inicio_fila == NULL){
        fila->final_fila = NULL;
    }
    return removido;
};

//------------------------------------------------------------------
                                //ESSE BLOCO POSSUI AS FUNÇÕES RELACIONADAS A PILHA

struct PilhaAuditoria {
    struct No *topo;
};

void inicializar_pilha(struct PilhaAuditoria *pilha) {
    pilha->topo = NULL;
}

int pilha_vazia(struct PilhaAuditoria *pilha) {
    return (pilha->topo == NULL);
}

void empilhar_rejeitada(struct PilhaAuditoria *pilha, struct Transacao t) {
    struct No *novo = (struct No*) malloc(sizeof(struct No));
    if (novo == NULL) {
        printf("Erro de alocação na pilha de auditoria.\n");
        return;
    }
    novo->tra = t;
    novo->proximo = pilha->topo;
    pilha->topo = novo;
    printf("Transação rejeitada empilhada (ID: %lu)\n", t.id);
}

struct Transacao desempilhar_rejeitada(struct PilhaAuditoria *pilha) {
    struct Transacao vazia = {0};
    if (pilha_vazia(pilha)) {
        printf("Pilha de auditoria vazia. Nada para desfazer.\n");
        return vazia;
    }
    struct No *removido = pilha->topo;
    struct Transacao t = removido->tra;
    pilha->topo = removido->proximo;
    free(removido);
    return t;
}

void undo(struct PilhaAuditoria *pilha) {
    struct Transacao t = desempilhar_rejeitada(pilha);
    if (t.id != 0) {
        printf("\n--- TRANSAÇÃO REJEITADA REMOVIDA PARA REVISÃO ---\n");
        printf("ID: %lu\n", t.id);
        printf("Data: %s\n", t.data);
        printf("Hora: %s\n", t.hora);
        printf("Bandeira: %s\n", t.bandeira);
        printf("Valor: R$ %.2f\n", t.valor);
        printf("Status: %d\n", t.status);
    }
}

//---------------------------------------------------------------------------
                    //VERIFICAÇÕES DE REGISTROS INVÁLIDOS

int hora_para_int(const char *hora_str) {
    return atoi(hora_str);   // converte "13" -> 13
}

int eh_transacao_risco(struct Transacao *t, float valor_limite) {
    int hora = hora_para_int(t->hora);
    int cond_hora = (hora >= 23 || hora <= 5);   // entre 23h e 5h
    return (t->valor > valor_limite && cond_hora);
}

#endif // LISTAR_TRANSACOES_H_INCLUDED
