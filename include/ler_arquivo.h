#ifndef LER_ARQUIVO_H
#define LER_ARQUIVO_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"
#include "processamento_texto.h"
#include "calcula_casamento.h"

char *readLine (FILE*);
int openFile (int, char**, FILE**, char*, FILE**);
void readFile (FILE*, FILE*, char*);

#endif