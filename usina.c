/***********************************************************************
 * SIGDE - Sistema Inteligente de Gerenciamento e Despacho de Energia
 *
 * Arquivo : usina.c
 * Módulo  : Gerenciamento das Usinas
 * Versão  : 3.0.0
 ***********************************************************************/

#include "usina.h"

static TipoUsina escolher_tipo(void);
static Regiao escolher_regiao(void);
static Prioridade escolher_prioridade(void);

/***********************************************************************
 * CONVERSÃO DOS ENUMS
 ***********************************************************************/

const char *tipo_para_texto(TipoUsina tipo)
{
    switch (tipo)
    {
        case HIDRELETRICA:
            return "Hidreletrica";

        case TERMOELETRICA:
            return "Termoeletrica";

        case EOLICA:
            return "Eolica";

        case SOLAR:
            return "Solar";

        case BIOMASSA:
            return "Biomassa";

        default:
            return "Desconhecido";
    }
}

const char *regiao_para_texto(Regiao regiao)
{
    switch (regiao)
    {
        case SUL:
            return "Sul";

        case SUDESTE:
            return "Sudeste";

        case CENTRO_OESTE:
            return "Centro-Oeste";

        case NORDESTE:
            return "Nordeste";

        case NORTE:
            return "Norte";

        default:
            return "Desconhecida";
    }
}

const char *prioridade_para_texto(Prioridade prioridade)
{
    switch (prioridade)
    {
        case PRIORIDADE_MUITO_ALTA:
            return "Muito Alta";

        case PRIORIDADE_ALTA:
            return "Alta";

        case PRIORIDADE_MEDIA:
            return "Media";

        case PRIORIDADE_BAIXA:
            return "Baixa";

        case PRIORIDADE_MUITO_BAIXA:
            return "Muito Baixa";

        default:
            return "Nao definida";
    }
}

const char *status_para_texto(StatusUsina status)
{
    if (status == ATIVA)
    {
        return "Ativa";
    }

    return "Inativa";
}

/***********************************************************************
 * CRIAÇÃO DE NÓ
 ***********************************************************************/

NoABB *criar_no(Usina usina)
{
    NoABB *novo;

    novo = malloc(sizeof(NoABB));
	//novo = (NoABB *) malloc(sizeof(NoABB));
	
    if (novo == NULL)
    {
        printf("\nErro de alocacao de memoria.\n");
        return NULL;
    }

    novo->dados = usina;

    novo->esq = NULL;

    novo->dir = NULL;

    return novo;
}

/***********************************************************************
 * BUSCA
 ***********************************************************************/

NoABB *buscar_abb(NoABB *raiz, int codigo)
{
    if (raiz == NULL)
    {
        return NULL;
    }

    if (codigo == raiz->dados.codigo)
    {
        return raiz;
    }

    if (codigo < raiz->dados.codigo)
    {
        return buscar_abb(raiz->esq, codigo);
    }

    return buscar_abb(raiz->dir, codigo);
}

/***********************************************************************
 * VERIFICA CÓDIGO
 ***********************************************************************/

int codigo_existe(NoABB *raiz, int codigo)
{
    return (buscar_abb(raiz, codigo) != NULL);
}

/***********************************************************************
 * INSERÇÃO NA ABB
 ***********************************************************************/

void inserir_abb(NoABB **raiz, Usina usina)
{
    if (*raiz == NULL)
    {
        *raiz = criar_no(usina);

        return;
    }

    if (usina.codigo < (*raiz)->dados.codigo)
    {
        inserir_abb(&((*raiz)->esq), usina);
    }
    else
    {
        if (usina.codigo > (*raiz)->dados.codigo)
        {
            inserir_abb(&((*raiz)->dir), usina);
        }
        else
        {
            printf("\nCodigo ja cadastrado.\n");
        }
    }
}

/***********************************************************************
 * CADASTRAR USINA
 ***********************************************************************/

Usina cadastrar_usina(NoABB *raiz)
{
    Usina u;

    mostrar_cabecalho("CADASTRO DE USINA");

    do
    {
        u.codigo = ler_inteiro("Codigo da usina: ");

        if(codigo_existe(raiz,u.codigo))
        {
            printf("\nCodigo ja cadastrado!\n\n");
        }

    } while (codigo_existe(raiz, u.codigo));

    u.tipo = escolher_tipo();

    u.regiao = escolher_regiao();

    u.potencia_instalada =
        ler_float("Potencia instalada (MW): ");

    u.capacidade_disponivel =
        ler_float("Capacidade disponivel (MW): ");

    u.reservatorio =
        ler_float("Nivel do reservatorio (%): ");

    u.custo_mwh =
        ler_float("Custo (R$/MWh): ");

    u.producao_diaria =
        ler_float("Producao diaria (MWh): ");

    u.producao_mensal =
        ler_float("Producao mensal (MWh): ");

    u.prioridade = escolher_prioridade();

    ler_string("Data da ultima manutencao: ",
               u.ultima_manutencao,
               MAX_DATA);

    u.energia_total = 0.0f;

    u.faturamento_total = 0.0f;

    u.despachos = 0;

    u.horas_operacao = 0;

    u.status = ATIVA;

    registrar_log("Nova usina cadastrada.");

    printf("\nCadastro realizado com sucesso!\n");

    return u;
}

