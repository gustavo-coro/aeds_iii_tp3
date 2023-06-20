#ifndef CALCULA_CASAMENTO_H
#define CALCULA_CASAMENTO_H

#include <string.h>

#include "lista.h"

int forcaBruta (list*, list*); // solucao usando forca bruta
int solucaoBMH (list*, list*, int*); // solucao usando o metodo de Boyer-Moore-Horspool
int solucaoShiftAnd (list*, list*, __int128_t*); // solucao usando o metodo shift-and
#endif