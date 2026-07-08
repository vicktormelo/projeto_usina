/***********************************************************************
 * Projeto Final - Estrutura de Dados
 *
 * Sistema Inteligente de Gerenciamento
 * e Despacho de Energia (SIGDE)
 *
 * Arquivo: relatorios.c
 *
 * Módulo responsável apenas pela apresentação das
 * informações do sistema.
 ***********************************************************************/

#include "relatorios.h"

/***********************************************************************
 * RELATÓRIO DE USINAS
 ***********************************************************************/

void relatorio_usinas(NoABB *raiz)
{
    mostrar_cabecalho("RELATORIO DE USINAS");

    if (raiz == NULL)
    {
        printf("\nNenhuma usina cadastrada.\n");
        return;
    }

    printf("%-8s %-15s %-15s %-12s %-12s\n",
           "Codigo",
           "Tipo",
           "Regiao",
           "Capacidade",
           "Status");

    linha_dupla();

    listar_usinas(raiz);

    linha_dupla();

    printf("\nTotal de usinas: %d\n",
           quantidade_usinas(raiz));
}

/***********************************************************************
 * RELATÓRIO ESTATÍSTICO
 ***********************************************************************/

void relatorio_estatisticas(NoABB *raiz)
{
    int total;

    int ativas;

    float potencia;

    float capacidade;

    mostrar_cabecalho("ESTATISTICAS DO SISTEMA");

    total = quantidade_usinas(raiz);

    ativas = quantidade_ativas(raiz);

    potencia = potencia_total(raiz);

    capacidade = capacidade_total_disponivel(raiz);

    printf("Usinas cadastradas........: %d\n",
           total);

    printf("Usinas ativas............: %d\n",
           ativas);

    printf("Usinas inativas..........: %d\n",
           total - ativas);

    printf("Potencia instalada.......: %.2f MW\n",
           potencia);

	printf("Capacidade disponivel....: %.2f MW\n",
       capacidade);

	if (potencia > 0)
	{
    printf("Utilizacao...............: %.2f %%\n",
           (capacidade / potencia) * 100.0f);
	}

linha_dupla();

}

/***********************************************************************
 * RELATÓRIO DE CAPACIDADE DISPONÍVEL
 ***********************************************************************/

static void listar_capacidade(NoABB *raiz)
{
    if (raiz == NULL)
    {
        return;
    }

    listar_capacidade(raiz->esq);

    printf("%5d  %-15s %10.2f MW  %10.2f MW\n",
           raiz->dados.codigo,
           tipo_para_texto(raiz->dados.tipo),
           raiz->dados.capacidade_disponivel,
           raiz->dados.potencia_instalada);

    listar_capacidade(raiz->dir);
}

void relatorio_capacidade(NoABB *raiz)
{
    mostrar_cabecalho("CAPACIDADE DAS USINAS");

    if (raiz == NULL)
    {
        printf("\nNenhuma usina cadastrada.\n");
        return;
    }

    printf("%-5s %-15s %-15s %-15s\n",
           "Cod",
           "Tipo",
           "Disponivel",
           "Instalada");

    linha_dupla();

    listar_capacidade(raiz);

    linha_dupla();
}

/***********************************************************************
 * RELATÓRIO DE CUSTOS
 ***********************************************************************/

static void listar_custos(NoABB *raiz)
{
    if (raiz == NULL)
    {
        return;
    }

    listar_custos(raiz->esq);

    printf("%5d  %-15s R$ %10.2f/MWh\n",
           raiz->dados.codigo,
           tipo_para_texto(raiz->dados.tipo),
           raiz->dados.custo_mwh);

    listar_custos(raiz->dir);
}

void relatorio_custos(NoABB *raiz)
{
    mostrar_cabecalho("CUSTO DAS USINAS");

    if (raiz == NULL)
    {
        printf("\nNenhuma usina cadastrada.\n");
        return;
    }

    printf("%-5s %-15s %-15s\n",
           "Cod",
           "Tipo",
           "Custo");

    linha_dupla();

    listar_custos(raiz);

    linha_dupla();
}
