#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>

#define N 4

/*CLAUSULAS POSIBLES: NINGUNA*/
/*ARGUMENTOS: (name)*/

int main(int argc, const char * argv[]) {
    int compartido;
    printf("El valor inicial de la variable compartida es: %d\n", compartido);
    #pragma omp parallel num_threads(N)
    {
        int id = omp_get_thread_num();
        #pragma omp critical (sumar) //indica seccion critica o protegida, solo un hilo ejecuta esta seccion.
        {
            printf("Soy el hilo %d y estoy en la seccion critica\n", id);
            compartido++;
        }
        
    }
    printf("El valor final de la variable compartida es: %d\n", compartido);
    
    return 0;
}


