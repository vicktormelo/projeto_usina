/***********************************************************************
 * Projeto Final - Estrutura de Dados
 *
 * Projeto 4 - Otimizador de Despacho de Carga
 * Versão 2.0
 *
 * Arquivo: usina.c
 ***********************************************************************/

#include "usina.h"

/***********************************************************************
 * Funções auxiliares
 ***********************************************************************/

void limpar_tela(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar(void)
{
    printf("\nPressione ENTER para continuar...");
    getchar();
}

void menu(void)
{
    printf("\n");
    printf("=====================================================\n");
    printf("      OTIMIZADOR DE DESPACHO DE CARGA - V2.0\n");
    printf("=====================================================\n");
    printf("1 - Cadastrar usina\n");
    printf("2 - Buscar usina\n");
    printf("3 - Listar usinas\n");
    printf("4 - Ativar usina\n");
    printf("5 - Desativar usina\n");
    printf("6 - Estatisticas\n");
    printf("7 - Solicitar despacho\n");
    printf("0 - Sair\n");
    printf("=====================================================\n");
    printf("Opcao: ");
}

/***********************************************************************
 * Criação do nó
 ***********************************************************************/

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

/***********************************************************************
 * Inserção na ABB
 ***********************************************************************/

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
    else if (u.codigo > (*raiz)->dados.codigo)
    {
        inserir_abb(&((*raiz)->dir), u);
    }
    else
    {
        printf("\nCodigo %d ja cadastrado.\n", u.codigo);
    }
}

/***********************************************************************
 * Busca por código
 ***********************************************************************/

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

/***********************************************************************
 * Impressão de uma usina
 ***********************************************************************/

void imprimir_usina(Usina u)
{
    printf("---------------------------------------------\n");
    printf("Codigo      : %d\n", u.codigo);
    printf("Tipo        : %s\n", u.tipo);
    printf("Capacidade  : %.2f MW\n", u.capacidade_mw);
    printf("Custo       : R$ %.2f / MWh\n", u.custo_mwh);

    if (u.status == ATIVA)
    {
        printf("Status      : ATIVA\n");
    }
    else
    {
        printf("Status      : INATIVA\n");
    }

    printf("---------------------------------------------\n");
}

/***********************************************************************
 * Listagem em ordem crescente de código
 ***********************************************************************/

void listar_usinas(NoABB *raiz)
{
    if (raiz == NULL)
    {
        return;
    }

    listar_usinas(raiz->esq);

    imprimir_usina(raiz->dados);

    listar_usinas(raiz->dir);
}

/***********************************************************************
 * Liberação da árvore
 ***********************************************************************/

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

/***********************************************************************
 * Cadastro de Usina
 ***********************************************************************/

Usina cadastrar_usina(void)
{
    Usina nova;

    printf("\n========== CADASTRO DE USINA ==========\n");

    printf("Codigo: ");
    scanf("%d", &nova.codigo);
    getchar();

    printf("Tipo: ");
    fgets(nova.tipo, MAX_TIPO, stdin);

    /* Remove o '\n' do fgets */
    nova.tipo[strcspn(nova.tipo, "\n")] = '\0';

    printf("Capacidade (MW): ");
    scanf("%f", &nova.capacidade_mw);

    printf("Custo (R$/MWh): ");
    scanf("%f", &nova.custo_mwh);

    printf("Status (1 = Ativa | 0 = Inativa): ");
    scanf("%d", &nova.status);
    getchar();

    return nova;
}

/***********************************************************************
 * Ativar Usina
 ***********************************************************************/

void ativar_usina(NoABB *raiz, int codigo)
{
    NoABB *aux;

    aux = buscar_abb(raiz, codigo);

    if (aux == NULL)
    {
        printf("\nUsina nao encontrada.\n");
        return;
    }

    aux->dados.status = ATIVA;

    printf("\nUsina ativada com sucesso.\n");
}

/***********************************************************************
 * Desativar Usina
 ***********************************************************************/

void desativar_usina(NoABB *raiz, int codigo)
{
    NoABB *aux;

    aux = buscar_abb(raiz, codigo);

    if (aux == NULL)
    {
        printf("\nUsina nao encontrada.\n");
        return;
    }

    aux->dados.status = INATIVA;

    printf("\nUsina desativada com sucesso.\n");
}

/***********************************************************************
 * Conta todas as usinas
 ***********************************************************************/

int contar_total(NoABB *raiz)
{
    if (raiz == NULL)
    {
        return 0;
    }

    return 1
        + contar_total(raiz->esq)
        + contar_total(raiz->dir);
}

/***********************************************************************
 * Conta apenas usinas ativas
 ***********************************************************************/

int contar_ativas(NoABB *raiz)
{
    if (raiz == NULL)
    {
        return 0;
    }

    return (raiz->dados.status == ATIVA)
        + contar_ativas(raiz->esq)
        + contar_ativas(raiz->dir);
}

/***********************************************************************
 * Conta apenas usinas inativas
 ***********************************************************************/

int contar_inativas(NoABB *raiz)
{
    if (raiz == NULL)
    {
        return 0;
    }

    return (raiz->dados.status == INATIVA)
        + contar_inativas(raiz->esq)
        + contar_inativas(raiz->dir);
}

/***********************************************************************
 * Soma toda a capacidade instalada
 ***********************************************************************/

float capacidade_total(NoABB *raiz)
{
    if (raiz == NULL)
    {
        return 0.0f;
    }

    return raiz->dados.capacidade_mw
        + capacidade_total(raiz->esq)
        + capacidade_total(raiz->dir);
}

