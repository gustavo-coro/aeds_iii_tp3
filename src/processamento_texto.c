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
int* tabelaMascaraBitsSA (char* texto) {
    int size = strlen(texto);
    int* tabelaMascaraBits = (int*) malloc(sizeof(int) * 26);
    for (int i = 0; i < 26; i++) {
        tabelaMascaraBits[i] = 0;
    }
    for (int i = 0; i < size; i++) {
        int temp = 1;
        temp = (temp << (size - i - 1));
        tabelaMascaraBits[texto[i] - 97] |= temp;
    }

    return tabelaMascaraBits;
}