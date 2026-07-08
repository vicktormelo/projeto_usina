/***********************************************************************
 * SIGDE - Sistema Inteligente de Gerenciamento e Despacho de Energia
 *
 * Arquivo : despacho.c
 * Módulo  : Algoritmo de Despacho
 * Versão  : 3.0.0
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "despacho.h"

static int prioridade_ecologica(TipoUsina tipo);

static float calcular_score(Usina usina);

/***********************************************************************
 * CONVERSÃO
 ***********************************************************************/

static int prioridade_ecologica(TipoUsina tipo)
{
    switch (tipo)
    {
        case SOLAR:
            return 1;

        case EOLICA:
            return 2;

        case HIDRELETRICA:
            return 3;

        case BIOMASSA:
            return 4;

        case TERMOELETRICA:
            return 5;

        default:
            return 99;
    }
}

static float calcular_score(Usina usina)
{
    return usina.capacidade_disponivel
           + (6 - usina.prioridade) * 100.0f
           - usina.custo_mwh;
}

const char *politica_para_texto(
            PoliticaDespacho politica)
{
    switch(politica)
    {
        case DESPACHO_ECONOMICO:
            return "Economico";

        case DESPACHO_EMERGENCIA:
            return "Emergencia";

        case DESPACHO_ECOLOGICO:
            return "Ecologico";

        case DESPACHO_BALANCEADO:
            return "Balanceado";

        default:
            return "Desconhecida";
    }
}

/***********************************************************************
 * MENU DE POLÍTICAS
 ***********************************************************************/

PoliticaDespacho escolher_politica(void)
{
    int op;

    do
    {
        linha_dupla();

        printf("POLITICA DE DESPACHO\n");

        linha();

        printf("1 - Economico\n");
        printf("2 - Emergencia\n");
        printf("3 - Ecologico\n");
        printf("4 - Balanceado\n");

        op = ler_inteiro("Escolha: ");

    } while(op < 1 || op > 4);

    return (PoliticaDespacho) op;
}

/***********************************************************************
 * PARTICIONAMENTO DO QUICKSORT
 ***********************************************************************/

int particionar(Usina vetor[],
                int inicio,
                int fim,
                PoliticaDespacho politica)
{
    Usina pivo;
    Usina aux;

    int i;
    int j;

    pivo = vetor[fim];

    i = inicio - 1;

    for (j = inicio; j < fim; j++)
    {
        if (comparar_usinas(&vetor[j], &pivo, politica) <= 0)
        {
            i++;

            aux = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = aux;
        }
    }

    aux = vetor[i + 1];
    vetor[i + 1] = vetor[fim];
    vetor[fim] = aux;

    return i + 1;
}

/***********************************************************************
 * QUICKSORT DAS USINAS
 ***********************************************************************/

void quicksort_usinas(Usina vetor[],
                      int inicio,
                      int fim,
                      PoliticaDespacho politica)
{
    int pivo;

    if (inicio < fim)
    {
        pivo = particionar(vetor,
                           inicio,
                           fim,
						   politica);

        quicksort_usinas(vetor,
                         inicio,
                         pivo - 1,
						 politica);

        quicksort_usinas(vetor,
                         pivo + 1,
                         fim,
						 politica);
    }
}

/***********************************************************************
 * CONTA USINAS ATIVAS
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
 * COPIA APENAS USINAS ATIVAS PARA O VETOR
 ***********************************************************************/

void copiar_ativas(NoABB *raiz,
                   Usina vetor[],
                   int *indice)
{
    if (raiz == NULL)
    {
        return;
    }

    copiar_ativas(raiz->esq,
                  vetor,
                  indice);

    if (raiz->dados.status == ATIVA)
    {
        vetor[*indice] = raiz->dados;
        (*indice)++;
    }

    copiar_ativas(raiz->dir,
                  vetor,
                  indice);
}

/***********************************************************************
 * COMPARADOR DAS USINAS
 ***********************************************************************/

int comparar_usinas(
        const Usina *a,
        const Usina *b,
        PoliticaDespacho politica)
{
    switch(politica)
    {

        case DESPACHO_ECONOMICO:

            if(a->custo_mwh != b->custo_mwh)
                return (a->custo_mwh < b->custo_mwh) ? -1 : 1;

            if(a->prioridade != b->prioridade)
                return (a->prioridade < b->prioridade) ? -1 : 1;

            if(a->capacidade_disponivel != b->capacidade_disponivel)
                return (a->capacidade_disponivel >
                        b->capacidade_disponivel) ? -1 : 1;

            return 0;

        case DESPACHO_EMERGENCIA:

            if(a->capacidade_disponivel !=
               b->capacidade_disponivel)

                return (a->capacidade_disponivel >
                        b->capacidade_disponivel) ? -1 : 1;

            if(a->custo_mwh != b->custo_mwh)

                return (a->custo_mwh <
                        b->custo_mwh) ? -1 : 1;

            return 0;

        case DESPACHO_ECOLOGICO:
        {
            int pa;
            int pb;

            pa = prioridade_ecologica(a->tipo);
            pb = prioridade_ecologica(b->tipo);

            if(pa != pb)
                return (pa < pb) ? -1 : 1;

            if(a->custo_mwh != b->custo_mwh)
                return (a->custo_mwh < b->custo_mwh) ? -1 : 1;

            return 0;
        }

        case DESPACHO_BALANCEADO:
        {
            float sa;
            float sb;

            sa = calcular_score(*a);
            sb = calcular_score(*b);

            if(sa > sb)
                return -1;

            if(sa < sb)
                return 1;

            return 0;
        }
    }

    return 0;
}

