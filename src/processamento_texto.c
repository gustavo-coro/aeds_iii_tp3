#include "../include/processamento_texto.h"

// retorna uma lista circular com a string passada como paramentro
list* retornaLista (char* string) {
    list* lista = startList();
    addFirstItem (lista, string[0]);
    int size = strlen(string);
    for (int i = 1; i < size; i++) {
        addItem(lista, string[i]);
    }
    return lista;
}

// Tabela com os deslocamentos que serao usados no metodo de Boyer-Moore-Horspool
int* tabelaDeslocamentosBMH (char* texto) {
    int* tabelaDeslocamentos = (int*) malloc(sizeof(int) * 26);
    int size = strlen(texto);
    for (int i = 0; i < 26; i++) {
        tabelaDeslocamentos[i] = size;
    } 
    for (int i = 0; i < size - 1; i++) {
        tabelaDeslocamentos[texto[i] - 97] = size - i - 1;
    }
    return tabelaDeslocamentos;
}

// Tabela com a mascara de bits para os caracteres do texto
int** tabelaMascaraBitsSA (char* texto) {
    int size = strlen(texto);
    int** tabelaMascaraBits = (int**) malloc(sizeof(int*) * 26);
    for (int i = 0; i < 26; i++) {
        tabelaMascaraBits[i] = (int*) malloc(sizeof(int) * size);
        for (int j = 0; j < size; j++) {
            tabelaMascaraBits[i][j] = 0;
        }
    }
    for (int i = 0; i < size; i++) {
        tabelaMascaraBits[texto[i] - 97][i] = 1;
    }
    return tabelaMascaraBits;
}

// desaloca a tabela de mascara de bits usada no shift-and
void freeTabelaMascaraBitsSA (int** tabelaMascaraBits) {
    for (int i = 0; i < 26; i++) {
        free(tabelaMascaraBits[i]);
    }
    free(tabelaMascaraBits);
}