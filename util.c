/***********************************************************************
 * SIGDE - Sistema Inteligente de Gerenciamento e Despacho de Energia
 *
 * Disciplina : Estrutura de Dados
 * Linguagem  : C
 *
 * Módulo     : Utilitários
 * Arquivo    : util.c
 * Versão     : 3.0.0
 *
 * Autor      : Vicktor Melo
 ***********************************************************************/

#include "util.h"

/***********************************************************************
 * LIMPEZA DE TELA
 ***********************************************************************/

void limpar_tela(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/***********************************************************************
 * PAUSA
 ***********************************************************************/

void pausar(void)
{
    printf("\nPressione ENTER para continuar...");
    getchar();
}

/***********************************************************************
 * LINHAS DECORATIVAS
 ***********************************************************************/

void linha(void)
{
    printf("------------------------------------------------------------\n");
}

void linha_dupla(void)
{
    printf("============================================================\n");
}

/***********************************************************************
 * CABEÇALHO PADRÃO
 ***********************************************************************/

void mostrar_cabecalho(const char *titulo)
{
    linha_dupla();

    printf("SIGDE 3.0\n");

    linha();

    printf("%s\n", titulo);

    linha_dupla();
}

/***********************************************************************
 * RODAPÉ
 ***********************************************************************/

void mostrar_rodape(void)
{
    linha_dupla();
}

/***********************************************************************
 * LEITURA DE STRING
 ***********************************************************************/

void ler_string(const char *mensagem,
                char texto[],
                int tamanho)
{
    printf("%s", mensagem);

    fgets(texto, tamanho, stdin);

    texto[strcspn(texto, "\n")] = '\0';
}

/***********************************************************************
 * LEITURA DE INTEIRO
 ***********************************************************************/

int ler_inteiro(const char *mensagem)
{
    int valor;

    printf("%s", mensagem);

    scanf("%d", &valor);

    getchar();

    return valor;
}

/***********************************************************************
 * LEITURA DE FLOAT
 ***********************************************************************/

float ler_float(const char *mensagem)
{
    float valor;

    printf("%s", mensagem);

    scanf("%f", &valor);

    getchar();

    return valor;
}

/***********************************************************************
 * CONFIRMAÇÃO
 ***********************************************************************/

int confirmar(const char *mensagem)
{
    char resposta;

    printf("%s (S/N): ", mensagem);

    scanf(" %c", &resposta);
    getchar();

    if (resposta == 'S' || resposta == 's')
    {
        return 1;
    }

    return 0;
}

/***********************************************************************
 * DATA E HORA
 ***********************************************************************/

/*
 * Obtém a data atual.
 */
void obter_data(char data[])
{
    time_t agora;
    struct tm *info;

    time(&agora);

    info = localtime(&agora);

    strftime(data,
             MAX_DATA,
             "%d/%m/%Y",
             info);
}

/*
 * Obtém o horário atual.
 */
void obter_hora(char hora[])
{
    time_t agora;
    struct tm *info;

    time(&agora);

    info = localtime(&agora);

    strftime(hora,
             MAX_DATA,
             "%H:%M:%S",
             info);
}

/*
 * Obtém data e hora.
 */
void obter_data_hora(char datahora[])
{
    time_t agora;
    struct tm *info;

    time(&agora);

    info = localtime(&agora);

    strftime(datahora,
             MAX_DATA,
             "%d/%m/%Y %H:%M:%S",
             info);
}

/***********************************************************************
 * REGISTRO DE LOG
 ***********************************************************************/

void registrar_log(const char *mensagem)
{
    FILE *arquivo;

    char datahora[MAX_DATA];

    obter_data_hora(datahora);

    arquivo = fopen("logs/sistema.log", "a");

    if (arquivo == NULL)
    {
        return;
    }

    fprintf(arquivo,
            "[%s] %s\n",
            datahora,
            mensagem);

    fclose(arquivo);
}

/***********************************************************************
 * GERADOR DE IDENTIFICADOR
 ***********************************************************************/

int gerar_id(void)
{
    static int ultimo_id = 0;

    ultimo_id++;

    return ultimo_id;
}

/***********************************************************************
 * VALIDAÇÕES
 ***********************************************************************/

int validar_intervalo_int(int valor,
                          int minimo,
                          int maximo)
{
    if (valor < minimo)
    {
        return 0;
    }

    if (valor > maximo)
    {
        return 0;
    }

    return 1;
}

int validar_intervalo_float(float valor,
                            float minimo,
                            float maximo)
{
    if (valor < minimo)
    {
        return 0;
    }

    if (valor > maximo)
    {
        return 0;
    }

    return 1;
}