/***********************************************************************
 * EXECUTA O DESPACHO DE ENERGIA
 ***********************************************************************/

ResultadoDespacho executar_despacho(
        NoABB *raiz,
        float demanda,
        PoliticaDespacho politica)
{
    ResultadoDespacho resultado;

    Usina vetor[MAX_USINAS];

    int quantidade;

    int indice;

    int i;

    float restante;

    /* Inicialização */

    memset(&resultado, 0, sizeof(ResultadoDespacho));

    resultado.demanda = demanda;

    resultado.politica = politica;

    obter_data(resultado.data);

    obter_hora(resultado.hora);

    /* Copia somente usinas ativas */

    quantidade = contar_ativas(raiz);

    indice = 0;

    copiar_ativas(raiz,
                  vetor,
                  &indice);

    /* Ordena conforme política */

    quicksort_usinas(
            vetor,
            0,
            quantidade - 1,
            politica);

    restante = demanda;

    for(i = 0;
        i < quantidade && restante > 0;
        i++)
    {
        float energia;

        energia = vetor[i].capacidade_disponivel;

        if(energia > restante)
        {
            energia = restante;
        }

        resultado.itens[resultado.quantidade_itens].codigo_usina =
                vetor[i].codigo;

        resultado.itens[resultado.quantidade_itens].energia_fornecida =
                energia;

        resultado.itens[resultado.quantidade_itens].custo_mwh =
                vetor[i].custo_mwh;

        resultado.itens[resultado.quantidade_itens].custo_total =
                energia * vetor[i].custo_mwh;

        resultado.quantidade_itens++;

        resultado.energia_atendida += energia;

        resultado.custo_total +=
                energia * vetor[i].custo_mwh;

        restante -= energia;
    }

    resultado.energia_nao_atendida = restante;

    if(demanda > 0)
    {
        resultado.percentual_atendido =
            (resultado.energia_atendida / demanda) * 100.0f;
    }

    resultado.usinas_utilizadas =
        resultado.quantidade_itens;

    resultado.sobra_energia = 0;

    resultado.deficit_energia =
        resultado.energia_nao_atendida;

    return resultado;
}


/***********************************************************************
 * ATUALIZA A CAPACIDADE DAS USINAS APÓS O DESPACHO
 ***********************************************************************/

void atualizar_capacidade(NoABB *raiz,
                          ResultadoDespacho resultado)
{
    int i;
    NoABB *no;

    for (i = 0; i < resultado.quantidade_itens; i++)
    {
        no = buscar_abb(raiz,
                        resultado.itens[i].codigo_usina);

        if (no != NULL)
        {
            no->dados.capacidade_disponivel -=
                resultado.itens[i].energia_fornecida;

            if (no->dados.capacidade_disponivel < 0)
            {
                no->dados.capacidade_disponivel = 0;
            }
        }
    }
}

/***********************************************************************
 * ATUALIZA AS ESTATÍSTICAS DAS USINAS
 ***********************************************************************/

void atualizar_estatisticas(NoABB *raiz,
                            ResultadoDespacho resultado)
{
    int i;

    NoABB *no;

    for(i = 0; i < resultado.quantidade_itens; i++)
    {
        no = buscar_abb(
                raiz,
                resultado.itens[i].codigo_usina);

        if(no != NULL)
        {
            no->dados.energia_total +=
                resultado.itens[i].energia_fornecida;

            no->dados.faturamento_total +=
                resultado.itens[i].custo_total;

            no->dados.despachos++;

            no->dados.horas_operacao++;
        }
    }
}

/***********************************************************************
 * IMPRIME O RESULTADO DO DESPACHO
 ***********************************************************************/

void imprimir_despacho(ResultadoDespacho resultado)
{
    int i;

    linha_dupla();

    printf("RESULTADO DO DESPACHO\n");

    linha_dupla();

    printf("Data..................: %s\n",
           resultado.data);

    printf("Hora..................: %s\n",
           resultado.hora);

    printf("Demanda...............: %.2f MW\n",
           resultado.demanda);

    printf("Energia Atendida......: %.2f MW\n",
           resultado.energia_atendida);

    printf("Energia Nao Atendida..: %.2f MW\n",
           resultado.energia_nao_atendida);

    printf("Custo Total...........: R$ %.2f\n",
           resultado.custo_total);

    printf("Usinas Utilizadas.....: %d\n",
           resultado.quantidade_itens);
    
	printf("Politica..............: %s\n",
       politica_para_texto(resultado.politica));

    linha();

    printf("%-8s %-15s %-12s %-15s\n",
           "Codigo",
           "Energia (MW)",
           "Custo (R$/MWh)",
           "Total (R$)");
          
    linha();

    for(i = 0;
        i < resultado.quantidade_itens;
        i++)
    {
        printf("%-8d %-15.2f %-12.2f %-15.2f\n",

               resultado.itens[i].codigo_usina,

               resultado.itens[i].energia_fornecida,

               resultado.itens[i].custo_mwh,

               resultado.itens[i].custo_total);
    }

    linha_dupla();
}
