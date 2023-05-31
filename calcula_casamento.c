#include "main.h"


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

int solucaoShiftAnd (list* texto, list* padrao, int** tabelaMascaraBits) {
    int posicaoCasamento = -1;
    node* temporario = texto->first;
    // variavel que guarda os prefixos que casam com o texto lido
    int* conjuntoPrefixos = (int*) malloc(sizeof(int) * padrao->size);
    for (int i = 0; i < padrao->size; i++) {
        conjuntoPrefixos[i] = 0;
    }
    int repeticoes = padrao->size + texto->size;
    for (int i = 0; i < repeticoes; i++) {
        // shift de 1 para a direita
        shiftUmDireita(conjuntoPrefixos, padrao->size);
        // and com a mascara da posicao atual do texto
        andBits(conjuntoPrefixos, tabelaMascaraBits[temporario->data - 97], padrao->size);
        // casamento aconteceu
        if (conjuntoPrefixos[padrao->size - 1] == 1) {
            // achando a posicao do casamento
            for (int i = 0; i < padrao->size-1; i++) {
                temporario = temporario->before;
            }
            posicaoCasamento = temporario->position;
            break;
        }
        temporario = temporario->next;
    }
    int resultado = posicaoCasamento;
    temporario = texto->last;
    for (int i = 0; i < repeticoes; i++) {
        // shift de 1 para a direita
        shiftUmDireita(conjuntoPrefixos, padrao->size);
        // and com a mascara da posicao atual do texto
        andBits(conjuntoPrefixos, tabelaMascaraBits[temporario->data - 97], padrao->size);
        // casamento aconteceu
        if (conjuntoPrefixos[padrao->size - 1] == 1) {
            // achando a posicao do casamento
            for (int i = 0; i < padrao->size-1; i++) {
                temporario = temporario->next;
            }
            posicaoCasamento = temporario->position;
            break;
        }
        temporario = temporario->before;
    }
    free(conjuntoPrefixos);
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

void shiftUmDireita (int* bits, int size) {
    int atual = bits[0];
    bits[0] = 1;
    for (int i = 1; i < size; i++) {
        int temp = atual;
        atual = bits[i];
        bits[i] = temp;
    }
}

void andBits (int* bits, int* mascara, int size) {
    for (int i = 0; i < size; i++) {
        bits[i] = bits[i] * mascara[i];
    }
}