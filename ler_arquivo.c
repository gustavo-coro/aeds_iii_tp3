#include <getopt.h>

#include "main.h"

// ***************************************************
// FUNCAO readLine RETIRADA DE:
// https://www.ime.usp.br/~pf/algoritmos/aulas/io2.html
// ***************************************************
// A função readLine lê uma linha (a partir da posição 
// corrente) do arquivo de texto infile e devolve uma
// string com o mesmo conteúdo da linha. O char \n que
// sinaliza o fim da linha não é armazenado como parte
// da string. A função devolve NULL se a posição
// corrente do arquivo estiver no fim do arquivo. Uso
// típico da função: 
//             s = readLine (infile);
// (Esta função é uma adaptação da função ReadLine da
// biblioteca simpio de Eric Roberts.)

char *readLine (FILE *infile) {
   int n = 0, size = 128, ch;
   char *line;
   line = malloc (size + 1);
   while ((ch = getc (infile)) != '\n' && ch != EOF) {
      if (n == size) {
         size *= 2;
         line = realloc (line, size + 1);
      }
      line[n++] = ch;
   }
   if (n == 0 && ch == EOF) {
      free (line);
      return NULL;
   }
   line[n] = '\0';
   line = realloc (line, n + 1);
   return line;
}

int openFile (int argc, char **argv, FILE **in, char *solution, FILE **out) {
    
    if (argc < 3) {
        perror("Faltam parametros para executar corretamente.\n");
        return -1;
    } else if (argc > 3) {
        perror("Parametros demais.\n");
        return -1;
    }

    *in = fopen(argv[1], "r");
    *solution = *argv[2];
    char* nomeArquivo = strrchr (argv[1], '/');
    if (nomeArquivo == NULL) {
        nomeArquivo = strtok(argv[1], ".");
    } else {
        nomeArquivo++;
        nomeArquivo = strtok(nomeArquivo, ".");
    }
    nomeArquivo = strcat(nomeArquivo, ".out");
    *out = fopen(nomeArquivo, "w+");

    return 1; //retorna em caso de sucesso
}

void readFile (FILE* inFile, FILE* outFile, char *solution) {
    char *line = NULL;
    int casosTeste;
    //ler a primeira linha com o numero de casos de teste
    if ((line = readLine(inFile)) != NULL) {
        sscanf(line, "%d", &casosTeste);
    }
    for (int contLine = 0; contLine < casosTeste; contLine++) {
        if ((line = readLine(inFile)) != NULL) {
            char* padrao;
            char* texto;
            padrao = strtok(line, " ");
            texto = strtok(NULL, "\n");
            list* listaPadrao = retornaLista(padrao);
            list* listaTexto = retornaLista(texto);
            int resultado = -1;
            switch (*solution) {
            case '1': {
                //chamadas de funcao para a primeira solucao
                resultado = forcaBruta(listaPadrao, listaTexto);
                break;
            }

            case '2': {
                //chamadas de funcao para a segunda solucao
                int* tabelaDeslocamentos;
                tabelaDeslocamentos = tabelaDeslocamentosBMH(padrao);
                resultado = solucaoBMH(listaTexto, listaPadrao, tabelaDeslocamentos);
                free(tabelaDeslocamentos);
                break;
            }
            case '3': {
                //chamadas de funcao para a terceira solucao
                break;
            }
            
            default: {
                perror("Solucao nao existe.");
                exit(0);
            }
            }
            if (resultado < 0) { // nao houve casamento
                fprintf(outFile, "N\n");
            } else { // houve casamento na posicao indicada por resultado
                fprintf(outFile, "S %d\n", resultado);
            }
            freeList(listaPadrao);
            freeList(listaTexto);
            free(line);
        }
    }
    
}

int forcaBruta (list* padrao, list* texto) {
    node* temporario = texto->first;
    for (int i = 0; i < texto->size; i++) {
        node* temporarioPadrao = padrao->first;
        node* temporarioTexto = temporario;
        for (int j = 0; j < padrao->size; j++) {
            if (temporarioTexto->data != temporarioPadrao->data) {
                //nao houve casamento
                break;
            } else if (j == padrao->size-1) {
                return temporario->position;
            }
            temporarioTexto = temporarioTexto->next;
            temporarioPadrao = temporarioPadrao->next;
        }
        temporarioTexto = temporario;
        temporarioPadrao = padrao->first;
        for (int j = 0; j < padrao->size; j++) {
            if (temporarioTexto->data != temporarioPadrao->data) {
                //nao houve casamento
                break;
            } else if (j == padrao->size-1) {
                return temporario->position;
            }
            temporarioTexto = temporarioTexto->before;
            temporarioPadrao = temporarioPadrao->next;
        }
        temporario = temporario->next;
    }
    return -1;
}

int solucaoBMH (list* texto, list* padrao, int* tabelaDeslocamentos) {
    int i = padrao->size;
    int posicaoCasamento = -1;
    node* temporario = texto->first;

    // solucao com texto da esquerda para a direita
    for (int j = 0; j < (padrao->size-1); j++) {
        temporario = temporario->next;
    }
    while (i < (texto->size + padrao->size)) {
        node* temporarioTexto = temporario;
        node* temporarioPadrao = padrao->last;
        int j = padrao->size;
        while ((j > 0) && (temporarioPadrao->data == temporarioTexto->data)) {
            j = j - 1;
            temporarioPadrao = temporarioPadrao->before;
            temporarioTexto = temporarioTexto->before;
        }
        if (j == 0) {
            posicaoCasamento = temporarioTexto->next->position;
            break;
        }

        int deslocamento = tabelaDeslocamentos[temporario->data - 97];
        i = i + deslocamento;
        for (int k = 0; k < (deslocamento); k++) {
            temporario = temporario->next;
        }
    }
    int resultado = posicaoCasamento;
    posicaoCasamento = -1;
    i = padrao->size;
    temporario = texto->last;

    // solucao com texto da direita para a esquerda
    for (int j = 0; j < (padrao->size-1); j++) {
        temporario = temporario->before;
    }
    while (i < (texto->size + padrao->size)) {
        node* temporarioTexto = temporario;
        node* temporarioPadrao = padrao->last;
        int j = padrao->size;
        while ((j > 0) && (temporarioPadrao->data == temporarioTexto->data)) {
            j = j - 1;
            temporarioPadrao = temporarioPadrao->before;
            temporarioTexto = temporarioTexto->next;
        }
        if (j == 0) {
            posicaoCasamento = temporarioTexto->before->position;
            break;
        }

        int deslocamento = tabelaDeslocamentos[temporario->data - 97];
        i = i + deslocamento;
        for (int k = 0; k < (deslocamento); k++) {
            temporario = temporario->before;
        }
    }
    // confirmando qual o primeiro casamento, caso ocorra mais de um
    if (posicaoCasamento == -1) {
        return resultado;
    } else if (resultado == -1) {
        return posicaoCasamento;
    } else {
        if (posicaoCasamento <= resultado) {
            return posicaoCasamento;
        } else {
            return resultado;
        }
    }
}