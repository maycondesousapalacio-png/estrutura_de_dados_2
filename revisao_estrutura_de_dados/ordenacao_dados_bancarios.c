#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "transacao.h"
#include "listar_transacoes.h"
#include "conversao.h"
#include "metodos_ordenacao.h"
#include "liberar_memoria.h"

int main() {
    setlocale(LC_ALL, "Portuguese");

    char arquivo_novo[] = "transacoes.dat";
    int linhas_lidas = 0;
    int *linhas = &linhas_lidas;
    struct No *lista_transacoes = NULL;
    struct No *lista_transacoes2 = NULL;
    struct Transacao t;
    int registros_fila_pendentes = 0;
    int numRegistros = 1600;
    struct No *lista_risco = NULL;
    float valor_limite_risco = 398.0f;
    double total_visa = 0.0;
    double total_master = 0.0;
    unsigned long maior_id = 0;
    float maior_valor = 0.0f;

    struct PilhaAuditoria pilha_rejeitadas;
    inicializar_pilha(&pilha_rejeitadas);

    conversaoBinario(&linhas_lidas, "transacoes.dat", 100050,
                     &pilha_rejeitadas, &lista_risco, valor_limite_risco,
                     &total_visa, &total_master, &maior_id, &maior_valor);

    int count_rejeitadas = 0;
    struct No *aux_pilha = pilha_rejeitadas.topo;
    while (aux_pilha) { count_rejeitadas++; aux_pilha = aux_pilha->proximo; }

    FILE *tmp = fopen("transacoes.dat", "rb");
    fseek(tmp, 0, SEEK_END);
    long tam = ftell(tmp);
    fclose(tmp);

    // -----------------------------------------------------------------------
    FILE *arquivoBin = fopen(arquivo_novo, "rb");
    if(arquivoBin == NULL) {
        printf("Arquivo 'transacoes.dat' não foi encontrado");
        return 1;
    }
    while(fread(&t, sizeof(struct Transacao), 1, arquivoBin) == 1) {
        lista_transacoes = inserirTransacao_inicio(lista_transacoes, t);
    }
    fclose(arquivoBin);

    // -----------------------------------------------------------------------
    printf("\n------------------------------\n");
    printf("Ordenando - Bubble Sort aguarde...\n");
    clock_t tempo_inicial_bubble = clock();
    ordenacao_bubble_sort(lista_transacoes);
    clock_t tempo_final_bubble = clock();
    double tempo_execucao_bubble = (double)(tempo_final_bubble - tempo_inicial_bubble) / CLOCKS_PER_SEC;
    criar_arquivo_ordenado_bubblesort(lista_transacoes);

    liberar_lista(lista_transacoes);

    // -----------------------------------------------------------------------
    FILE *arquivoBin2 = fopen(arquivo_novo, "rb");
    if(arquivoBin2 == NULL) {
        printf("Arquivo 'transacoes.dat' não foi encontrado");
        return 1;
    }
    while(fread(&t, sizeof(struct Transacao), 1, arquivoBin2) == 1) {
        lista_transacoes2 = inserirTransacao_inicio(lista_transacoes2, t);
    }
    fclose(arquivoBin2);

    // -----------------------------------------------------------------------
    int contagem = 1;
    int *contador = &contagem;
    int visa = 0;
    int master = 0;
    int temp_cont = 0;

    struct No *ultimo = ultimo_registro(lista_transacoes2, &temp_cont, &visa, &master);

    printf("\n------------------------------\n");
    printf("Ordenando - Quick Sort aguarde...\n");

    clock_t tempo_inicial_quick = clock();
    quicksort_iterativo(lista_transacoes2, ultimo, linhas_lidas, &visa, &master);
    clock_t tempo_final_quick = clock();
    double tempo_execucao_quick = (double)(tempo_final_quick - tempo_inicial_quick) / CLOCKS_PER_SEC;

    criar_arquivo_ordenado_quicksort(lista_transacoes2);

    // -----------------------------------------------------------------------
    struct FilaPendentes fila;
    iniciar_fila(&fila);
    struct No *transacao_atual = lista_transacoes2;
    while(transacao_atual != NULL) {
        if(transacao_atual->tra.status == 0) {
            ++registros_fila_pendentes;
            inserir_fila(&fila, transacao_atual->tra);
        }
        transacao_atual = transacao_atual->proximo;
    }
    liberar_fila(&fila);
    liberar_lista(lista_transacoes2);

    // -----------------------------------------------------------------------
    printf("\n--- TRANSAÇÕES DE RISCO ---\n");
    struct No *aux = lista_risco;
    int count_risco = 0;
    while (aux) {
        count_risco++;
        aux = aux->proximo;
    }
    printf("Total de transações de risco: %d\n", count_risco);

    // -----------------------------------------------------------------------
    printf("\n--- PILHA DE AUDITORIA (TRANSAÇÕES REJEITADAS) ---\n");
    if (pilha_vazia(&pilha_rejeitadas)) {
        printf("Nenhuma transação rejeitada para revisão.\n");
    } else {
        char opcao;
        do {
            printf("\nDeseja desfazer (estornar) a ÚLTIMA transação rejeitada? (s/n): ");
            scanf(" %c", &opcao);
            if (opcao == 's' || opcao == 'S') {
                if (!pilha_vazia(&pilha_rejeitadas)) {
                    undo(&pilha_rejeitadas);
                } else {
                    printf("Pilha de auditoria vazia. Nada mais para desfazer.\n");
                    break;
                }
            } else {
                break;
            }
        } while (1);
    }

    // ==================== GERAR RELATÓRIO CONSOLIDADO ====================
    FILE *rel = fopen("relatorio_consolidado.txt", "w");
    if (!rel) {
        printf("Erro ao criar relatório\n");
        return 1;
    }

    fprintf(rel, "==================================================\n");
    fprintf(rel, "RELATORIO DE PERFORMANCE E AUDITORIA DE TRANSACOES\n");
    fprintf(rel, "==================================================\n\n");

    fprintf(rel, "1. DESEMPENHO DA ORDENACAO\n");
    fprintf(rel, "  - Tempo gasto para ordenar %d registros: \n  - Bubble Sort:  %.2f segundos.\n", linhas_lidas, tempo_execucao_bubble);
    fprintf(rel, "  - Quick Sort: %.2f segundos.\n\n", tempo_execucao_quick);

    fprintf(rel, "2. METRICAS FINANCEIRAS\n");
    fprintf(rel, "  - Total processado por Bandeira - Visa: R$ %.2f\n", total_visa);
    fprintf(rel, "  - Total processado por Bandeira - Mastercard: R$ %.2f\n", total_master);
    fprintf(rel, "  - Maior transacao detectada: ID %lu - Valor: R$ %.2f\n\n", maior_id, maior_valor);

    fprintf(rel, "3. STATUS DAS ESTRUTURAS\n");
    fprintf(rel, "  - Transacoes processadas na Fila (FIFO): %d transaçoes.\n", registros_fila_pendentes);
    fprintf(rel, "  - Transacoes armazenadas na Pilha de Rejeicao: %d transacoes.\n", count_rejeitadas);
    fprintf(rel, "  - Transacoes críticas na Lista de Suspeitas: %d transacoes.\n\n", count_risco);

    fprintf(rel, "==================================================\n");
    fprintf(rel, "LISTA DE TRANSACOES SUSPEITAS (VALOR ALTO + MADRUGADA)\n");
    fprintf(rel, "==================================================\n");

    struct No *suspeito = lista_risco;
    while (suspeito) {
        fprintf(rel, "[ID: %lu] - Data: %s %s:00 - Valor: R$ %.2f - Categoria: %s\n",
                suspeito->tra.id, suspeito->tra.data, suspeito->tra.hora,
                suspeito->tra.valor, suspeito->tra.categoria);
        suspeito = suspeito->proximo;
    }
    fclose(rel);

    printf("\nRelatório gerado: relatorio_consolidado.txt\n\n");
    system("pause");

    // ==================== LIBERAR ESTRUTURAS RESTANTES ====================
    while (!pilha_vazia(&pilha_rejeitadas)) {
        desempilhar_rejeitada(&pilha_rejeitadas);
    }
    liberar_lista(lista_risco);

    // -----------------------------------------------------------------------
    printf("\n------------------------------------\nTEMPOS DE EXECUÇÃO\n\n\n");
    printf("Bubble Sort: %lf\n", tempo_execucao_bubble);
    printf("Quick Sort: %lf\n", tempo_execucao_quick);

    printf("\n\n\nTOTAL BANDEIRAS PROCESSADAS\n\n");
    printf("Visa: %i\n", visa);
    printf("MasterCard: %i\n", master);

    printf("\nDeseja exibir detalhes no console? (s/n): ");
    char opt;
    scanf(" %c", &opt);
    if (opt == 's' || opt == 'S') {
        system("type relatorio_consolidado.txt");
    }

    return 0;
}
