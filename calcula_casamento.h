#ifndef CALCULA_CASAMENTO_H
#define CALCULA_CASAMENTO_H

#include "main.h"

int forcaBruta (list*, list*); // solucao usando forca bruta
int solucaoBMH (list*, list*, int*); // solucao usando o metodo de Boyer-Moore-Horspool
int solucaoShiftAnd (list*, list*, int**); // solucao usando o metodo shift-and
void shiftUmDireita (int*, int);
void andBits (int*, int*, int);

#endif