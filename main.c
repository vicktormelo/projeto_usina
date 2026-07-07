/*******************************************************************
 * Projeto Final - Estrutura de Dados
 *
 * Projeto 4 - Otimizador de Despacho de Carga
 *
 * Arquivo: main.c
 *
 * Descrição:
 * Programa principal responsável por cadastrar as usinas,
 * construir a Árvore Binária de Busca e executar o despacho
 * de energia.
 ********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "usina.h"

int main()
{
    /* Ponteiro para a raiz da árvore */
    NoABB *raiz = NULL;

    /* Cadastro das usinas */
    Usina u1 = {101, "Hidreletrica", 300.0, 45.50, 1};
    Usina u2 = {55,  "Termoeletrica", 150.0, 120.00, 1};
    Usina u3 = {202, "Eolica", 80.0, 30.00, 1};
    Usina u4 = {12,  "Solar", 50.0, 25.00, 0};
    Usina u5 = {88,  "Biomassa", 90.0, 60.00, 1};

    /* Inserção das usinas na árvore */
    inserir_abb(&raiz, u1);
    inserir_abb(&raiz, u2);
    inserir_abb(&raiz, u3);
    inserir_abb(&raiz, u4);
    inserir_abb(&raiz, u5);

    printf("==========================================\n");
    printf(" OTIMIZADOR DE DESPACHO DE CARGA\n");
    printf("==========================================\n\n");

    /* Demanda solicitada */
    float demanda = 400.0;

    printf("Demanda solicitada: %.2f MW\n\n", demanda);

    /* Executa o despacho */
    despachar_carga(raiz, demanda);

    /* Libera toda a memória da árvore */
    liberar_abb(raiz);

    return 0;
}