/***********************************************************************
 * Soma apenas capacidade disponível
 ***********************************************************************/

float capacidade_ativa(NoABB *raiz)
{
    float capacidade = 0.0f;

    if (raiz == NULL)
    {
        return 0.0f;
    }

    if (raiz->dados.status == ATIVA)
    {
        capacidade = raiz->dados.capacidade_mw;
    }

    return capacidade
        + capacidade_ativa(raiz->esq)
        + capacidade_ativa(raiz->dir);
}

/***********************************************************************
 * Soma os custos das usinas
 ***********************************************************************/

float soma_custos(NoABB *raiz)
{
    if (raiz == NULL)
    {
        return 0.0f;
    }

    return raiz->dados.custo_mwh
        + soma_custos(raiz->esq)
        + soma_custos(raiz->dir);
}

/***********************************************************************
 * Exibe estatísticas
 ***********************************************************************/

void mostrar_estatisticas(NoABB *raiz)
{
    int total;
    int ativas;
    int inativas;

    float capacidadeInstalada;
    float capacidadeDisponivel;
    float mediaCusto;

    total = contar_total(raiz);
    ativas = contar_ativas(raiz);
    inativas = contar_inativas(raiz);

    capacidadeInstalada = capacidade_total(raiz);
    capacidadeDisponivel = capacidade_ativa(raiz);

    if (total > 0)
    {
        mediaCusto = soma_custos(raiz) / total;
    }
    else
    {
        mediaCusto = 0.0f;
    }

    printf("\n=========================================\n");
    printf("          ESTATISTICAS DO SISTEMA\n");
    printf("=========================================\n");

    printf("Total de usinas...........: %d\n", total);
    printf("Usinas ativas............: %d\n", ativas);
    printf("Usinas inativas..........: %d\n", inativas);

    printf("Capacidade instalada.....: %.2f MW\n",
           capacidadeInstalada);

    printf("Capacidade disponivel....: %.2f MW\n",
           capacidadeDisponivel);

    printf("Custo medio..............: R$ %.2f / MWh\n",
           mediaCusto);

    printf("=========================================\n");
}

/***********************************************************************
 * Copia as usinas ativas para um vetor
 ***********************************************************************/
void copiar_ativas_para_vetor(NoABB *raiz,
                              Usina vetor[],
                              int *indice)
{
    if (raiz == NULL)
    {
        return;
    }

    copiar_ativas_para_vetor(raiz->esq, vetor, indice);

    if (raiz->dados.status == ATIVA)
    {
        vetor[*indice] = raiz->dados;
        (*indice)++;
    }

    copiar_ativas_para_vetor(raiz->dir, vetor, indice);
}

/***********************************************************************
 * Quicksort
 ***********************************************************************/
void quicksort_usinas(Usina vetor[],
                      int inicio,
                      int fim)
{
    int i;
    int j;

    Usina pivo;
    Usina aux;

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
            aux = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = aux;

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

/***********************************************************************
 * Despacho de carga
 ***********************************************************************/
void despachar_carga(NoABB *raiz,
                     float demanda)
{
    int quantidade;
    int indice;
    int i;

    float cargaAtual;
    float necessidade;
    float geracao;
    float custoTotal;

    Usina *vetor;

    quantidade = contar_ativas(raiz);

    if (quantidade == 0)
    {
        printf("\nNao existem usinas ativas.\n");
        return;
    }

    vetor = (Usina *) malloc(sizeof(Usina) * quantidade);

    if (vetor == NULL)
    {
        printf("\nErro de memoria.\n");
        exit(1);
    }

    indice = 0;

    copiar_ativas_para_vetor(raiz,
                             vetor,
                             &indice);

    quicksort_usinas(vetor,
                     0,
                     quantidade - 1);

    cargaAtual = 0.0f;
    custoTotal = 0.0f;

    printf("\n");
    printf("=====================================================\n");
    printf("           DESPACHO DE CARGA\n");
    printf("=====================================================\n");
    printf("Demanda solicitada : %.2f MW\n\n", demanda);

    for (i = 0; i < quantidade && cargaAtual < demanda; i++)
    {
        necessidade = demanda - cargaAtual;

        if (vetor[i].capacidade_mw >= necessidade)
        {
            geracao = necessidade;
        }
        else
        {
            geracao = vetor[i].capacidade_mw;
        }

        cargaAtual += geracao;
        custoTotal += geracao * vetor[i].custo_mwh;

        printf("------------------------------------------\n");
        printf("Codigo      : %d\n", vetor[i].codigo);
        printf("Tipo        : %s\n", vetor[i].tipo);
        printf("Geracao     : %.2f MW\n", geracao);
        printf("Custo Unit. : R$ %.2f / MWh\n", vetor[i].custo_mwh);
        printf("Custo Parc. : R$ %.2f\n",
               geracao * vetor[i].custo_mwh);
    }

    printf("------------------------------------------\n");

    if (cargaAtual >= demanda)
    {
        printf("Despacho concluido com sucesso.\n");
    }
    else
    {
        printf("ATENCAO!\n");
        printf("Nao foi possivel atender toda a demanda.\n");
        printf("Faltaram %.2f MW\n",
               demanda - cargaAtual);
    }

    printf("\nResumo\n");
    printf("Energia fornecida : %.2f MW\n", cargaAtual);
    printf("Custo total       : R$ %.2f\n", custoTotal);

    free(vetor);
}