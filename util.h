/***********************************************************************
 * SIGDE - Sistema Inteligente de Gerenciamento e Despacho de Energia
 *
 * Disciplina : Estrutura de Dados
 * Linguagem  : C
 *
 * Módulo     : Utilitários
 * Arquivo    : util.h
 * Versão     : 3.0.0
 *
 * Autor      : Vicktor Melo
 *
 * Descrição:
 * Biblioteca de funções auxiliares utilizadas por todo o sistema.
 ***********************************************************************/

#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/***********************************************************************
 * CONSTANTES
 ***********************************************************************/

#define MAX_STRING     100
//#define MAX_DATA       25
#define MAX_LOG        200

/***********************************************************************
 * ENTRADA DE DADOS
 ***********************************************************************/

/*
 * Lê um número inteiro.
 */
int ler_inteiro(const char *mensagem);

/*
 * Lê um número real.
 */
float ler_float(const char *mensagem);

/*
 * Lê uma string.
 */
void ler_string(const char *mensagem,
                char texto[],
                int tamanho);

/*
 * Pergunta Sim ou Não.
 *
 * Retorna:
 * 1 = Sim
 * 0 = Não
 */
int confirmar(const char *mensagem);

/***********************************************************************
 * TELA
 ***********************************************************************/

/*
 * Limpa a tela.
 */
void limpar_tela(void);

/*
 * Pausa a execução.
 */
void pausar(void);

/*
 * Exibe um cabeçalho padronizado.
 */
void mostrar_cabecalho(const char *titulo);

/*
 * Exibe um rodapé.
 */
void mostrar_rodape(void);

/***********************************************************************
 * DATA E HORA
 ***********************************************************************/

/*
 * Obtém a data atual.
 *
 * Exemplo:
 * 07/07/2026
 */
void obter_data(char data[]);

/*
 * Obtém o horário atual.
 *
 * Exemplo:
 * 21:45:10
 */
void obter_hora(char hora[]);

/*
 * Obtém data e hora.
 *
 * Exemplo:
 * 07/07/2026 21:45:10
 */
void obter_data_hora(char datahora[]);

/***********************************************************************
 * LOG
 ***********************************************************************/

/*
 * Registra uma mensagem no arquivo de log.
 */
void registrar_log(const char *mensagem);

/***********************************************************************
 * IDENTIFICADORES
 ***********************************************************************/

/*
 * Gera um novo ID sequencial.
 */
int gerar_id(void);

/***********************************************************************
 * VALIDAÇÕES
 ***********************************************************************/

/*
 * Verifica se um inteiro está dentro do intervalo.
 */
int validar_intervalo_int(int valor,
                          int minimo,
                          int maximo);

/*
 * Verifica se um float está dentro do intervalo.
 */
int validar_intervalo_float(float valor,
                            float minimo,
                            float maximo);

/***********************************************************************
 * FORMATAÇÃO
 ***********************************************************************/

/*
 * Exibe uma linha separadora.
 */
void linha(void);

/*
 * Exibe uma linha dupla.
 */
void linha_dupla(void);

#endif
