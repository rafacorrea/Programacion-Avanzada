#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define SECCIONES 10 //cuantas secciones tiene el centro comercial
#define PESO_MAX 100 //peso maximo de las secciones
#define PESOROBOT 30 //cuanto pesa un robot
#define ROBOTS 20 //cuantos robots hay

int peso[SECCIONES];//int para guardar los pesos que sostienen las secciones

void * threadfunc(void *); //funcion para los threads

pthread_mutex_t mutexes[SECCIONES] = PTHREAD_MUTEX_INITIALIZER; //mutexes para accesar a cada indice de la variable peso
pthread_cond_t condiciones[SECCIONES] = PTHREAD_COND_INITIALIZER; //condiciones para cada seccion

int main(int argc, const char * argv[]) {
    
    srand(time(NULL));
 
    pthread_t * robots = (pthread_t *) malloc (sizeof(pthread_t) * ROBOTS);

    /* Crear los robots */
    for (int i = 0; i < ROBOTS; i++) {
        printf("Creando el robot %d ---\n", i+1);
        pthread_create(robots+i, NULL, threadfunc, i + 1);
    }
    ;
    /* Esperar a que los robots terminen */
    for (int i = 0; i < ROBOTS; i++) {
        pthread_join(*(robots+i), NULL);
    }
    
    free(robots);
    
    return 0;
}

void * threadfunc(void * arg)
{
    
    int id = (int) arg;

    for(int i = 0; i < SECCIONES; i++)
    {
        //para revisar el peso actual del siguiente nivel   
        pthread_mutex_lock(&(*(mutexes+i)));
        while(1)
        {
            /*revisar si se puede pasar a la siguiente seccion*/
            if(peso[i]+PESOROBOT <= PESO_MAX)
            {
                printf("[Robot %d]Entrando a la seccion %d\n", id, i);
                //ajustar peso de la seccion a la que acabo de entrar
                peso[i]+= PESOROBOT;
                
                //ya no necesito acceso al espacio correspondiente al peso de la seccione
                pthread_mutex_unlock(&(*(mutexes+i)));
                
                
                
                if(i > 0)
                {
                    //ajustar peso de seccion que acabo de dejar
                    pthread_mutex_lock(&(*(mutexes+i-1)));
                    peso[i-1]-=PESOROBOT;
                    pthread_mutex_unlock(&(*(mutexes+i-1)));
                    
                    //avisar que ya se puede pasar
                    pthread_cond_signal(&(*(condiciones+i-1)));
                    
                }

                printf("[Robot %d]  Comprando...\n", id);

                //Esperar 1-3 segundos para comprar        
                sleep(rand()%3 + 1);
                printf("[Robot %d]    Termine con la seccion %d\n", id, i);
                
                //tratar de subir al siguiente piso (iterar el for)
                break;
                
            }
            /*Si no se puede... esperar*/
            else
            {
                /*esperar a que me avisen que ya se salio un robot*/
                pthread_cond_wait(&(*(condiciones+i)), &(*(mutexes+i)));
                
            }
        }       
    }
    printf("[Robot %d]      Termine de hacer las compras\n", id);

    /*bajar peso actual de la ultima seccion*/
    pthread_mutex_lock(&(*(mutexes+SECCIONES - 1)));
    peso[SECCIONES-1]-= PESOROBOT;
    pthread_mutex_unlock(&(*(mutexes+SECCIONES - 1)));
    
    /*avisar a los robots esperando que ya se puede pasar a la ultima seccion*/
    pthread_cond_signal(&(*(condiciones+SECCIONES - 1)));
    pthread_exit(NULL);
}
