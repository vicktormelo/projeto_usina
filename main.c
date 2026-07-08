/***********************************************************************
 * Projeto Final - Estrutura de Dados
 *
 * Sistema Inteligente de Gerenciamento
 * e Despacho de Energia (SIGDE)
 *
 * Arquivo: main.c
 *
 * Autor: Vicktor Melo
 *
 * Programa principal.
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "tipos.h"
#include "util.h"
#include "usina.h"
#include "despacho.h"
#include "persistencia.h"
#include "relatorios.h"

/***********************************************************************
 * VARIÁVEIS GLOBAIS
 ***********************************************************************/

NoABB *raiz = NULL;

/***********************************************************************
 * PROTÓTIPOS DAS FUNÇÕES DO MENU
 ***********************************************************************/

void menu_principal(void);

void menu_cadastro(void);

void menu_relatorios(void);

void menu_despacho(void);

void finalizar_sistema(void);

/***********************************************************************
 * FUNÇÃO PRINCIPAL
 ***********************************************************************/

int main(void)
{
    int opcao;

    inicializar_banco();

    carregar_usinas(&raiz);

    do
    {
        menu_principal();

        opcao = ler_inteiro("\nOpcao: ");

        switch(opcao)
        {

            case 1:

                menu_cadastro();

                break;

            case 2:

                menu_despacho();

                break;

            case 3:

                menu_relatorios();

                break;

            case 4:

    			finalizar_sistema();

    			break;

            default:

                printf("\nOpcao invalida.\n");

        }

    } while(opcao != 4);

    raiz = NULL;

return 0;
}

/***********************************************************************
 * MENU PRINCIPAL
 ***********************************************************************/

void menu_principal(void)
{
    limpar_tela();

    mostrar_cabecalho(
        "SIGDE - Sistema Inteligente de Gerenciamento e Despacho de Energia");

    printf("1 - Cadastro de Usinas\n");

    printf("2 - Despacho de Energia\n");

    printf("3 - Relatorios\n");

    printf("4 - Salvar e Sair\n");

    linha_dupla();
}

/***********************************************************************
 * MENU DE CADASTRO
 ***********************************************************************/

void menu_cadastro(void)
{
    int opcao;
    int codigo;
    Usina usina;

    do
    {
        limpar_tela();

        mostrar_cabecalho("CADASTRO DE USINAS");

        printf("1 - Cadastrar usina\n");
        printf("2 - Editar usina\n");
        printf("3 - Ativar usina\n");
        printf("4 - Desativar usina\n");
        printf("5 - Listar usinas\n");
        printf("0 - Voltar\n");

        linha_dupla();

        opcao = ler_inteiro("\nOpcao: ");

        switch(opcao)
        {

            case 1:

                usina = cadastrar_usina(raiz);

                inserir_abb(&raiz, usina);

                printf("\nUsina cadastrada com sucesso!\n");

                pausar();

                break;

            case 2:

                editar_usina(raiz);

                pausar();

                break;

            case 3:

                codigo = ler_inteiro("Codigo da usina: ");

                ativar_usina(raiz, codigo);

                pausar();

                break;

            case 4:

                codigo = ler_inteiro("Codigo da usina: ");

                desativar_usina(raiz, codigo);

                pausar();

                break;

            case 5:

                limpar_tela();

                mostrar_cabecalho("LISTA DE USINAS");

                listar_usinas(raiz);

                pausar();

                break;

            case 0:

                break;

            default:

                printf("\nOpcao invalida.\n");

                pausar();

        }

    } while(opcao != 0);
}

/***********************************************************************
 * MENU DE RELATÓRIOS
 ***********************************************************************/

void menu_relatorios(void)
{
    int opcao;

    do
    {
        limpar_tela();

        mostrar_cabecalho("RELATORIOS");

        printf("1 - Relatorio de Usinas\n");

        printf("2 - Estatisticas\n");

        printf("3 - Capacidade Disponivel\n");

        printf("4 - Custos\n");

        printf("0 - Voltar\n");

        linha_dupla();

        opcao = ler_inteiro("\nOpcao: ");

        switch(opcao)
        {

            case 1:

                relatorio_usinas(raiz);

                pausar();

                break;

            case 2:

                relatorio_estatisticas(raiz);

                pausar();

                break;

            case 3:

                relatorio_capacidade(raiz);

                pausar();

                break;

            case 4:

                relatorio_custos(raiz);

                pausar();

                break;

            case 0:

                break;

            default:

                printf("\nOpcao invalida.\n");

                pausar();

        }

    } while(opcao != 0);
}

/***********************************************************************
 * MENU DE DESPACHO
 ***********************************************************************/

void menu_despacho(void)
{
    float demanda;

    ResultadoDespacho resultado;

    limpar_tela();

    mostrar_cabecalho("DESPACHO DE ENERGIA");

    if (raiz == NULL)
    {
        printf("\nNao existem usinas cadastradas.\n");

        pausar();

        return;
    }

    demanda = ler_float("Informe a demanda (MW): ");

    //resultado = executar_despacho(raiz, demanda);
    
    PoliticaDespacho politica;

politica = escolher_politica();

resultado =
    executar_despacho(
        raiz,
        demanda,
        politica);

    imprimir_despacho(resultado);

    atualizar_capacidade(raiz, resultado);

    atualizar_estatisticas(raiz, resultado);

    registrar_historico(resultado.demanda,
                         resultado.energia_atendida,
                         resultado.custo_total);

    gerar_ticket(resultado.demanda,
                 resultado.energia_atendida,
                 resultado.custo_total);

    salvar_usinas(raiz);

    pausar();
}


/*
 * Salva todos os dados antes de encerrar.
 */
void finalizar_sistema(void)
{
    printf("\nSalvando banco de dados...\n");

    salvar_usinas(raiz);

    liberar_abb(raiz);
    
    raiz = NULL;

    printf("\nSistema encerrado com sucesso.\n");
}
