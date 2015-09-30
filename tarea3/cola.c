#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>

#define MSGSZ   sizeof(int) //la estructura solo manda un int



typedef struct msgbuf {
         long    mtype;
         int     numero;
         } message_buf; //estructura para mandar mensaje

int factorial(int); //regresa el factorial del parametro

int main()
{
    int msqid;
    int msgflg = IPC_CREAT | 0666;
    key_t key;
    message_buf sbuf, rbuf;
    size_t buf_length;

    key = 1234; //key predefinida, se puede utilizar IPC_PRIVATE 


    if ((msqid = msgget(key, msgflg )) < 0) {
        perror("msgget");
        exit(1);
    }

    if(fork()!=0)
    {
        while(1) //para que siga preguntando
        {
	        printf("Escriba el numero que desea calcular\n");
         	scanf("%d", &(sbuf.numero));
            sbuf.mtype = 1; //se usa por msgqueue para envio de mensajes
            buf_length = MSGSZ; //sizeof(int) porejemplo


            if (msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0) {
                printf ("%d, %d, %d, %d\n", msqid, sbuf.mtype, sbuf.numero, buf_length);
                perror("msgsnd");
                exit(1);
            }
            sleep(1); //tiempo para que el hijo calcule (funciona sin esto, pero el menu no sale bien)
          
        }
    }
    else
    {
	    while(1) //para que siga preguntando por numeros
	    {
            if (msgrcv(msqid, &rbuf, MSGSZ, 1, 0) < 0) {
                perror("msgrcv");
                exit(1);
            }


            printf("El factorial de %d es: %d\n", rbuf.numero, factorial(rbuf.numero));


	    }
    }
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