/***********************************************************************
 * ESCOLHER TIPO DA USINA
 ***********************************************************************/

static TipoUsina escolher_tipo(void)
{
    int opcao;

    do
    {
        printf("\n");
        linha_dupla();
        printf("TIPO DA USINA\n");
        linha();

        printf("1 - Hidreletrica\n");
        printf("2 - Termoeletrica\n");
        printf("3 - Eolica\n");
        printf("4 - Solar\n");
        printf("5 - Biomassa\n");

        opcao = ler_inteiro("Escolha: ");

    } while (!validar_intervalo_int(opcao,1,5));

    return (TipoUsina) opcao;
}

/***********************************************************************
 * ESCOLHER REGIAO
 ***********************************************************************/

static Regiao escolher_regiao(void)
{
    int opcao;

    do
    {
        printf("\n");
        linha_dupla();
        printf("REGIAO\n");
        linha();

        printf("1 - Sul\n");
        printf("2 - Sudeste\n");
        printf("3 - Centro-Oeste\n");
        printf("4 - Nordeste\n");
        printf("5 - Norte\n");

        opcao = ler_inteiro("Escolha: ");

    } while (!validar_intervalo_int(opcao,1,5));

    return (Regiao) opcao;
}

/***********************************************************************
 * ESCOLHER PRIORIDADE
 ***********************************************************************/

static Prioridade escolher_prioridade(void)
{
    int opcao;

    do
    {
        printf("\n");
        linha_dupla();
        printf("PRIORIDADE\n");
        linha();

        printf("1 - Muito Alta\n");
        printf("2 - Alta\n");
        printf("3 - Media\n");
        printf("4 - Baixa\n");
        printf("5 - Muito Baixa\n");

        opcao = ler_inteiro("Escolha: ");

    } while (!validar_intervalo_int(opcao,1,5));

    return (Prioridade) opcao;
}

/***********************************************************************
 * EDITAR USINA
 ***********************************************************************/

void editar_usina(NoABB *raiz)
{
    int codigo;
    NoABB *no;

    mostrar_cabecalho("EDITAR USINA");

    codigo = ler_inteiro("Codigo da usina: ");

    no = buscar_abb(raiz, codigo);

    if (no == NULL)
    {
        printf("\nUsina nao encontrada.\n");
        return;
    }

    printf("\nAlterando dados da usina %d\n", codigo);

    no->dados.tipo = escolher_tipo();

    no->dados.regiao = escolher_regiao();

    no->dados.potencia_instalada =
        ler_float("Potencia instalada (MW): ");

    no->dados.capacidade_disponivel =
        ler_float("Capacidade disponivel (MW): ");

    no->dados.reservatorio =
        ler_float("Nivel do reservatorio (%): ");

    no->dados.custo_mwh =
        ler_float("Custo (R$/MWh): ");

    no->dados.producao_diaria =
        ler_float("Producao diaria (MWh): ");

    no->dados.producao_mensal =
        ler_float("Producao mensal (MWh): ");

    no->dados.prioridade =
        escolher_prioridade();

    ler_string("Ultima manutencao: ",
               no->dados.ultima_manutencao,
               MAX_DATA);

    registrar_log("Cadastro de usina alterado.");

    printf("\nDados atualizados com sucesso!\n");
}

/***********************************************************************
 * ATIVAR USINA
 ***********************************************************************/

void ativar_usina(NoABB *raiz,
                  int codigo)
{
    NoABB *no;

    no = buscar_abb(raiz, codigo);

    if (no == NULL)
    {
        printf("\nUsina nao encontrada.\n");
        return;
    }

    no->dados.status = ATIVA;

    registrar_log("Usina ativada.");

    printf("\nUsina ativada com sucesso.\n");
}

/***********************************************************************
 * DESATIVAR USINA
 ***********************************************************************/

void desativar_usina(NoABB *raiz,
                     int codigo)
{
    NoABB *no;

    no = buscar_abb(raiz, codigo);

    if (no == NULL)
    {
        printf("\nUsina nao encontrada.\n");
        return;
    }

    no->dados.status = INATIVA;

    registrar_log("Usina desativada.");

    printf("\nUsina desativada com sucesso.\n");
}

/***********************************************************************
 * ATUALIZAR MANUTENÇÃO
 ***********************************************************************/

void atualizar_manutencao(NoABB *raiz,
                          int codigo)
{
    NoABB *no;

    no = buscar_abb(raiz, codigo);

    if (no == NULL)
    {
        printf("\nUsina nao encontrada.\n");
        return;
    }

    obter_data(no->dados.ultima_manutencao);

    registrar_log("Data de manutencao atualizada.");

    printf("\nManutencao registrada.\n");
}

