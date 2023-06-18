#include "../include/calcula_casamento.h"

// solucao usando forca bruta
int forcaBruta (list* padrao, list* texto) {
    // temporario usado para passar por cada letra do texto
    node* temporario = texto->first;
    for (int i = 0; i < texto->size; i++) {
        // temporarios usados para caminhar pelo padrao e pelo texto
        node* temporarioPadrao = padrao->first;
        node* temporarioTexto = temporario;
        // verificando se existe casamento a partir da posicao atual do texto
        // caminhando da esquerda para a direita no texto
        for (int j = 0; j < padrao->size; j++) {
            if (temporarioTexto->data != temporarioPadrao->data) {
                // nao houve casamento
                break;
            } else if (j == padrao->size-1) {
                // houve casamento na posicao do temporario
                return temporario->position;
            }
            temporarioTexto = temporarioTexto->next;
            temporarioPadrao = temporarioPadrao->next;
        }
        // verificando se existe casamento a partir da posicao atual do texto
        // caminhando da direita para a esquerda no texto
        temporarioTexto = temporario;
        temporarioPadrao = padrao->first;
        for (int j = 0; j < padrao->size; j++) {
            if (temporarioTexto->data != temporarioPadrao->data) {
                // nao houve casamento
                break;
            } else if (j == padrao->size-1) {
                // houve casamento na posicao do temporario
                return temporario->position;
            }
            temporarioTexto = temporarioTexto->before;
            temporarioPadrao = temporarioPadrao->next;
        }
        // caminhando para o proximo caracter do texto
        temporario = temporario->next;
    }
    // retorna caso nao exista casamento
    return -1;
}

// solucao usando o algoritmo de Boyer-Moore-Horspool
int solucaoBMH (list* texto, list* padrao, int* tabelaDeslocamentos) {
    int i = padrao->size;
    int posicaoCasamento = -1;
    // temporario usado para passar por cada letra do texto
    node* temporario = texto->first;

    // anda para a posicao do texto em que o indice e o tamanho do padrao
    for (int j = 0; j < (padrao->size-1); j++) {
        temporario = temporario->next;
    }
    // solucao com texto da esquerda para a direita
    while (i < (texto->size + padrao->size)) {
        // temporarios usados para caminhar pelo texto e pelo padrao
        node* temporarioTexto = temporario;
        node* temporarioPadrao = padrao->last;
        int j = padrao->size;
        // verifica se o ultimo caracter do padrao e igual ao caracter atual do texto
        // anda da direita para a esquerda ate eles forem diferentes ou chegarmos na posicao inicial do padrao
        while ((j > 0) && (temporarioPadrao->data == temporarioTexto->data)) {
            j = j - 1;
            temporarioPadrao = temporarioPadrao->before;
            temporarioTexto = temporarioTexto->before;
        }
        if (j == 0) {
            // houve casamento
            posicaoCasamento = temporarioTexto->next->position;
            break;
        }
        // em caso de nao ocorrer casamentos, consulta a tabela de deslocamentos para andar pelo texto
        int deslocamento = tabelaDeslocamentos[temporario->data - 97];
        i = i + deslocamento;
        // anda pelo texto de acordo com o deslocamento
        for (int k = 0; k < (deslocamento); k++) {
            temporario = temporario->next;
        }
    }
    
    // guardando o resultado da verificacao do texto da esquerda para a direita
    int resultado = posicaoCasamento;
    posicaoCasamento = -1;
    i = padrao->size;
    temporario = texto->last;


    // anda para a posicao do texto em que o indice e o tamanho do padrao
    for (int j = 0; j < (padrao->size-1); j++) {
        temporario = temporario->before;
    }
    // solucao com texto da direita para a esquerda
    while (i < (texto->size + padrao->size)) {
        // temporarios usados para caminhar pelo texto e pelo padrao
        node* temporarioTexto = temporario;
        node* temporarioPadrao = padrao->last;
        int j = padrao->size;
        // verifica se o ultimo caracter do padrao e igual ao caracter atual do texto
        // anda da direita para a esquerda pelo padrao e da esquerda para a direita pelo texto
        // ate eles forem diferentes ou chegarmos na posicao inicial do padrao
        while ((j > 0) && (temporarioPadrao->data == temporarioTexto->data)) {
            j = j - 1;
            temporarioPadrao = temporarioPadrao->before;
            temporarioTexto = temporarioTexto->next;
        }
        if (j == 0) {
            // houve casamento
            // verifica qual, caso exista um casamento da solucao andando da esquerda para a direita, e a primeira posicao a ocorrer
            if (posicaoCasamento == -1) {
                posicaoCasamento = temporarioTexto->before->position;
            } else if (posicaoCasamento > temporarioTexto->before->position) {
                posicaoCasamento = temporarioTexto->before->position;
            }
        }

        // em caso de nao ocorrer casamentos, consulta a tabela de deslocamentos para andar pelo texto
        int deslocamento = tabelaDeslocamentos[temporario->data - 97];
        i = i + deslocamento;
        // anda pelo texto de acordo com o deslocamento
        for (int k = 0; k < (deslocamento); k++) {
            temporario = temporario->before;
        }
    }
    // confirmando qual o primeiro casamento, caso ocorra mais de um
    // caso nao ocorra casamento, retorna -1
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

// solucao usando o algoritmo Shift-And
int solucaoShiftAnd (list* texto, list* padrao, int** tabelaMascaraBits) {
    int posicaoCasamento = -1;
    // temporario usado para caminhar pelo texto
    node* temporario = texto->first;
    // variavel que guarda os prefixos que casam com o texto lido
    int* conjuntoPrefixos = (int*) malloc(sizeof(int) * padrao->size);
    for (int i = 0; i < padrao->size; i++) {
        conjuntoPrefixos[i] = 0;
    }
    int repeticoes = padrao->size + texto->size;
    // procurando casamento da esquerda para a direita no texto
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
    // guardando o resultado do casamento
    int resultado = posicaoCasamento;
    temporario = texto->last;
    // procurando casamento da esquerda para a direita no texto
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
            if (posicaoCasamento == -1) {
                posicaoCasamento = temporario->position;
            } else if (posicaoCasamento > temporario->position) {
                posicaoCasamento = temporario->position;
            }
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

// operacao de shift de um para a direita
void shiftUmDireita (int* bits, int size) {
    int atual = bits[0];
    bits[0] = 1;
    for (int i = 1; i < size; i++) {
        int temp = atual;
        atual = bits[i];
        bits[i] = temp;
    }
}

// operacao and de bits
void andBits (int* bits, int* mascara, int size) {
    for (int i = 0; i < size; i++) {
        bits[i] = bits[i] * mascara[i];
    }
}