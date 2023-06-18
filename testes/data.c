#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char **argv) {

    usleep(1000000);

    fclose(fopen(argv[1], "w"));
    FILE *exit = fopen(argv[1], "a");
    time_t t;

    int maxCasosTeste = 100;
    int maxCharPadrao = 64;
    int maxCharTexto = 10000;
    int casosTeste;

    srand((unsigned)time(&t));
    casosTeste = 1;// + (rand() % maxCasosTeste);
    fprintf(exit, "%d\n", casosTeste);
    while (casosTeste > 0) {
        int tamPadrao, tamTexto;
        tamPadrao = 1 + (rand() % maxCharPadrao);
        tamTexto = 1 + (rand() % maxCharTexto);
        for (int i = 0; i < tamPadrao; i++) {
            char c = 'a' + (char) (rand()%26);
            fprintf(exit, "%c", c);
        }
        fprintf(exit, " ");
        for (int i = 0; i < tamTexto; i++) {
            char c = 'a' + (char) (rand()%26);
            fprintf(exit, "%c", c);
        }
        fprintf(exit, "\n");
        casosTeste--;
    }
    fclose(exit);
    return (0);
}