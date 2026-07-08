/***********************************************************************
 * SIGDE - Sistema Inteligente de Gerenciamento e Despacho de Energia
 *
 * Disciplina : Estrutura de Dados
 * Linguagem  : C
 *
 * Arquivo    : config.h
 * Módulo     : Configuração Global
 * Versão     : 3.0.0
 *
 * Autor      : Vicktor Melo
 *
 * Descrição:
 * Constantes globais utilizadas por todo o sistema.
 ***********************************************************************/

#ifndef CONFIG_H
#define CONFIG_H

/***********************************************************************
 * IDENTIFICAÇÃO DO SISTEMA
 ***********************************************************************/

#define NOME_SISTEMA           "SIGDE"
#define VERSAO_SISTEMA         "3.0.0"

/***********************************************************************
 * TAMANHO DAS STRINGS
 ***********************************************************************/

#define MAX_STRING             100
#define MAX_NOME               50
#define MAX_TIPO               30
#define MAX_REGIAO             30
#define MAX_DATA               25
#define MAX_HORA               10
#define MAX_DATA_HORA          30

/***********************************************************************
 * LIMITES DO SISTEMA
 ***********************************************************************/

#define MAX_USINAS             1000
#define MAX_DESPACHOS          10000
#define MAX_ITENS_DESPACHO     100
#define MAX_LOG                200

/***********************************************************************
 * ARQUIVOS
 ***********************************************************************/

#define ARQ_USINAS             "dados/usinas.txt"
#define ARQ_HISTORICO          "dados/historico.txt"
#define ARQ_MANUTENCAO         "dados/manutencao.txt"
#define ARQ_CONFIG             "dados/configuracao.txt"

#define ARQ_LOG                "logs/sistema.log"

/***********************************************************************
 * DIRETÓRIOS
 ***********************************************************************/

#define DIR_DADOS              "dados/"
#define DIR_LOGS               "logs/"
#define DIR_TICKETS            "tickets/"

/***********************************************************************
 * VALORES PADRÃO
 ***********************************************************************/

#define RESERVATORIO_CHEIO     100.0f
#define RESERVATORIO_VAZIO       0.0f

#define PRIORIDADE_MAXIMA        1
#define PRIORIDADE_MINIMA        5

/***********************************************************************
 * STATUS
 ***********************************************************************/

#define SUCESSO                 1
#define ERRO                    0

#endif
