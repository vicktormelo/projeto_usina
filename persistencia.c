/***********************************************************************
 * Projeto Final - Estrutura de Dados
 *
 * Sistema Inteligente de Gerenciamento
 * e Despacho de Energia (SIGDE)
 *
 * Arquivo: persistencia.c
 *
 * Responsável pela persistência dos dados do sistema.
 ***********************************************************************/

#include "persistencia.h"

/***********************************************************************
 * FUNÇÃO AUXILIAR
 *
 * Percorre a ABB em ordem gravando todas as usinas.
 ***********************************************************************/

static void gravar_em_arquivo(NoABB *raiz, FILE *arquivo)
{
    if (raiz == NULL)
    {
        return;
    }

    gravar_em_arquivo(raiz->esq, arquivo);

    fprintf(arquivo,
            "%d;%d;%d;%d;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%d;%d;%d;%s\n",

            raiz->dados.codigo,

            raiz->dados.tipo,

            raiz->dados.regiao,

            raiz->dados.status,

            raiz->dados.potencia_instalada,

            raiz->dados.capacidade_disponivel,

            raiz->dados.reservatorio,

            raiz->dados.custo_mwh,

            raiz->dados.producao_diaria,

            raiz->dados.producao_mensal,

            raiz->dados.energia_total,

            raiz->dados.faturamento_total,

            raiz->dados.despachos,

            raiz->dados.horas_operacao,

            raiz->dados.prioridade,

            raiz->dados.ultima_manutencao);

    gravar_em_arquivo(raiz->dir, arquivo);
}

/***********************************************************************
 * SALVAR TODAS AS USINAS
 ***********************************************************************/

void salvar_usinas(NoABB *raiz)
{
    FILE *arquivo;

    arquivo = fopen(ARQUIVO_USINAS, "w");

    if (arquivo == NULL)
    {
        printf("\nErro ao abrir %s\n",
               ARQUIVO_USINAS);

        return;
    }

    gravar_em_arquivo(raiz,
                      arquivo);

    fclose(arquivo);

    printf("\nBanco de dados salvo com sucesso.\n");
}

/***********************************************************************
 * CARREGA TODAS AS USINAS DO ARQUIVO
 ***********************************************************************/

void carregar_usinas(NoABB **raiz)
{
    FILE *arquivo;

    Usina usina;

    arquivo = fopen(ARQUIVO_USINAS, "r");

    if (arquivo == NULL)
    {
        printf("\nBanco de dados inexistente.\n");
        printf("Um novo banco sera criado automaticamente.\n");

        return;
    }

    while (fscanf(arquivo,
                  "%d;%d;%d;%d;%f;%f;%f;%f;%f;%f;%f;%f;%d;%d;%d;%49[^\n]\n",

                  &usina.codigo,

                  (int *)&usina.tipo,

                  (int *)&usina.regiao,

                  (int *)&usina.status,

                  &usina.potencia_instalada,

                  &usina.capacidade_disponivel,

                  &usina.reservatorio,

                  &usina.custo_mwh,

                  &usina.producao_diaria,

                  &usina.producao_mensal,

                  &usina.energia_total,

                  &usina.faturamento_total,

                  &usina.despachos,

                  &usina.horas_operacao,

                  (int *)&usina.prioridade,

                  usina.ultima_manutencao) == 16)
    {
        //*raiz = inserir_abb(*raiz, usina);
        inserir_abb(raiz, usina);
    }

    fclose(arquivo);

    printf("\nBanco de dados carregado com sucesso.\n");
}

/***********************************************************************
 * REGISTRA UM DESPACHO NO HISTÓRICO
 ***********************************************************************/

void registrar_historico(float demanda,
                         float energia_fornecida,
                         float custo_total)
{
    FILE *arquivo;

    arquivo = fopen(ARQUIVO_HISTORICO, "a");

    if (arquivo == NULL)
    {
        printf("\nErro ao abrir historico.\n");
        return;
    }

    fprintf(arquivo,
            "%.2f;%.2f;%.2f\n",
            demanda,
            energia_fornecida,
            custo_total);

    fclose(arquivo);
}

/***********************************************************************
 * GERA UM TICKET DO DESPACHO
 ***********************************************************************/

void gerar_ticket(float demanda,
                  float energia_fornecida,
                  float custo_total)
{
    FILE *arquivo;

    char nomeArquivo[100];

    static int numero_ticket = 1;

    sprintf(nomeArquivo,
            "%sticket_%04d.txt",
            PASTA_TICKETS,
            numero_ticket++);

    arquivo = fopen(nomeArquivo, "w");

    if (arquivo == NULL)
    {
        printf("\nErro ao gerar ticket.\n");
        return;
    }

    fprintf(arquivo,
            "=====================================\n");

    fprintf(arquivo,
            "SIGDE - COMPROVANTE DE DESPACHO\n");

    fprintf(arquivo,
            "=====================================\n\n");

    fprintf(arquivo,
            "Demanda.............: %.2f MW\n",
            demanda);

    fprintf(arquivo,
            "Energia fornecida...: %.2f MW\n",
            energia_fornecida);

    fprintf(arquivo,
            "Custo total.........: R$ %.2f\n",
            custo_total);

    fprintf(arquivo,
            "\n=====================================\n");

    fclose(arquivo);

    printf("\nTicket gerado: %s\n",
           nomeArquivo);
}

/***********************************************************************
 * INICIALIZA O BANCO DE DADOS
 *
 * Verifica a existência dos arquivos utilizados pelo sistema.
 * Caso não existam, eles são criados automaticamente.
 ***********************************************************************/

void inicializar_banco(void)
{
    FILE *arquivo;

    /* Banco de usinas */

    arquivo = fopen(ARQUIVO_USINAS, "r");

    if (arquivo == NULL)
    {
        arquivo = fopen(ARQUIVO_USINAS, "w");

        if (arquivo != NULL)
        {
            fclose(arquivo);

            printf("Arquivo %s criado.\n",
                   ARQUIVO_USINAS);
        }
    }
    else
    {
        fclose(arquivo);
    }

    /* Histórico */

    arquivo = fopen(ARQUIVO_HISTORICO, "r");

    if (arquivo == NULL)
    {
        arquivo = fopen(ARQUIVO_HISTORICO, "w");

        if (arquivo != NULL)
        {
            fclose(arquivo);

            printf("Arquivo %s criado.\n",
                   ARQUIVO_HISTORICO);
        }
    }
    else
    {
        fclose(arquivo);
    }
}
