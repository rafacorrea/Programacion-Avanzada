#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
	

int factorial(int);

int main(int argc, const char * argv[])
{
    sem_t * mutex, * mutex2;
    pid_t pid;
    int * numero = mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);

	 if ((pid = fork()) < 0) {
		perror("fork");
		exit(1);
	    }

    mutex = sem_open("mutex", O_CREAT, 0644, 1); //crear el semaforo compartido antes del forc
    mutex2 = sem_open("mutex2", O_CREAT, 0644, 0); //segundo semaforo
    sem_init(mutex,1,1); //inicializar en 1
    sem_init(mutex2,1,0); //inicializar en 0

	if (pid == 0)
	 { 
		while(1)
		{   
		   
		    sem_wait(mutex2); //Esperar a que el hijo de post
		    fprintf(stdout, "[Padre]: El factorial de %d es %d\n", *numero, factorial(*numero));
		    sem_post(mutex); //Darle permiso al hijo, ya termine

		   
		}
	 }

	else
	{
        while(1)
        {
            sem_wait(mutex); //Espero a que el padre de post...
            sleep(1);  //para asegurar que imprima el otro proceso antes   
            fprintf(stdout, "[Hijo]: Dame el numero\n");
            scanf("%d", &(*numero));
            fprintf(stdout, "[Hijo]: Se guardo el numero\n");
            sem_post(mutex2); //Ya termine, darle permiso al padre
	    }

		
	}


	return 0;

}//Cierre de main

int factorial(int a)
{
	int i=0; int resultado=1;
	for (i=2;i<=a; ++i)
	resultado *=i;

	return resultado;
}
