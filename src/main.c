#include "../include/main.h"

int main (int argc, char **argv) {

    // variaveis usadas para armazenar o tempo de execucao do programa
    struct timeval tempoInicio, tempoFim, tempoDiferenca;

    // variaveis que armazenam os diferentes tempos em microssegundos
    double tempoUsuarioInicio, tempoSistemaInicio, tempoUsuarioFim, tempoSistemaFim;
    double tempoGetTimeofDay, tempoUsuario, tempoSistema, tempoRuUsage;

    // pega os tempos do inicio da execucao
    getUsageNow(&tempoUsuarioInicio, &tempoSistemaInicio);
    gettimeofday(&tempoInicio, NULL);

    // abre o arquivo de entrada e armazena a solucao requisitada
    FILE (*inFile);
    FILE (*outFile);
    char* solution = (char*) malloc(sizeof(char));
    if (openFile(argc, argv, &inFile, solution, &outFile) != 1) {
        exit(0);
    }

    // le o arquivo de entrada, calcula cada entrada e escreve no arquivo de saida
    readFile(inFile, outFile, solution);

    // pega os temps do fim da execucao
    getUsageNow(&tempoUsuarioFim, &tempoSistemaFim);
    gettimeofday(&tempoFim, NULL);
    timeval_subtract(&tempoDiferenca, &tempoFim, &tempoInicio);

    // guarda os tempos em microssegundos
    tempoGetTimeofDay = joinTimes(tempoDiferenca.tv_sec, tempoDiferenca.tv_usec);
    tempoUsuario = tempoUsuarioFim - tempoUsuarioInicio;
    tempoSistema = tempoSistemaFim - tempoSistemaInicio;
    tempoRuUsage = tempoUsuario + tempoSistema;

    // escreve os tempos no terminal
    printTimes(tempoUsuario, tempoSistema, tempoRuUsage, tempoGetTimeofDay);

    // fecha os arquivos e desaloca as variaveis usadas
    fclose(inFile);
    fclose(outFile);
    free(solution);

    return 0;
}