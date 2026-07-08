/***********************************************************************
 * SIGDE - Sistema Inteligente de Gerenciamento e Despacho de Energia
 *
 * Arquivo    : despacho.h
 * Módulo     : Algoritmo de Despacho
 * Versão     : 3.0.0
 *
 * Autor      : Vicktor Melo
 ***********************************************************************/

#ifndef DESPACHO_H
#define DESPACHO_H

#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "tipos.h"
#include "util.h"
#include "usina.h"

/***********************************************************************
 * ORDENAÇÃO
 ***********************************************************************/

/*
 * Ordena as usinas pelo menor custo de geração.
 */
void quicksort_usinas(Usina vetor[],
                      int inicio,
                      int fim,
					  PoliticaDespacho politica);

/*
 * Particionamento do QuickSort.
 */
int particionar(Usina vetor[],
                int inicio,
                int fim,
				PoliticaDespacho politica);

/***********************************************************************
 * DESPACHO
 ***********************************************************************/

/*
 * Executa o algoritmo guloso de despacho.
 */
ResultadoDespacho executar_despacho(
        NoABB *raiz,
        float demanda,
        PoliticaDespacho politica);

/***********************************************************************
 * ATUALIZAÇÃO
 ***********************************************************************/

/*
 * Atualiza a capacidade disponível das usinas
 * após um despacho.
 */
void atualizar_capacidade(
        NoABB *raiz,
        ResultadoDespacho resultado);

/*
 * Atualiza estatísticas da usina.
 */
void atualizar_estatisticas(
        NoABB *raiz,
        ResultadoDespacho resultado);

/***********************************************************************
 * RELATÓRIOS
 ***********************************************************************/

/*
 * Exibe o resultado do despacho.
 */
void imprimir_despacho(
        ResultadoDespacho resultado);

/***********************************************************************
 * APOIO
 ***********************************************************************/

/*
 * Conta apenas usinas ativas.
 */
int contar_ativas(NoABB *raiz);

/*
 * Copia apenas usinas ativas para um vetor.
 */
void copiar_ativas(NoABB *raiz,
                   Usina vetor[],
                   int *indice);

/***********************************************************************
 * COMPARAÇÃO
 ***********************************************************************/

/*
 * Retorna:
 * < 0 -> a vem antes de b
 * = 0 -> iguais
 * > 0 -> b vem antes de a
 */
                    
/***********************************************************************
 * POLÍTICAS
 ***********************************************************************/

PoliticaDespacho escolher_politica(void);

const char *politica_para_texto(
            PoliticaDespacho politica);

int comparar_usinas(
        const Usina *a,
        const Usina *b,
        PoliticaDespacho politica);

#endif
