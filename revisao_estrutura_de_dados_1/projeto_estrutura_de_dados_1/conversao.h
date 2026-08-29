#ifndef CONVERSAO_H_INCLUDED
#define CONVERSAO_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "transacao.h"
#include "listar_transacoes.h"

void conversaoBinario(int *linhas, const char *arquivo_novo, int limite,
                      struct PilhaAuditoria *pilha_rejeitadas,
                      struct No **lista_risco,
                      float valor_limite_risco,
                      double *total_visa, double *total_master,
                      unsigned long *maior_id, float *maior_valor) {
    FILE *arquivoCsv = fopen("CreditCardData.csv", "r");
    FILE *arquivoBin = fopen(arquivo_novo, "wb");

    if (arquivoCsv == NULL) {
        printf("Arquivo 'CreditCardData.csv' não encontrado...\n");
        return;
    }
    if (arquivoBin == NULL) {
        printf("Arquivo 'transacoes.dat' não encontrado...\n");
        return;
    }


    int primeira_linha=1;
    int registros_gravados=0;
    char frase[1024];
    int falhas = 0;

    while (fgets(frase, 1024, arquivoCsv) != NULL && registros_gravados<limite) {
        if(primeira_linha){
            primeira_linha=0;
            continue;
        }

        struct Transacao transacao;
        struct Registro registro;

        int extraido = sscanf(frase, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];R$ %f;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%i",
                              registro.id,
                              registro.data,
                              registro.dia,
                              registro.hora,
                              registro.bandeira,
                              registro.modoEntrada,
                              &registro.valor,
                              registro.tipoTransacao,
                              registro.categoria,
                              registro.paisTransacao,
                              registro.paisEntrega,
                              registro.paisResidencia,
                              registro.genero,
                              registro.idade,
                              registro.banco,
                              &registro.status);

//-----------------------------------------------------------------------------------------------------

        int k = 1; int j = 0;
        char casting[8];
        while (k < 9) {
            if (k == 5) {
                ++k;
                continue;
            }
                                                //CONVERSÃO DO ID PARA UNSIGNED LONG
            casting[j] = registro.id[k];
            ++k;
            ++j;
        }

        casting[j] = '\0';
        transacao.id = strtoul(casting, NULL, 10);

//--------------------------------------------------------------------------------------------------------
        k=0, j=0;
        char castingData[3];
        while(k<2){
            castingData[j] = registro.data[k];          //CONVERSÃO DA DATA PARA INT
            ++k;
            ++j;
        }
        castingData[j] = '\0';
        transacao.dataInt = strtoul(castingData, NULL, 10);

//---------------------------------------------------------------------------------------------------------

        strcpy(transacao.data, registro.data);
        strcpy(transacao.hora, registro.hora);
        strcpy(transacao.bandeira, registro.bandeira);
        strcpy(transacao.categoria, registro.categoria);

        transacao.valor = registro.valor;
        transacao.status = registro.status;

        if (extraido == 16) {

            float limitevalorr = 8500.0f;
            if (transacao.valor > limitevalorr) {
                empilhar_rejeitada(pilha_rejeitadas, transacao);
                continue;
            }


            if (eh_transacao_risco(&transacao, valor_limite_risco)) {
                inserir_risco(lista_risco, transacao);
            }

            if (strcmp(transacao.bandeira, "Visa") == 0) {
                *total_visa += transacao.valor;
            } else if (strcmp(transacao.bandeira, "MasterCard") == 0) {
                *total_master += transacao.valor;
            }

            if (transacao.valor > *maior_valor) {
                *maior_valor = transacao.valor;
                *maior_id = transacao.id;
            }

            fwrite(&transacao, sizeof(transacao), 1, arquivoBin);
            registros_gravados++;
        } else {
            struct Transacao rejeitada = {0};
            if (registro.id[0] == '#') {
                rejeitada.id = strtoul(registro.id + 1, NULL, 10);
            }

            strcpy(rejeitada.data, registro.data);
            strcpy(rejeitada.hora, registro.hora);
            strcpy(rejeitada.bandeira, registro.bandeira);
            rejeitada.valor = registro.valor;
            rejeitada.status = -1;  // indica rejeição por parse
            empilhar_rejeitada(pilha_rejeitadas, rejeitada);
            falhas++;
        }
    }

    *linhas = registros_gravados;

    printf("\n--- RELATÓRIO DA CONVERSÃO ---\n");
    printf("Registros gravados com sucesso: %d\n", registros_gravados);
    printf("Linhas ignoradas: %d\n", falhas);
    printf("Total de linhas lidas do CSV (incluindo cabeçalho): %d\n",
           (primeira_linha ? 0 : registros_gravados + falhas + 1));

    fclose(arquivoCsv);
    fclose(arquivoBin);
}

#endif // CONVERSAO_H_INCLUDED
