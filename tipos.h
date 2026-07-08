/***********************************************************************
 * SIGDE - Sistema Inteligente de Gerenciamento e Despacho de Energia
 *
 * Disciplina : Estrutura de Dados
 * Linguagem  : C
 *
 * Arquivo    : tipos.h
 * Módulo     : Tipos Globais
 * Versão     : 3.0.0
 *
 * Autor      : Vicktor Melo
 *
 * Descrição:
 * Enumerações e estruturas compartilhadas por todo o sistema.
 ***********************************************************************/

#ifndef TIPOS_H
#define TIPOS_H

#include "config.h"

/***********************************************************************
 * ENUMERAÇÕES
 ***********************************************************************/

/*
 * Tipos de usinas.
 */
typedef enum
{
    HIDRELETRICA = 1,
    TERMOELETRICA,
    EOLICA,
    SOLAR,
    BIOMASSA

} TipoUsina;

/*
 * Regiões do Brasil.
 */
typedef enum
{
    SUL = 1,
    SUDESTE,
    CENTRO_OESTE,
    NORDESTE,
    NORTE

} Regiao;

/*
 * Prioridade operacional.
 */
typedef enum
{
    PRIORIDADE_MUITO_ALTA = 1,
    PRIORIDADE_ALTA,
    PRIORIDADE_MEDIA,
    PRIORIDADE_BAIXA,
    PRIORIDADE_MUITO_BAIXA

} Prioridade;

/*
 * Situação da usina.
 */
typedef enum
{
    INATIVA = 0,
    ATIVA = 1

} StatusUsina;

/***********************************************************************
 * ESTRUTURA DO SISTEMA
 ***********************************************************************/

typedef struct
{
    int ultimo_ticket;

    int ultimo_despacho;

    int quantidade_usinas;

    float demanda_total;

    float energia_total;

    float faturamento_total;

} Sistema;

/***********************************************************************
 * ITEM DE DESPACHO
 ***********************************************************************/

typedef struct
{
    int codigo_usina;

    float energia_fornecida;

    float custo_mwh;

    float custo_total;

} ItemDespacho;

/***********************************************************************
 * POLÍTICAS DE DESPACHO
 ***********************************************************************/

typedef enum
{
    DESPACHO_ECONOMICO = 1,
    DESPACHO_EMERGENCIA,
    DESPACHO_ECOLOGICO,
    DESPACHO_BALANCEADO

} PoliticaDespacho;

/***********************************************************************
 * RESULTADO DO DESPACHO
 ***********************************************************************/

typedef struct
{
    int id_despacho;

    char data[MAX_DATA];

    char hora[MAX_HORA];

    PoliticaDespacho politica;

    float demanda;

    float energia_atendida;

    float energia_nao_atendida;

    float percentual_atendido;

    float sobra_energia;

    float deficit_energia;

    float custo_total;

    int usinas_utilizadas;

    int quantidade_itens;

    ItemDespacho itens[MAX_ITENS_DESPACHO];

} ResultadoDespacho;

/***********************************************************************
 * PROTÓTIPOS DE CONVERSÃO
 ***********************************************************************/

/* Tipo de Usina */

const char *tipo_para_texto(TipoUsina tipo);

TipoUsina texto_para_tipo(const char *texto);

/* Região */

const char *regiao_para_texto(Regiao regiao);

Regiao texto_para_regiao(const char *texto);

/* Prioridade */

const char *prioridade_para_texto(Prioridade prioridade);

/* Status */

const char *status_para_texto(StatusUsina status);

#endif
