#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define N 10000000
#define THREADS 1

//int asientos[ASIENTOS*SALAS*COMPLEJOS];

int total;
FILE * archivo;
int numeros[N];
void popularArchivo(int);
void * threadfunc(void *); //funcion para los threads
clock_t despues;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
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
    
    pthread_t * calculos = (pthread_t *) malloc (sizeof(pthread_t) * THREADS);

    /* Crear los robots */
    clock_t antes;//, despues;
    double elapsed;
    antes= clock();
    //printf("%f\n", antes);
    
    for (int i = 0; i < THREADS; i++) {
        //printf("Creando el comprador %d ---\n", i+1);
        pthread_create(calculos+i, NULL, threadfunc,  i);
    }

    /* Esperar a que los robots terminen */
    for (int i = 0; i < THREADS; i++) {
        pthread_join(*(calculos+i), NULL);
    }

    elapsed = ((double) (despues-antes)) / CLOCKS_PER_SEC;
    printf("Suma %d\n en %f segundos\n", total, elapsed);
    free(calculos);
    
    return 0;
}

void * threadfunc(void * arg)
{
    
    int empiezo = (int) arg;
    int fin = (int) arg;
    fin = (empiezo+1)*N/THREADS;
    empiezo = empiezo*N/THREADS;
    int i;
    int temp = 0;
    int contador1 = empiezo;
        while(contador1 >= empiezo && contador1 < fin)
        {
            temp+=numeros[contador1];
            contador1++;     
        }   

    pthread_mutex_lock(&mutex);
    total+=temp;
    pthread_mutex_unlock(&mutex);

    despues = clock();
    pthread_exit(NULL);
}



void popularArchivo(int n)
{
    archivo = fopen("numeros.txt", "w+");
    for(int i = 0; i < n; i++)
    {

        fprintf(archivo,"%d\n", rand()%10);
        
    }
    fclose(archivo);
}
