//
//  main.c
//  conjunto_señales
//
//  Created by Vicente Cubells Nonell on 08/10/15.
//  Copyright © 2015 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <signal.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>

#define TIEMPO 3
#define FICHEROS 5
#define NSIG 64;

DIR * directorio;
char * buffer[20];
int existe;
FILE *fp= NULL;
int grabar;

void manejador1(int ids)
{
    grabar = 0;
}
int main(int argc, const char * argv[])
{
    
    sigset_t pendientes, todas;
    struct dirent* in_file;

    sigfillset(&todas);

    
    sigdelset(&todas, SIGALRM);
    

    sigprocmask(SIG_BLOCK, &todas, NULL);

    directorio = opendir("."); //volver a abrir el directorio

    while((in_file = readdir(directorio)))
    {

        if(strcmp(in_file->d_name, "datos") == 0) //si es un numero ie. es un proceso
        existe = 1;
    }
                   
    if(existe == 0)
    {
        system("mkdir datos");
        printf("Se creo la carpeta\n");
        existe = 1;
    }
    
    signal (SIGALRM, manejador1);
    
    int k = 0;
    while (k < FICHEROS)
    {
        printf("Creando archivo... (Bloqueando senales)\n");
        int sig;
        grabar = 1;
        sprintf(buffer, "./datos/a%d", k);
        k++;
        fp = fopen(buffer, "w+");
        //char unChar = 'x';
        alarm(TIEMPO);
        while(grabar){
            fputc('x', fp);
        }
        sigpending(&pendientes);
        for(sig=1; sig < 64; sig++)
        {
            if(sigismember(&pendientes, sig))
                fprintf(fp, "\nEstaba bloqueada: la senal %d\n", sig);
        }
        fclose(fp);
        
    }
    printf("Imprimiendo informacion ...\n\n");
                       system("ls -lh datos");
                       sigprocmask(SIG_UNBLOCK, &todas, NULL);

    return 0;
}
