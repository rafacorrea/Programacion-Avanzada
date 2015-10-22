//
//  main.c
//  solucion_problema_variable_global
//
//  Created by Vicente Cubells Nonell on 19/10/15.
//  Copyright © 2015 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
tabaco = 0;
papel = 0;
fosforos = 0;


void * agente(void * arg)
{
    int tid = (int) arg;
    int i;
    
    int temp;
    
        
        /* Inicia Región crítica */
        while(1)
        {
            pthread_mutex_lock(&mutex);
            while(pthread_mutex_trylock(&mutex2))
            {
                pthread_mutex_unlock(&mutex);
            
                pthread_mutex_lock(&mutex);
            }//pthread_mutex_lock(&mutex); // DOWN
            //printf("AGENTE!!\n");
            if(!fosforos && !papel && !tabaco)
            {
                
                temp = rand() % 3;
                switch (temp)
                {
                    case 0: tabaco += 1; papel += 1; printf("[Agente]Se coloco papel y tabaco\n");break; 
                    case 1: tabaco += 1; fosforos += 1; printf("[Agente]Se coloco tabaco y fosforos\n");break;
                    case 2: papel += 1; fosforos += 1; printf("[Agente]Se coloco papel y fosforos\n"); break;
                }
                /* Podría haber un cambio de contexto */

                /* Termina región crítica */
            }
            pthread_mutex_unlock(&mutex2); // UP
            pthread_mutex_unlock(&mutex);
        }
    
    
    //pthread_exit(0);
}

void * fumar(void * arg)
{
    int tid = (int) arg;
    int i;
    
    int temp;
    
    while(1) {
        
        pthread_mutex_lock(&mutex2);
        /* Inicia Región crítica */
        while(pthread_mutex_trylock(&mutex)){
            pthread_mutex_unlock(&mutex2);
            
            pthread_mutex_lock(&mutex2);
        
        }//pthread_mutex_lock(&mutex2);
        switch (tid)
        {
           
            case 0: 
                if (papel && fosforos){
                    printf("[Tabaco]Fumando... Esperando 0-2 segundos...\n");
                    papel -= 1;
                    fosforos -= 1;
                    sleep (rand()%3);
                    
                }
                break;
            case 1:
                if (tabaco && fosforos){
                    printf("[Papel]Fumando... Esperando 0-2 segundos...\n");

                    tabaco-=1;
                    fosforos-=1;
                    sleep (rand()%3);
                }
                break;
            case 2:
                if (tabaco && papel){
                    printf("[Fosforos]Fumando... Esperando 0-2 segundos...\n");
                    
                    tabaco -= 1;
                    fosforos -= 1;
                    sleep (rand()%3);
                }
                    
        }
        pthread_mutex_unlock(&mutex);
        pthread_mutex_unlock(&mutex2);
    }
    
    
    //pthread_exit(0);
}

int main(int argc, const char * argv[])
{
    srand(time(NULL));
    
    pthread_t * tid;
    tid = malloc(4 * sizeof(pthread_t));
    
    printf("Creando hilos ...\n");
    
    pthread_create(tid, NULL, fumar, (void *)0);
    pthread_create(tid+1, NULL, fumar, (void *)1);
    pthread_create(tid+2, NULL, fumar, (void *)2);
    pthread_create(tid+3, NULL, agente, (void *)3);
    
    printf("Se crearon %d hilos ...\n", 4);
    /*
    for (i = 0; i < nhilos; ++i) {
        pthread_join(*(tid+i), NULL);
        printf("Se unió el hilo %d con TID = %d...\n", i, *(tid+i));
    }
    */
    while(1);    
    printf("Soy el proceso principal y ya terminaron todos los hilos...\n");
    
    
    free(tid);
    
    return 0;
}

