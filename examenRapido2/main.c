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
            ctrlc++;
            break;
        case SIGTSTP:
            valor--;
            ctrlz++;
            break;
        case SIGUSR1:
            printf("Se ha pulsado %d veces CTRL+C y se ha pulsado %d veces CTRL+Z Acabando...", ctrlc, ctrlz);
    }
}


int main(int argc, const char * argv[]) {
    
    
    pid_t pid;
    
    pid = fork();
    //signal(SIGTSTP, manejador);
    if (!pid)
    {
        signal(SIGTSTP, SIG_IGN);
        signal(SIGINT, SIG_IGN);
        int k = 10;
        while(k--)
        {
        printf("[Hijo] Segundo #%d\n", k);
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
        int k;
        while(1)
        {
        printf("Aparezco cada %d segundos\n", valor);
        
        k = valor;
        while(k--)
            sleep(1);
        
        //wait(NULL);
        }
    }
    // A partir de aquí Ctrl+C no termina el programa
    

    return 0;
}
