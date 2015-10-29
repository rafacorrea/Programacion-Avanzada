#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define ASIENTOS 10 
#define SALAS 3
#define COMPLEJOS 4 
#define COMPRADORES 10 
#define MAXBOLETOS 3
int asientos[ASIENTOS*SALAS*COMPLEJOS];

void * threadfunc(void *); //funcion para los threads

pthread_mutex_t mutexes[ASIENTOS*SALAS*COMPLEJOS] = PTHREAD_MUTEX_INITIALIZER;
int main(int argc, const char * argv[]) {
    
    srand(time(NULL));
 
    pthread_t * compradores = (pthread_t *) malloc (sizeof(pthread_t) * COMPRADORES);

    /* Crear los robots */
    for (int i = 0; i < COMPRADORES; i++) {
        printf("Creando el comprador %d ---\n", i+1);
        pthread_create(compradores+i, NULL, threadfunc, i + 1);
    }
    ;
    /* Esperar a que los robots terminen */
    for (int i = 0; i < COMPRADORES; i++) {
        pthread_join(*(compradores+i), NULL);
    }
    
    free(compradores);
    
    return 0;
}

void * threadfunc(void * arg)
{
    
    int id = (int) arg;
    
    
    int complejo;
    int sala;
    int asiento;
    
    int temp;
    int aux = 0;
    int cuantos = rand()%MAXBOLETOS + 1;
    while(aux < cuantos)
    {
        
        sleep(rand()%3 + 1); //Esta decidiendo el comprador..
        complejo = rand()%COMPLEJOS;
        sala = rand()%SALAS;
        asiento = rand()%ASIENTOS;
        
        temp = complejo * SALAS * ASIENTOS + (sala * ASIENTOS) + asiento;
        pthread_mutex_lock(&(*(mutexes+temp)));
        if(!asientos[temp])
        {
            printf("[Comprador %d]Comprando el asiento %d, en la sala %d, en el complejo %d\n", id, asiento, sala, complejo);
            asientos[temp]++;
            aux++;
        }
        else
        {
            printf("[Comprador %d]El asiento que queria ya estaba ocupado (asiento %d, sala %d, complejo %d), comprando otro...\n", id, asiento, sala, complejo);
        }
        pthread_mutex_unlock(&(*(mutexes+temp)));
    }
    
    pthread_exit(NULL);
}
