/***********************************************************************
 * Projeto Final - Estrutura de Dados
 *
 * Projeto 4 - Otimizador de Despacho de Carga
 * Versão 2.0
 *
 * Arquivo: main.c
 ***********************************************************************/

#include "usina.h"

int main(void)
{
    NoABB *raiz = NULL;

    int opcao;
    int codigo;
    float demanda;

    Usina nova;
    NoABB *resultado;

    do
    {
        limpar_tela();

        menu();

        scanf("%d", &opcao);
        getchar();

        switch(opcao)
        {
            case 1:

                limpar_tela();

                nova = cadastrar_usina();

                inserir_abb(&raiz, nova);

                pausar();

                break;

            case 2:

                limpar_tela();

                printf("\nDigite o codigo da usina: ");
                scanf("%d", &codigo);
                getchar();

                resultado = buscar_abb(raiz, codigo);

                if(resultado == NULL)
                {
                    printf("\nUsina nao encontrada.\n");
                }
                else
                {
                    imprimir_usina(resultado->dados);
                }

                pausar();

                break;

            case 3:

                limpar_tela();

                if(raiz == NULL)
                {
                    printf("\nNenhuma usina cadastrada.\n");
                }
                else
                {
                    listar_usinas(raiz);
                }

                pausar();

                break;

            case 4:

                limpar_tela();

                printf("Codigo da usina: ");
                scanf("%d", &codigo);
                getchar();

                ativar_usina(raiz, codigo);

                pausar();

                break;

            case 5:

                limpar_tela();

                printf("Codigo da usina: ");
                scanf("%d", &codigo);
                getchar();

                desativar_usina(raiz, codigo);

                pausar();

                break;

            case 6:

                limpar_tela();

                mostrar_estatisticas(raiz);

                pausar();

                break;

            case 7:

                limpar_tela();

                printf("Informe a demanda (MW): ");
                scanf("%f", &demanda);
                getchar();

                despachar_carga(raiz, demanda);

                pausar();

                break;

            case 0:

                printf("\nEncerrando o sistema...\n");

                break;

            default:

                printf("\nOpcao invalida.\n");

                pausar();

                break;
        }

    } while(opcao != 0);

    liberar_abb(raiz);

    return 0;
}