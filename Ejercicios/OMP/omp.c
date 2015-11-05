#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>

#define N 10000000

FILE * archivo;
int numeros[N];
void popularArchivo(int);

int main(int argc, const char * argv[]) {

    srand(time(NULL));
    //popularArchivo(N);
    archivo = fopen ("numeros.txt", "r");
    int j;
    int contador = 0;
    fscanf (archivo, "%d", &j);
    while(!feof (archivo))
    {
        fscanf (archivo, "%d", &numeros[contador]);
        contador++;     
    }
    fclose(archivo);

    double antes, despues;
    double elapsed;
    int sum;    
    antes = omp_get_wtime();
    #pragma omp parallel reduction(+:sum)
    {
        #pragma omp for schedule(dynamic,1000000)
        for (int i = 0; i < N; i++)
        {
            sum+=numeros[i];
        }
        printf("Suma del hilo: %d\n", sum);
    }
    despues = omp_get_wtime();
    elapsed = despues - antes;
    printf("Suma %d\n en %f segundos\n", sum, elapsed);
    
    return 0;
}



void popularArchivo(int n)
{
    archivo = fopen("numeros.txt", "w+");
    fprintf(archivo,"%d\n", N);
    for(int i = 0; i < n; i++)
    {

        fprintf(archivo,"%d\n", rand()%10);
        
    }
    fclose(archivo);
}
