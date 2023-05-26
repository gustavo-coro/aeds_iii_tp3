#include "main.h"

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
    for (int i = 0; i < size; i++) {
        for (int j = 1; j < size; j++) {
            if (texto[(size - 1) - j] == texto[i]) {
                tabelaDeslocamentos[texto[i] - 97] = j;
                break;
            }
        }
    }
    return tabelaDeslocamentos;
}