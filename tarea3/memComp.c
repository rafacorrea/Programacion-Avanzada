#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE    1024 * 1024


int factorial(int);

void die(char *s)
{
    perror(s);
    exit(1);
}


int main()
{
    char c;
    int shmid;
    key_t key;
    //char *shm, *s;
    int *status, *sNumero;
    int numero;
    const int shareSize = MAXSIZE * sizeof(int);
    
    key = 5678; //no se utilizo (se utilizo IPC_PRIVATE), pero se podria reemplazar en el shmget para comunicar entre procesos no relacionados

    shmid = shmget(IPC_PRIVATE, shareSize, IPC_CREAT | 0666);
    status = (int*)shmat(shmid, NULL, 0);
    sNumero = status+1;
    *status = 0;

    if (fork()!=0)
    {

        while(1)
	    { //loop para que pregunte por otro numero
            if ((*status) != 1) //status es para revisar que ya se calculo el factorial por el hijo
            {
                fprintf(stdout, "Escriba un numero a calcular el factorial\n");
                scanf("%d", &numero);
                *sNumero = numero;
                *status = 1;
                
                //wait(NULL);
            }
        }
        
    }
    else
    {
        //for(;;){
        while(1) //loop para que siga esperando
        {
            if(*status)
            {
                fprintf(stdout, "Factorial de %d es %d\n", *sNumero, factorial(*sNumero));                
                (*status) = 0; //para que el padre pregunte por otro numero
            }
        }

    }
    return 0;
}


int factorial(int numero)
{
    int temp = 1;
    for( ; numero > 1; numero--)
    {
        temp *= numero;
    }
    return temp;
}