/***********************************************************************
 * RESTAURAR CAPACIDADE
 ***********************************************************************/

void restaurar_capacidade(NoABB *raiz)
{
    if (raiz == NULL)
    {
        return;
    }

    restaurar_capacidade(raiz->esq);

    raiz->dados.capacidade_disponivel =
        raiz->dados.potencia_instalada;

    restaurar_capacidade(raiz->dir);
}

/***********************************************************************
 * IMPRIMIR DADOS COMPLETOS DA USINA
 ***********************************************************************/

void imprimir_usina(Usina usina)
{
    linha_dupla();

    printf("Codigo................: %d\n", usina.codigo);

    printf("Tipo..................: %s\n",
           tipo_para_texto(usina.tipo));

    printf("Regiao................: %s\n",
           regiao_para_texto(usina.regiao));

    printf("Status................: %s\n",
           status_para_texto(usina.status));

    printf("Potencia Instalada....: %.2f MW\n",
           usina.potencia_instalada);

    printf("Capacidade Disponivel.: %.2f MW\n",
           usina.capacidade_disponivel);

    printf("Reservatorio..........: %.2f %%\n",
           usina.reservatorio);

    printf("Custo.................: R$ %.2f / MWh\n",
           usina.custo_mwh);

    printf("Producao Diaria.......: %.2f MWh\n",
           usina.producao_diaria);

    printf("Producao Mensal.......: %.2f MWh\n",
           usina.producao_mensal);

    printf("Prioridade............: %s\n",
           prioridade_para_texto(usina.prioridade));

    printf("Despachos.............: %d\n",
           usina.despachos);

    printf("Horas Operacao........: %d\n",
           usina.horas_operacao);

    printf("Energia Produzida.....: %.2f MWh\n",
           usina.energia_total);

    printf("Faturamento...........: R$ %.2f\n",
           usina.faturamento_total);

    printf("Ultima Manutencao.....: %s\n",
           usina.ultima_manutencao);

    linha_dupla();
}

/***********************************************************************
 * IMPRIME RESUMO
 ***********************************************************************/

void imprimir_resumo(Usina usina)
{
    printf("%5d | %-15s | %-12s | %10.2f MW | %-8s\n",
           usina.codigo,
           tipo_para_texto(usina.tipo),
           regiao_para_texto(usina.regiao),
           usina.capacidade_disponivel,
           status_para_texto(usina.status));
}

/***********************************************************************
 * LISTAGEM EM ORDEM
 ***********************************************************************/

void listar_usinas(NoABB *raiz)
{
    if (raiz == NULL)
    {
        return;
    }

    listar_usinas(raiz->esq);

    imprimir_resumo(raiz->dados);

    listar_usinas(raiz->dir);
}

/***********************************************************************
 * QUANTIDADE DE USINAS
 ***********************************************************************/

int quantidade_usinas(NoABB *raiz)
{
    if (raiz == NULL)
    {
        return 0;
    }

    return 1 +
           quantidade_usinas(raiz->esq) +
           quantidade_usinas(raiz->dir);
}

/***********************************************************************
 * QUANTIDADE DE USINAS ATIVAS
 ***********************************************************************/

int quantidade_ativas(NoABB *raiz)
{
    if (raiz == NULL)
    {
        return 0;
    }

    return (raiz->dados.status == ATIVA) +
           quantidade_ativas(raiz->esq) +
           quantidade_ativas(raiz->dir);
}

/***********************************************************************
 * POTÊNCIA INSTALADA TOTAL
 ***********************************************************************/

float potencia_total(NoABB *raiz)
{
    if (raiz == NULL)
    {
        return 0.0f;
    }

    return raiz->dados.potencia_instalada +
           potencia_total(raiz->esq) +
           potencia_total(raiz->dir);
}

/***********************************************************************
 * CAPACIDADE DISPONÍVEL
 ***********************************************************************/

float capacidade_total_disponivel(NoABB *raiz)
{
    if (raiz == NULL)
    {
        return 0.0f;
    }

    return raiz->dados.capacidade_disponivel +
           capacidade_total_disponivel(raiz->esq) +
           capacidade_total_disponivel(raiz->dir);
}

/***********************************************************************
 * COPIA ABB PARA VETOR
 ***********************************************************************/

void copiar_usinas(NoABB *raiz,
                   Usina vetor[],
                   int *indice)
{
    if (raiz == NULL)
    {
        return;
    }

    copiar_usinas(raiz->esq,
                  vetor,
                  indice);

    vetor[*indice] = raiz->dados;

    (*indice)++;

    copiar_usinas(raiz->dir,
                  vetor,
                  indice);
}

/***********************************************************************
 * LIBERA MEMÓRIA
 ***********************************************************************/

void liberar_abb(NoABB *raiz)
{
    if (raiz == NULL)
    {
        return;
    }

    liberar_abb(raiz->esq);

    liberar_abb(raiz->dir);

    free(raiz);
}
