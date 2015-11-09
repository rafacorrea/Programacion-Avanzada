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
        printf("Hilo %d ejecuta esta instruccion\n", id);
        #pragma omp master
        {
            printf("Soy el hilo maestro(id: %d) y soy el unico que ejecuta esta instruccion\n", id);
        }
    }
    
    return 0;
}


