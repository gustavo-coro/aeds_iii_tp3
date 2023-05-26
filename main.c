#include "main.h"
#include <sys/time.h>
#include <sys/resource.h>

// timeval_subtract retirado de:
// https://ftp.gnu.org/old-gnu/Manuals/glibc-2.2.3/html_node/libc_418.html
void timeval_subtract (struct timeval *result, struct timeval *x, struct timeval *y) {
  /* Perform the carry for the later subtraction by updating y. */
  if (x->tv_usec < y->tv_usec) {
    int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
    y->tv_usec -= 1000000 * nsec;
    y->tv_sec += nsec;
  }
  if (x->tv_usec - y->tv_usec > 1000000) {
    int nsec = (x->tv_usec - y->tv_usec) / 1000000;
    y->tv_usec += 1000000 * nsec;
    y->tv_sec -= nsec;
  }

  /* Compute the time remaining to wait.
     tv_usec is certainly positive. */
  result->tv_sec = x->tv_sec - y->tv_sec;
  result->tv_usec = x->tv_usec - y->tv_usec;
}

int main (int argc, char **argv) {

    struct timeval tempoInicio, tempoFim, tempoDiferenca;
    struct rusage usage;

    gettimeofday(&tempoInicio, NULL);

    FILE (*inFile);
    FILE (*outFile);
    char* solution = (char*) malloc(sizeof(char));
    if (openFile(argc, argv, &inFile, solution, &outFile) != 1) {
        exit(0);
    }
    readFile(inFile, outFile, solution);


    getrusage(RUSAGE_SELF, &usage);
    gettimeofday(&tempoFim, NULL);

    timeval_subtract(&tempoDiferenca, &tempoFim, &tempoInicio);

    double tempoUsuario = (double) usage.ru_utime.tv_sec * 1000000 + usage.ru_utime.tv_usec;
    double tempoSistema = (double) usage.ru_stime.tv_sec * 1000000 + usage.ru_stime.tv_usec;
    double tempoGetTimeofDay = (double) ((tempoDiferenca.tv_sec * 1000000) + tempoDiferenca.tv_usec);
    double tempoRuUsage = tempoUsuario + tempoSistema;

    printf("Tempo em microssegunods:\n");
    printf("Tempo Usuario = %.3f microssegundos\n", tempoUsuario);
    printf("Tempo Sistema = %.3f microssegundos\n", tempoSistema);
    printf("Tempo rusage = %.3f microssegundos\n", tempoRuUsage);
    printf("Tempo gettimeofday = %.3f microssegundos\n", tempoGetTimeofDay);

    printf("\nTempo em segundos:\n");
    printf("Tempo Usuario = %.3f segundos\n", tempoUsuario / 1000000);
    printf("Tempo Sistema = %.3f segundos\n", tempoSistema / 1000000);
    printf("Tempo rusage = %.3f segundos\n", tempoRuUsage / 1000000);
    printf("Tempo gettimeofday = %.3f segundos\n", tempoGetTimeofDay / 1000000);

    fclose(inFile);
    fclose(outFile);
    free(solution);

    return 0;
}