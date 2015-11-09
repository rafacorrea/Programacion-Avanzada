#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>

#define N 4

/*CLAUSULAS POSIBLES: NINGUNA*/

int main(int argc, const char * argv[]) {
    #pragma omp parallel num_threads(N)
    {
        int id = omp_get_thread_num();
        sleep(id);
        printf("Hilo %d termino, esperando a los demas...\n", id);
        #pragma omp barrier
        printf("Hilo %d continua...\n", id);
    }
    
    return 0;
}


