/***********************************************************************
 * SIGDE - Sistema Inteligente de Gerenciamento e Despacho de Energia
 *
 * Disciplina : Estrutura de Dados
 * Linguagem  : C
 *
 * Arquivo    : usina.h
 * Módulo     : Gerenciamento de Usinas
 * Versão     : 3.0.0
 *
 * Autor      : Vicktor Melo
 *
 * Descrição:
 * Define a estrutura da usina, da árvore binária de busca (ABB)
 * e os protótipos das funções responsáveis pelo gerenciamento
 * das usinas.
 ***********************************************************************/

#ifndef USINA_H
#define USINA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "tipos.h"
#include "util.h"

/***********************************************************************
 * ESTRUTURA DA USINA
 ***********************************************************************/

typedef struct
{
    /***********************************************************
     * IDENTIFICAÇÃO
     ***********************************************************/

    int codigo;

    TipoUsina tipo;

    Regiao regiao;

    StatusUsina status;

    /***********************************************************
     * PRODUÇÃO
     ***********************************************************/

    float potencia_instalada;

    float capacidade_disponivel;

    float reservatorio;

    float custo_mwh;

    float producao_diaria;

    float producao_mensal;

    /***********************************************************
     * ESTATÍSTICAS
     ***********************************************************/

    float energia_total;

    float faturamento_total;

    int despachos;

    int horas_operacao;

    /***********************************************************
     * GESTÃO
     ***********************************************************/

    Prioridade prioridade;

    char ultima_manutencao[MAX_DATA];

} Usina;

/***********************************************************************
 * ÁRVORE BINÁRIA DE BUSCA
 ***********************************************************************/

typedef struct NoABB
{
    Usina dados;

    struct NoABB *esq;

    struct NoABB *dir;

} NoABB;

/***********************************************************************
 * FUNÇÕES DA ABB
 ***********************************************************************/

NoABB *criar_no(Usina usina);

void inserir_abb(NoABB **raiz,
                 Usina usina);

NoABB *buscar_abb(NoABB *raiz,
                  int codigo);

void listar_usinas(NoABB *raiz);

void liberar_abb(NoABB *raiz);

/***********************************************************************
 * CADASTRO
 ***********************************************************************/

Usina cadastrar_usina(NoABB *raiz);

void editar_usina(NoABB *raiz);

void ativar_usina(NoABB *raiz,
                  int codigo);

void desativar_usina(NoABB *raiz,
                     int codigo);

/***********************************************************************
 * CONSULTAS
 ***********************************************************************/

int quantidade_usinas(NoABB *raiz);

int quantidade_ativas(NoABB *raiz);

float potencia_total(NoABB *raiz);

float capacidade_total_disponivel(NoABB *raiz);

/***********************************************************************
 * IMPRESSÃO
 ***********************************************************************/

void imprimir_usina(Usina usina);

void imprimir_resumo(Usina usina);

/***********************************************************************
 * VALIDAÇÕES
 ***********************************************************************/

int codigo_existe(NoABB *raiz,
                  int codigo);

/***********************************************************************
 * MANUTENÇÃO
 ***********************************************************************/

void atualizar_manutencao(NoABB *raiz,
                          int codigo);

void restaurar_capacidade(NoABB *raiz);

/***********************************************************************
 * ORDENAÇÃO
 ***********************************************************************/

/*
 * Utilizada pelos relatórios.
 */

void copiar_usinas(NoABB *raiz,
                   Usina vetor[],
                   int *indice);

#endif
