#include "../include/gerenciaTempo.h"

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

void getUsageNow (double *user, double *system) {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    *user = joinTimes(usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
    *system = joinTimes(usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
}

double joinTimes (time_t s, suseconds_t ms) {
    return ((double) (s * 1000000 + ms));
}

void printTimes (double tempoUsuario, double tempoSistema, double tempoRuUsage, double tempoGetTimeofDay) {
    // imprime os tempos de execucao em microssegundos
    printf("\n---Tempo de execucao do programa---\n");
    printf("\nTempo em microssegunods:\n");
    printf("Tempo Usuario = %.3f microssegundos\n", tempoUsuario);
    printf("Tempo Sistema = %.3f microssegundos\n", tempoSistema);
    printf("Tempo rusage = %.3f microssegundos\n", tempoRuUsage);
    printf("Tempo gettimeofday = %.3f microssegundos\n", tempoGetTimeofDay);
    // imprime os tempos de execucao em segundos
    printf("\nTempo em segundos:\n");
    printf("Tempo Usuario = %.3f segundos\n", tempoUsuario / 1000000);
    printf("Tempo Sistema = %.3f segundos\n", tempoSistema / 1000000);
    printf("Tempo rusage = %.3f segundos\n", tempoRuUsage / 1000000);
    printf("Tempo gettimeofday = %.3f segundos\n", tempoGetTimeofDay / 1000000);
}