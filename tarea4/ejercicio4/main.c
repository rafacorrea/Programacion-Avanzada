#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define UAD 5 //cuantas secciones tiene el centro comercial
#define ALARMA 6 //frecuencia del muestro 1-N

int medida[UAD];
int criticos[UAD];
FILE * disco;

pthread_mutex_t mutexes[UAD * 2] = PTHREAD_MUTEX_INITIALIZER; //
pthread_mutex_t m_archivo = PTHREAD_MUTEX_INITIALIZER;

pthread_t control;


void * threadfunc(void *); //funcion para los threads
void * centralfunc(void *); //funcion para el nodo principal
void registro(int);
void registroCritico(int);
void cerrar_archivo(int);

int main(int argc, const char * argv[]) {
    
    srand(time(NULL));
    //disco = fopen("disco", "w+");
 
    pthread_t * uads = (pthread_t *) malloc (sizeof(pthread_t) * UAD);
    

    /* Crear los UAD */
    for (int i = 0; i < UAD; i++) {
        printf("Creando el UAD %d\n", i);
        pthread_create(uads+i, NULL, threadfunc, i);
    }
    pthread_create(&control,NULL,centralfunc,NULL);
    
    /* Esperar a que los threads terminen */
    for (int i = 0; i < UAD; i++) {
        pthread_join(*(uads+i), NULL);
    }
    
    pthread_join(control, NULL);
    
    free(uads);
    
    return 0;
}

void registro(int ids) //manejador de senial periodica alarm (central)
{
    printf("[Central]Empezando el muestreo...\n");
    for (int i = 0; i < UAD; i++)
    {
        pthread_mutex_lock(mutexes+i);
        pthread_mutex_lock(&m_archivo);
        
        disco = fopen("disco", "a+");
        fprintf(disco,"[UAD %d]Sensor midio=>%d\n",i, medida[i]);
        fclose(disco);
        
        pthread_mutex_unlock(&m_archivo);
        pthread_mutex_unlock(mutexes+i);
        //int temp = rand()%ALARMA + 1;
        alarm(rand()%ALARMA+1);
    }
    printf("[Central]Se termino el muestro exitosamente\n");
}

void registroCritico(int ids) //manejador de senial cuando se detecta una medida critica
{
    for (int i = 0; i < UAD; i++)
    {
        pthread_mutex_lock(mutexes+UAD+i);

        if (criticos[i])
        {
            //printf("Guardando alarma..\n");
            pthread_mutex_lock(&m_archivo); 
            disco = fopen("disco", "a+");
            fprintf(disco,"[UAD %d]VALOR CRITICO DETECTADO\n",i);
            fclose(disco);
            pthread_mutex_unlock(&m_archivo);
            criticos[i]--;
        }
        
        pthread_mutex_unlock(mutexes+UAD+i);


    }

    printf("[Central]Se registraron las alarmas en el disco\n");
}

void * threadfunc(void * arg) //funcion para los UADs
{
    int id = (int) arg;
    int temp;
    //signal(SIGUSR1, manejador);
    while(1)
    {
        sleep(rand()%3 + 1);
        pthread_mutex_lock(&(*(mutexes + id)));
        //printf("[UAD %d]Midiendo...\n", id);
        medida[id] = rand()%10;
        pthread_mutex_unlock(&(*(mutexes + id)));
        if(!(temp =rand()%10))//critico
        {
            printf("[UAD %d]VALOR CRITICO DETECTADO, MANDANDO ALARMA A LA CENTRAL\n", id);
            
            pthread_mutex_lock(mutexes + id + UAD);
            
            criticos[id]++;
            pthread_kill(control, SIGUSR1);
         
            pthread_mutex_unlock(mutexes + id + UAD);
        }

    }
    pthread_exit(NULL);
}

void * centralfunc(void * arg) //funcion para la central
{
    signal(SIGALRM, registro); //cada cierto tiempo....
    signal(SIGUSR1, registroCritico);
    //int temp = rand()%ALARMA + 1;
    alarm(rand()%ALARMA + 1);
    while(1);
    pthread_exit(NULL);
}
