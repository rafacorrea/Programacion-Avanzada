//
//  main.c
//  productor_consumidor
//
//  Created by Vicente Cubells Nonell on 22/10/15.
//  Copyright © 2015 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define ENANITOS 7
#define SILLAS 4

int sillas;
int comida;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t consume_t = PTHREAD_COND_INITIALIZER;
pthread_cond_t produce_t = PTHREAD_COND_INITIALIZER;

void * servir(void *);
void * comer(void *);

int main(int argc, const char * argv[]) {
    
    
    srand(time(NULL));
    
    pthread_t blancanieves;
    pthread_t * enanitos = (pthread_t *) malloc (sizeof(pthread_t) * ENANITOS);
    
    /* Crear el hilo productor */
    blancanieves = pthread_create(&blancanieves, NULL, servir, NULL);
    /* Crear el hilo consumidor */
    for (int i = 0; i < ENANITOS; i++) {
        printf("Creando el enanito %d ---\n", i+1);
        pthread_create(enanitos+i, NULL, comer, i);
    }
    
    
    pthread_t * aux;
    aux = enanitos;
    /* Esperar a que los hilos terminen */
    for (int i = 0; i < ENANITOS; i++) {
        pthread_join(*(aux+i), NULL);
    }
    pthread_join(blancanieves, NULL);
    
    free(enanitos);
    
    return 0;
}

void * servir(void * arg)
{
    
    
    while(1)
    {
        //sleep(rand() % 2);
        pthread_mutex_lock(&mutex2);
        if(!comida)
        {
            printf("[Blancanieves] Nadie me necesita, me voy a dar una vuelta\n");
            pthread_cond_wait(&produce_t, &mutex2);
           
        }
        printf("[Blancanieves] Un enanito me pidio comida, voy a cocinar \n");
        pthread_mutex_unlock(&mutex2);
        printf("[Blancanieves] Cocinando (0-2 segundos)...\n");
        sleep(rand()%3);   
        pthread_mutex_lock(&mutex2);
        comida--;
        pthread_cond_signal(&consume_t);
        pthread_mutex_unlock(&mutex2);
        printf("[Blancanieves] Le di comida al enanito\n");


//pthread_mutex_unlock(&mutex);

    }
    pthread_exit(NULL);
}

void * comer(void * arg)
{
    int id = (int) arg + 1;
    
    while(1)
    {
        printf("[Enanito %d]Estoy trabajando..\n", id);
        sleep(5 + rand() % 10);
        
        pthread_mutex_lock(&mutex);
        if(sillas < SILLAS)
        {

            sillas++;
            printf("[Enanito %d]Ocupe una silla, quedan %d sillas\n", id, SILLAS - sillas);
            pthread_mutex_unlock(&mutex);
            
            pthread_mutex_lock(&mutex2);
            comida++;
            pthread_mutex_unlock(&mutex2);
            pthread_cond_signal(&produce_t);
            printf("[Enanito %d]Ya le avise a blancanieves...\n", id);
            pthread_mutex_lock(&mutex2);
            pthread_cond_wait(&consume_t, &mutex2);
            pthread_mutex_unlock(&mutex2);
            /*pthread_mutex_lock(&mutex2);
            comida--;
            pthread_mutex_unlock(&mutex2);
            */
            printf("[Enanito %d]Recibi mi comida, comiendo...\n", id);
            sleep(rand() % 2);
            
            pthread_mutex_lock(&mutex);
            sillas--;
            printf("[Enanito %d]Termine de comer... Desocupando silla, quedan %d sillas\n", id, SILLAS - sillas);
            
            pthread_mutex_unlock(&mutex);
        }
        else
        {
            pthread_mutex_unlock(&mutex);
        }
    }
    pthread_exit(NULL);
}

