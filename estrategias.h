/***********************************************************************
 * SIGDE
 *
 * estrategias.h
 *
 * Estratégias de despacho
 ***********************************************************************/

#ifndef ESTRATEGIAS_H
#define ESTRATEGIAS_H

#include "tipos.h"
#include "usina.h"

/***********************************************************************
 * COMPARAÇÃO
 ***********************************************************************/

int comparar_usinas(
        const Usina *a,
        const Usina *b,
        PoliticaDespacho politica);

/***********************************************************************
 * POLÍTICA ECOLÓGICA
 ***********************************************************************/

int prioridade_ecologica(
        TipoUsina tipo);

/***********************************************************************
 * POLÍTICA BALANCEADA
 ***********************************************************************/

float calcular_score(Usina u)
{
    float score;

    float custo;

    float prioridade;

    float capacidade;

    float reservatorio;

    custo = 1000.0f / (u.custo_mwh + 1.0f);

    prioridade = 6.0f - u.prioridade;

    capacidade = u.capacidade_disponivel / 1000.0f;

    reservatorio = u.reservatorio / 100.0f;

    score =
          custo * 0.40f
        + prioridade * 0.30f
        + capacidade * 0.20f
        + reservatorio * 0.10f;

    return score;
}

#endif
