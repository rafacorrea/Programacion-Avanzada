#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define PERSONAS 10

//van a ser random
#define T_BANO 7 //tiempo en el bano (maximo)
#define T_START 10 //tiempo antes de tener que ir al bano (maximo)

//mujer_quiere_entrar, hombre_quiere_entrar, mujer_sale y hombre_sale.

int status; // 0 = vacio, 1 = mujeres, 2 = hombres
int mujeres; //en espera
int hombres; //en espera
int ocupado; //en el bano

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int mujer_quiere_entrar ();
int hombre_quiere_entrar();
void mujer_sale();
void hombre_sale();

void * threadfunc(void *);

int main(int argc, const char * argv[]) {
    
    
    srand(time(NULL));
    
    pthread_t * personas = (pthread_t *) malloc (sizeof(pthread_t) * PERSONAS);

    /* Crear los hilos */
    for (int i = 0; i < PERSONAS; i++) {
        printf("+++ Creando la persona %d... \n", 1 + i);
        pthread_create(personas+i, NULL, threadfunc, rand()%2); //rand para definir genero
    }
    
    
    /* Esperar a que los hilos terminen */
    for (int i = 0; i < PERSONAS; i++) {
        pthread_join(*(personas+i), NULL);
    }
    
    free(personas);
    
    return 0;
}

void * threadfunc(void * arg)
{
    int genero = (int) arg;
    sleep(rand() % T_START);
    
    if(genero) //hombre
    {
        pthread_mutex_lock(&mutex);
        hombres++;
        printf("Llega un hombre (%d en espera)\n", hombres);
        pthread_mutex_unlock(&mutex);
        int entro = 0;
        while(!entro)
        {
            pthread_mutex_lock(&mutex);
            entro = hombre_quiere_entrar();
            pthread_mutex_unlock(&mutex);
        }
        sleep(rand()% T_BANO); //Esta en el bano...
        pthread_mutex_lock(&mutex);
        hombre_sale();
        pthread_mutex_unlock(&mutex);
    }
    else //mujer
    {

        pthread_mutex_lock(&mutex);
        mujeres++;
        printf("Llega una mujer (%d en espera)\n", mujeres);
        pthread_mutex_unlock(&mutex);
        int entro = 0;
        while(!entro)
        {
            pthread_mutex_lock(&mutex);
            entro = mujer_quiere_entrar();
            pthread_mutex_unlock(&mutex);
        }
        sleep(rand()% T_BANO); //Esta en el bano...
        pthread_mutex_lock(&mutex);
        mujer_sale();
        pthread_mutex_unlock(&mutex);
    }

    
    pthread_exit(NULL);
}

int mujer_quiere_entrar()
{
    if(status == 0 || status ==1)
    {
        
        mujeres--;
        ocupado++;
        printf("Entra una mujer (%d en espera)\n", mujeres);
        if (!status) //estaba vacio
        {
            status = 1;
            printf("Sanitario ocupado por mujeres\n");
        }
        return 1;
    }
    else
        return 0;
}

int hombre_quiere_entrar()
{
    if(status == 0 || status == 2)
    {
        
        hombres--;
        ocupado++;
        printf("Entra un hombre (%d en espera)\n", hombres);
        if (!status) //estaba vacio
        {
            status = 2;
            printf("Sanitario ocupado por hombres\n");
        }
        return 1;
    }
    else return 0;
}

void mujer_sale()
{
    printf("Sale una mujer\n");
    ocupado--;
    if(!ocupado)
    {
        status = 0;
        printf("Sanitario vacio\n");
    }
}

void hombre_sale()
{
    printf("Sale un hombre\n");
    ocupado--;
    if(!ocupado)
    {
        status = 0;
        printf("Sanitario vacio\n");
    }
}

