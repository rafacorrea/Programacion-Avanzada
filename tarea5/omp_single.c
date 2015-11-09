#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>

#define N 4

/*CLAUSULAS POSIBLES: copyprivate, firstprivate, nowait, private*/

int main(int argc, const char * argv[]) {

    #pragma omp parallel num_threads(N)
    {
        int id = omp_get_thread_num();
        printf("Hilo %d ejecuta esta instruccion\n", id);
        #pragma omp single
        {
            printf("Soy el unico thread que ejecuta esta instruccion y soy el hilo numero %d", id);
        }
    }
    
    return 0;
}


