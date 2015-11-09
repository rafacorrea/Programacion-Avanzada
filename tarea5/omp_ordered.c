#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>

#define N 4

/*CLAUSULAS POSIBLES: NINGUNA*/
/*EN CLAUSULA: for, o dentro de un pragma omp for*/

int main(int argc, const char * argv[]) {
    #pragma omp parallel num_threads(N)
    {
        #pragma omp single
        {
            printf("Con ordered:\n");
        }
        int id = omp_get_thread_num();
        #pragma omp for ordered
        for(int i = 0; i < 10; i++)
        {
            #pragma omp ordered
            printf("Thread %d, ciclo: %d\n", id, i);
        }
        
        #pragma omp single
        {
            printf("\nSin ordered:\n");
        }
        //int id = omp_get_thread_num();
        #pragma omp for
        for(int i = 0; i < 10; i++)
        {
            printf("Thread %d, ciclo: %d\n", id, i);
        }

        
    }
    
    return 0;
}


