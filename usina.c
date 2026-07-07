/*******************************************************************
 * Projeto Final - Estrutura de Dados
 *
 * Proejto 4 - Otimizador de Despacho de Carga
 *
 * Arquivo: usina.c
 ********************************************************************/

#include "usina.h"

/********************************************************************
 * Função: criar_no
 *
 * Objetivo:
 * Criar um novo nó da árvore e armazenar os dados da usina.
 ********************************************************************/
NoABB *criar_no(Usina u)
{
    NoABB *novo;

    novo = (NoABB *) malloc(sizeof(NoABB));

    if (novo == NULL)
    {
        printf("Erro na alocacao de memoria.\n");
        exit(1);
    }

    novo->dados = u;
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}


/********************************************************************
 * Função: inserir_abb
 *
 * Objetivo:
 * Inserir uma usina na Árvore Binária de Busca utilizando
 * o código da usina como chave.
 ********************************************************************/
void inserir_abb(NoABB **raiz, Usina u)
{
    if (*raiz == NULL)
    {
        *raiz = criar_no(u);
        return;
    }

    if (u.codigo < (*raiz)->dados.codigo)
    {
        inserir_abb(&((*raiz)->esq), u);
    }
    else
    {
        inserir_abb(&((*raiz)->dir), u);
    }
}


/********************************************************************
 * Função: buscar_abb
 *
 * Objetivo:
 * Localizar uma usina utilizando seu código.
 ********************************************************************/
NoABB *buscar_abb(NoABB *raiz, int codigo)
{
    if (raiz == NULL)
    {
        return NULL;
    }

    if (codigo == raiz->dados.codigo)
    {
        return raiz;
    }

    if (codigo < raiz->dados.codigo)
    {
        return buscar_abb(raiz->esq, codigo);
    }

    return buscar_abb(raiz->dir, codigo);
}


/********************************************************************
 * Função: liberar_abb
 *
 * Objetivo:
 * Liberar toda a memória utilizada pela árvore.
 ********************************************************************/
void liberar_abb(NoABB *raiz)
{
    if (raiz == NULL)
    {
        return;
    }

    liberar_abb(raiz->esq);

    liberar_abb(raiz->dir);

    free(raiz);
}

/********************************************************************
 * Função: contar_ativas
 *
 * Objetivo:
 * Contar quantas usinas estão ativas na árvore.
 ********************************************************************/
int contar_ativas(NoABB *raiz)
{
    if (raiz == NULL)
    {
        return 0;
    }

    return (raiz->dados.status == 1)
           + contar_ativas(raiz->esq)
           + contar_ativas(raiz->dir);
}


/********************************************************************
 * Função: copiar_ativas_para_vetor
 *
 * Objetivo:
 * Percorrer a árvore e copiar todas as usinas ativas
 * para um vetor.
 ********************************************************************/
void copiar_ativas_para_vetor(NoABB *raiz,
                              Usina *vetor,
                              int *indice)
{
    if (raiz == NULL)
    {
        return;
    }

    /* Percorre esquerda */
    copiar_ativas_para_vetor(raiz->esq, vetor, indice);

    /* Copia apenas usinas ativas */
    if (raiz->dados.status == 1)
    {
        vetor[*indice] = raiz->dados;
        (*indice)++;
    }

    /* Percorre direita */
    copiar_ativas_para_vetor(raiz->dir, vetor, indice);
}


/********************************************************************
 * Função: quicksort_usinas
 *
 * Objetivo:
 * Ordenar o vetor pelo menor custo de geração.
 ********************************************************************/
void quicksort_usinas(Usina *vetor, int inicio, int fim)
{
    int i;
    int j;
    Usina pivo;
    Usina temp;

    i = inicio;
    j = fim;

    pivo = vetor[(inicio + fim) / 2];

    while (i <= j)
    {
        while (vetor[i].custo_mwh < pivo.custo_mwh)
        {
            i++;
        }

        while (vetor[j].custo_mwh > pivo.custo_mwh)
        {
            j--;
        }

        if (i <= j)
        {
            temp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = temp;

            i++;
            j--;
        }
    }

    if (inicio < j)
    {
        quicksort_usinas(vetor, inicio, j);
    }

    if (i < fim)
    {
        quicksort_usinas(vetor, i, fim);
    }
}


/********************************************************************
 * Função: despachar_carga
 *
 * Objetivo:
 * Atender a demanda utilizando primeiro as usinas
 * de menor custo.
 ********************************************************************/
void despachar_carga(NoABB *raiz, float demanda_solicitada)
{
    int n;
    int indice;
    int i;

    float carga_atual;
    float custo_total;
    float necessidade;
    float geracao;

    Usina *vetor_ativas;

    /* Conta quantas usinas estão ativas */
    n = contar_ativas(raiz);

    if (n == 0)
    {
        printf("Nenhuma usina ativa disponivel.\n");
        return;
    }

    /* Aloca o vetor */
    vetor_ativas = (Usina *) malloc(n * sizeof(Usina));

    if (vetor_ativas == NULL)
    {
        printf("Erro na alocacao de memoria.\n");
        exit(1);
    }

    /* Copia as usinas para o vetor */
    indice = 0;

    copiar_ativas_para_vetor(raiz,
                             vetor_ativas,
                             &indice);

    /* Ordena pelo menor custo */
    quicksort_usinas(vetor_ativas,
                     0,
                     n - 1);

    carga_atual = 0.0;
    custo_total = 0.0;

    printf("\n------------------------------------------\n");
    printf(" DESPACHO DE ENERGIA\n");
    printf("------------------------------------------\n\n");

    for (i = 0; i < n && carga_atual < demanda_solicitada; i++)
    {
        necessidade = demanda_solicitada - carga_atual;

        if (vetor_ativas[i].capacidade_mw > necessidade)
        {
            geracao = necessidade;
        }
        else
        {
            geracao = vetor_ativas[i].capacidade_mw;
        }

        carga_atual += geracao;

        custo_total += geracao * vetor_ativas[i].custo_mwh;

        printf("Usina %d (%s)\n",
               vetor_ativas[i].codigo,
               vetor_ativas[i].tipo);

        printf("Geracao : %.2f MW\n", geracao);

        printf("Custo   : R$ %.2f / MWh\n\n",
               vetor_ativas[i].custo_mwh);
    }

    if (carga_atual < demanda_solicitada)
    {
        printf("------------------------------------------\n");
        printf("ATENCAO!\n");
        printf("Nao foi possivel atender toda a demanda.\n");
        printf("Faltaram %.2f MW.\n",
               demanda_solicitada - carga_atual);
    }
    else
    {
        printf("------------------------------------------\n");
        printf("Despacho realizado com sucesso.\n");
    }

    printf("Energia fornecida : %.2f MW\n", carga_atual);
    printf("Custo total       : R$ %.2f\n", custo_total);

    /* Libera memória */
    free(vetor_ativas);
}