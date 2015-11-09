#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>

#define N 2

/*CLAUSULAS POSIBLES: NINGUNA*/

int main(int argc, const char * argv[]) {
    int numero = 0;
    #pragma omp parallel sections num_threads(N)
    {
        #pragma omp section
        {
            int id = omp_get_thread_num();
            printf("Thread %d esta cambiando el valor de numero..\n", id);
            numero = 10;

            #pragma omp flush(numero)
        }
        #pragma omp section
        {
            int id = omp_get_thread_num();
            while(!numero)
            {
                #pragma omp flush(numero)
            }
            printf("Al ejecutar flush, thread %d se dio cuenta que cambio el valor\n", id);
        }
    }
    
    return 0;
}


