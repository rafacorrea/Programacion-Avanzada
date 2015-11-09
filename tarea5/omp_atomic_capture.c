#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>

#define N 4

/*CLAUSULAS POSIBLES: NINGUNA*/

int main(int argc, const char * argv[]) {
    int compartido;
    printf("El valor inicial de la variable compartida es: %d\n", compartido);
    #pragma omp parallel num_threads(N)
    {
        int viejo;
        int id = omp_get_thread_num();
        #pragma omp atomic capture //INSTRUCCION UNICA, para multiples utilizar omp critical
            viejo=compartido++;
        printf("Valor antes de sumar: %d\n", viejo);
    }
    printf("El valor final de la variable compartida es: %d\n", compartido);
    
    return 0;
}


