/*******************************************************************
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