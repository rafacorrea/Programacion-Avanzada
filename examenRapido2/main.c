#include <stdio.h>
#include <signal.h>
#include <unistd.h>
int valor;
int ctrlc = 0;
int ctrlz = 0;
void manejador(int ids)
{

    switch(ids)
    {
        case SIGINT:
            valor++;
            break;
        case SIGTSTP:
            valor--;
            break;
        case SIGUSR1:
            printf("Se ha pulsado %d veces CTRL+C y se ha pulsado %d veces CTRL+Z Acabando...", ctrlc, ctrlz);
    }
}

void manejador2(int ids)
{

    switch(ids)
    {
        case SIGINT:
            ctrlc++;
            break;
        case SIGTSTP:
            ctrlz++;
            break;
    }
}
int main(int argc, const char * argv[]) {
    
    
    pid_t pid;
    
    pid = fork();
    signal(SIGTSTP, manejador);
    if (!pid)
    {
        signal(SIGTSTP, manejador2);
        signal(SIGINT, manejador2);
        int k = 10;
        while(k--)
        {
        sleep(1);
        }
        kill(getppid(),10);
    
    }
    else
    {
        valor = 3;
        signal(SIGUSR1, manejador);
        signal(SIGTSTP, manejador);
        signal(SIGINT, manejador);
        while(1)
        {
        printf("Aparezco cada %d segundos\n", valor);
        sleep(valor);
        
        //wait(NULL);
        }
    }
    // A partir de aquí Ctrl+C no termina el programa
    

    return 0;
}
