/***********************************************************************
 * Projeto Final - Estrutura de Dados
 *
 * Sistema Inteligente de Gerenciamento
 * e Despacho de Energia (SIGDE)
 *
 * Arquivo: relatorios.h
 ***********************************************************************/

#ifndef RELATORIOS_H
#define RELATORIOS_H

#include "usina.h"
#include "despacho.h"

/***********************************************************************
 * RELATÓRIOS
 ***********************************************************************/

/* Lista todas as usinas cadastradas */
void relatorio_usinas(NoABB *raiz);

/* Exibe informações gerais do sistema */
void relatorio_estatisticas(NoABB *raiz);

/* Mostra as usinas disponíveis para despacho */
void relatorio_capacidade(NoABB *raiz);

/* Lista os custos das usinas */
void relatorio_custos(NoABB *raiz);



#endif
