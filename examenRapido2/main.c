#include <stdio.h>
#include <signal.h>
#include <unistd.h>
int valor;

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
    }
}

int main(int argc, const char * argv[]) {
    
    
    pid_t pid;
    
    pid = fork();
    signal(SIGTSTP, manejador);
    if (!pid)
    {
        sleep(10);
        
    
    }
    else
    {
        valor = 3;
        signal(SIGTSTP, manejador);
        signal(SIGINT, manejador);
        while(1)
        {
        printf("Aparezco cada 3 segundos\n");
        sleep(3);
        
        //wait(NULL);
        }
    }
    // A partir de aquí Ctrl+C no termina el programa
    

    return 0;
}
