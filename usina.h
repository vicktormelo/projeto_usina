/******************************************************************
 * Projeto Final - Estrutura de Dados
 *
 * Projeto 4 - Otimizador de Despacho de Carga
 * Versão 2.0
 *
 * Arquivo: usina.h
 *
 * Autor: Vicktor Melo
 *
 * Descrição:
 * Biblioteca principal contendo as estruturas de dados
 * e os protótipos das funções utilizadas no sistema.
 **********************************************************************/

#ifndef USINA_H
#define USINA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***********************************************************************
 * Constantes
 ***********************************************************************/

#define ATIVA       1
#define INATIVA     0

#define MAX_TIPO   30

/***********************************************************************
 * Estrutura da Usina
 ***********************************************************************/

typedef struct
{
    int codigo;
    char tipo[MAX_TIPO];
    float capacidade_mw;
    float custo_mwh;
    int status;

} Usina;

/***********************************************************************
 * Nó da Árvore Binária de Busca
 ***********************************************************************/

typedef struct NoABB
{
    Usina dados;

    struct NoABB *esq;
    struct NoABB *dir;

} NoABB;

/***********************************************************************
 *====================== ÁRVORE BINÁRIA ================================
 ***********************************************************************/

/* Cria um novo nó */
NoABB *criar_no(Usina u);

/* Insere uma usina */
void inserir_abb(NoABB **raiz, Usina u);

/* Busca por código */
NoABB *buscar_abb(NoABB *raiz, int codigo);

/* Libera toda a árvore */
void liberar_abb(NoABB *raiz);

/***********************************************************************
 *====================== LISTAGEM ======================================
 ***********************************************************************/

/* Lista todas as usinas em ordem crescente de código */
void listar_usinas(NoABB *raiz);

/* Imprime uma única usina */
void imprimir_usina(Usina u);

/***********************************************************************
 *====================== CADASTRO ======================================
 ***********************************************************************/

/* Lê os dados digitados pelo usuário */
Usina cadastrar_usina(void);

/* Ativa uma usina */
void ativar_usina(NoABB *raiz, int codigo);

/* Desativa uma usina */
void desativar_usina(NoABB *raiz, int codigo);

/***********************************************************************
 *====================== ESTATÍSTICAS ==================================
 ***********************************************************************/

/* Conta quantas usinas existem */
int contar_total(NoABB *raiz);

/* Conta apenas usinas ativas */
int contar_ativas(NoABB *raiz);

/* Conta apenas usinas inativas */
int contar_inativas(NoABB *raiz);

/* Soma toda a capacidade instalada */
float capacidade_total(NoABB *raiz);

/* Soma apenas a capacidade disponível */
float capacidade_ativa(NoABB *raiz);

/* Soma o custo das usinas */
float soma_custos(NoABB *raiz);

/* Mostra estatísticas */
void mostrar_estatisticas(NoABB *raiz);

/***********************************************************************
 *====================== VETORES =======================================
 ***********************************************************************/

/* Copia as usinas ativas para um vetor */
void copiar_ativas_para_vetor(NoABB *raiz,
                              Usina vetor[],
                              int *indice);

/***********************************************************************
 *====================== ORDENAÇÃO =====================================
 ***********************************************************************/

/* Quicksort */
void quicksort_usinas(Usina vetor[],
                      int inicio,
                      int fim);

/***********************************************************************
 *====================== DESPACHO ======================================
 ***********************************************************************/

/* Realiza o despacho de energia */
void despachar_carga(NoABB *raiz,
                     float demanda);

/***********************************************************************
 *====================== MENU ==========================================
 ***********************************************************************/

/* Exibe o menu principal */
void menu(void);

/* Aguarda o usuário pressionar ENTER */
void pausar(void);

/* Limpa a tela */
void limpar_tela(void);

#endif*
 
 /***********************************************************************
 * Projeto Final - Estrutura de Dados
 *
 * Projeto 4 - Otimizador de Despacho de Carga
 *
 * Arquivo: usina.h
 *
 * Descrição:
 * Declaração das estruturas de dados e protótipos das funções
 * utilizadas no projeto.
 ********************************************************************/

#ifndef USINA_H
#define USINA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/********************************************************************
 * Estrutura que representa uma usina geradora de energia
 ********************************************************************/
typedef struct
{
    int codigo;
    char tipo[30];
    float capacidade_mw;
    float custo_mwh;
    int status;          /* 1 = Ativa | 0 = Inativa */

} Usina;


/********************************************************************
 * Nó da Árvore Binária de Busca
 ********************************************************************/
typedef struct NoABB
{
    Usina dados;

    struct NoABB *esq;
    struct NoABB *dir;

} NoABB;


/********************************************************************
 * Funções da Árvore Binária de Busca
 ********************************************************************/

/* Cria um novo nó */
NoABB *criar_no(Usina u);

/* Insere uma usina na ABB */
void inserir_abb(NoABB **raiz, Usina u);

/* Busca uma usina pelo código */
NoABB *buscar_abb(NoABB *raiz, int codigo);

/* Libera toda a memória da ABB */
void liberar_abb(NoABB *raiz);


/********************************************************************
 * Funções auxiliares
 ********************************************************************/

/* Conta quantas usinas estão ativas */
int contar_ativas(NoABB *raiz);

/* Copia as usinas ativas para um vetor */
void copiar_ativas_para_vetor(NoABB *raiz,
                              Usina *vetor,
                              int *indice);


/********************************************************************
 * Ordenação
 ********************************************************************/

/* Ordena o vetor de usinas pelo menor custo */
void quicksort_usinas(Usina *vetor,
                      int inicio,
                      int fim);


/********************************************************************
 * Função principal do despacho
 ********************************************************************/

/* Realiza o despacho de energia */
void despachar_carga(NoABB *raiz,
                     float demanda_solicitada);

#endif
