#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>

#define N 4

/*CLAUSULAS POSIBLES: */
/*
PARAMETROS POSIBLES: parallel, sections, for, taskgroup
Ejecutar asi: OMP_CANCELLATION=true ./a.out
*/

int main(int argc, const char * argv[]) {

    #pragma omp parallel num_threads(N)
    {
        int id = omp_get_thread_num();
        #pragma omp for 
        for(int i = 0; i<20; i++)
        {
            printf("Ciclo %d por hilo %d\n", i, id);
             if(i>9)
            {
                printf("Hilo %d: El ciclo en el que estoy es mayor a 9, saliendo del pragma omp for Y saltando al cancellation point...\n", id);
                #pragma omp cancel for
            }
            printf("Se ejecuto correctamente\n");
            #pragma omp cancellation point for
            
        }
        
        
    }
    
    return 0;
}


