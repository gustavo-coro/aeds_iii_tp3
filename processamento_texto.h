#ifndef PROCESSAMENTO_TEXTO_H
#define PROCESSAMENTO_TEXTO_H

#include "main.h"

list* retornaLista (char*);
int* tabelaDeslocamentosBMH (char*);
int** tabelaMascaraBitsSA (char*);
void freeTabelaMascaraBitsSA (int**);

#endif