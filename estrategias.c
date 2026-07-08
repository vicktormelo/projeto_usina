/***********************************************************************
 * SIGDE
 *
 * estrategias.c
 ***********************************************************************/

#include "estrategias.h"

/***********************************************************************
 * PRIORIDADE ECOLÓGICA
 ***********************************************************************/

int prioridade_ecologica(TipoUsina tipo)
{
    switch(tipo)
    {
        case SOLAR:
            return 1;

        case EOLICA:
            return 2;

        case HIDRELETRICA:
            return 3;

        case BIOMASSA:
            return 4;

        case TERMOELETRICA:
            return 5;

        default:
            return 99;
    }
}
