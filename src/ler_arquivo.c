#include "../include/ler_arquivo.h"

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
    // verifica se foi passado o numero de parametros necessarios
    if (argc < 3) {
        perror("Faltam parametros para executar corretamente.\n");
        return -1;
    } else if (argc > 3) {
        perror("Parametros demais.\n");
        return -1;
    }

    // recebe o arquivo de entrada
    *in = fopen(argv[1], "r");
    // recebe a solucao desejada
    *solution = *argv[2];
    // verifica se o arquivo de entrada esta em outra pasta e copia seu nome para criar o arquivo de saida
    char* nomeArquivo = strrchr (argv[1], '/');
    if (nomeArquivo == NULL) {
        nomeArquivo = strtok(argv[1], ".");
    } else {
        nomeArquivo++;
        nomeArquivo = strtok(nomeArquivo, ".");
    }
    nomeArquivo = strcat(nomeArquivo, ".out");
    // abre o arquivo de saida
    *out = fopen(nomeArquivo, "w+");

    return 1; // retorna em caso de sucesso
}

// funcao que le o arquivo de entrada e escreve a resposta no arquivo de saida
void readFile (FILE* inFile, FILE* outFile, char *solution) {
    char *line = NULL;
    int casosTeste;
    // ler a primeira linha com o numero de casos de teste
    if ((line = readLine(inFile)) != NULL) {
        sscanf(line, "%d", &casosTeste);
    }
    // le cada caso de teste e calcula seu resultado
    for (int contLine = 0; contLine < casosTeste; contLine++) {
        if ((line = readLine(inFile)) != NULL) {
            char* padrao;
            char* texto;
            padrao = strtok(line, " ");
            texto = strtok(NULL, "\n");
            // coloca o padrao e o texto em uma lista circular necessaria para as solucoes
            list* listaPadrao = retornaLista(padrao);
            list* listaTexto = retornaLista(texto);
            // variavel que guardara a posicao do casamento, caso exista
            int resultado = -1;
            // verifica qual solucao foi escolhida
            switch (*solution) {
            case '1': {
                // chamadas de funcao para a primeira solucao
                // calcula se existem casamentos usando um algoritmo forca bruta
                resultado = forcaBruta(listaPadrao, listaTexto);
                break;
            }

            case '2': {
                // chamadas de funcao para a segunda solucao
                int* tabelaDeslocamentos;
                // tabela com os deslocamentos de cada caracter do alfabeto
                tabelaDeslocamentos = tabelaDeslocamentosBMH(padrao);
                // calcula se existem casamentos usando o algoritmo de Boyer-Moore-Horspool
                resultado = solucaoBMH(listaTexto, listaPadrao, tabelaDeslocamentos);
                free(tabelaDeslocamentos);
                break;
            }
            case '3': {
                // chamadas de funcao para a terceira solucao
                // cria uma tabela com a mascara de bits de cada letra do alfabeto
                __int128_t* tabelaMascaraBits = tabelaMascaraBitsSA(padrao);
                // calcula se existem casamentos usando o algoritmo Shift-And
                resultado = solucaoShiftAnd (listaTexto, listaPadrao, tabelaMascaraBits);
                free(tabelaMascaraBits);
                break;
            }
            
            default: {
                perror("Solucao nao existe.");
                exit(0);
            }
            }
            // imprime o resultado no arquivo de saida
            if (resultado < 0) { // nao houve casamento
                fprintf(outFile, "N\n");
            } else { // houve casamento na posicao indicada por resultado
                fprintf(outFile, "S %d\n", resultado);
            }
            // desaloca as variaveis usadas
            freeList(listaPadrao);
            freeList(listaTexto);
            free(line);
        }
    }
    
}