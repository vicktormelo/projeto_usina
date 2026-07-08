/***********************************************************************
 * Projeto Final - Estrutura de Dados
 *
 * Sistema Inteligente de Gerenciamento
 * e Despacho de Energia (SIGDE)
 *
 * Versão 3.0
 *
 * Arquivo: persistencia.h
 *
 * Responsável pelas operações de leitura e gravação
 * dos arquivos texto utilizados como banco de dados.
 ***********************************************************************/

#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include "usina.h"

/***********************************************************************
 * Arquivos utilizados pelo sistema
 ***********************************************************************/

#define ARQUIVO_USINAS      "dados/usinas.txt"

#define ARQUIVO_HISTORICO   "dados/historico.txt"

#define PASTA_TICKETS       "dados/tickets/"

/***********************************************************************
 * Banco de Dados
 ***********************************************************************/

/* Carrega todas as usinas do arquivo texto para a ABB */
void carregar_usinas(NoABB **raiz);

/* Salva todas as usinas da ABB no arquivo texto */
void salvar_usinas(NoABB *raiz);

/***********************************************************************
 * Funções auxiliares
 ***********************************************************************/

/* Percorre a ABB gravando os registros */
//void gravar_em_arquivo(NoABB *raiz, FILE *arquivo);

/***********************************************************************
 * Histórico
 ***********************************************************************/

/* Registra um despacho realizado */
void registrar_historico(float demanda,
                         float energia_fornecida,
                         float custo_total);

/***********************************************************************
 * Tickets
 ***********************************************************************/

/* Gera um arquivo TXT contendo o resumo do despacho */
void gerar_ticket(float demanda,
                  float energia_fornecida,
                  float custo_total);

/***********************************************************************
 * Utilidades
 ***********************************************************************/

/* Verifica se os arquivos necessários existem */
void inicializar_banco(void);

#endif


